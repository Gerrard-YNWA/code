#include <iostream>

#include "oneapi/tbb.h"
#include "oneapi/tbb/tick_count.h"


using tbb::task_group_context;
using tbb::flow::function_node;
using tbb::flow::graph;
using namespace std;


void spin_for( double delta_seconds ) {
    tbb::tick_count start = tbb::tick_count::now();
    while( (tbb::tick_count::now() - start).seconds() < delta_seconds ) ;
}

int main() {
    task_group_context t;
    graph g(t);


    function_node< int, int > f1( g, 1, []( int i ) {  return i; } );


    function_node< int, int > f2( g, 1,
            []( const int i ) -> int {
            cout << "Begin " << i << "\n";
            spin_for(1);
            cout << "End " << i << "\n";
            return i;
            } );


    function_node< int, int > f3( g, 1, []( int i ) {  return i; } );


    make_edge( f1, f2 );
    make_edge( f2, f3 );
    f1.try_put(1);
    f1.try_put(2);
    spin_for(0.1);
    cout<<t.cancel_group_execution()<<endl;
    g.wait_for_all();
    return 0;
}


