#include <iostream>
#include <tuple>

#include  "oneapi/tbb.h"

using tbb::flow::graph;
using tbb::flow::multifunction_node;
using tbb::flow::input_node;
using tbb::flow::function_node;
using tbb::flow::serial;
using tbb::flow_control;
using tbb::flow::output_port;

const size_t num = 10;

class Generator {
    public:
        Generator(): counter(0){}

        size_t operator() (flow_control& fc) {
            if(counter < num) {
                ++counter;
                return counter;
            }
            fc.stop();
            return 0;
        }
    private:
        size_t counter;
};

class MultiNodeFunctor {
    public:
        void operator() (const int i, multifunction_node<int, std::tuple<int, int>>::output_ports_type &op) {
            if (i % 2) {
                std::get<0>(op).try_put(i);
            }else{
                std::get<1>(op).try_put(2*i);
            }
        }
};

template<typename T>
class TaskInput {
    public:
        TaskInput(T c): counter(c){

        }
        T operator()(tbb::flow_control& fc) { //try_put to start node
            if(counter < num) {
                ++counter;
                return counter;
            }
            fc.stop();
            return 0;
        }
    private:
        T counter;
};



void start_flow() {
    graph g;

    //input_node<int> n1(g, Generator());
    input_node<int> n1(g, TaskInput<float>(0));
    multifunction_node<int, std::tuple<int, int>> n2(g, 1, MultiNodeFunctor());

    function_node<int, int>n3(g, 1, [](const int i) -> int {
        std::cout<<"n3 i:"<<i<<std::endl;
        return i;
    });
    
    n1.activate();
    make_edge(n1, n2);
    make_edge(output_port<0>(n2), n3);
    make_edge(output_port<1>(n2), n3);
    g.wait_for_all();
}

int main() {
    start_flow();
    return 0;
}
