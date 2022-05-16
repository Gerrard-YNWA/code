#include <iostream>
#include <chrono>
#include <memory>
#include <thread>

#include "oneapi/tbb.h"
#include "oneapi/tbb/tick_count.h"


using tbb::flow::function_node;
using tbb::flow::queue_node;
using tbb::flow::lightweight;
using tbb::flow::graph;
using tbb::flow::unlimited;
using tbb::flow::serial;



void spin_for( double delta_seconds ) {
    tbb::tick_count start = tbb::tick_count::now();
    while( (tbb::tick_count::now() - start).seconds() < delta_seconds ) ;
}


static const int sub_graph_count = 1;

void spawn_sub_flow(size_t concurrency, int data) {
    graph g2;

    function_node<int, int> f3(g2, concurrency, [](int i) {
        std::cout<<"f3:" << i <<std::endl;
        return i;
    });

    queue_node<int> q1(g2);

    function_node<int, int> f4(g2, serial, [&](const int i) -> int {
        std::cout<<"f4 begin to spin:" << i << std::endl;
        int a;
        while(true) {
            auto ret = q1.try_get(a);
            if (ret) {
            
                std::cout<<"try_get " << a <<std::endl;
                spin_for(1);
            }  else {
                //wait for a while
                std::cout << std::this_thread::get_id()<<" sleep 100ms " << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        }
        std::cout<<"f4 end" << std::endl;
        return i;
    });

    make_edge(f3, q1);
    make_edge(q1, f4);
    for(auto j = 1; j < 100; j++) {
        q1.try_put(j);
    }
    //f3.try_put(data);
    g2.wait_for_all();
}


void start(int range) {
    graph g1;

    function_node<int, int> f1(g1, 1, [](int i) {
        std::cout<<"f1:" << i <<std::endl;
        return i;
    });

    function_node<int, int, lightweight> f2(g1, sub_graph_count, [](const int i) -> int{
        std::cout << "f2 Begin sub graph:" << i <<std::endl;

        auto t0 = tbb::tick_count::now();
        spawn_sub_flow(sub_graph_count, i);
        auto t1 = tbb::tick_count::now();

        std::cout << "f2 End , cost:"  << (t1-t0).seconds()<< std::endl;
        return i;
    });
        
    function_node< int, int > f5(g1, 1, []( int i ) {
        std::cout<<"f5:" << i <<std::endl;
        return i;
    });

    make_edge(f1, f2);
    make_edge(f2, f5);
    for (auto i = 1; i <= range; ++i) {
        f1.try_put(i);
    }
    std::cout<<"put done." <<std::endl;
    g1.wait_for_all();
}


int main() {
    std::thread t1(start, 1);
    //std::thread t2(start, 100);
    t1.join();
    //t2.join();    
    return 0;
}
