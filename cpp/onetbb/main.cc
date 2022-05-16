#include <vector>
#include <iostream>

#include "oneapi/tbb.h"
#include "oneapi/tbb/task.h"

using namespace oneapi::tbb;
using namespace oneapi::tbb::task;
using namespace std;

vector<int> Data;

struct Update{
    void operator() (const blocked_range<int>& r) const{
        for(int i = r.begin(); i != r.end(); ++i) {
            if (i < Data.size()) {
                ++Data[i];
            }else {
                if (current_context()->cancel_group_execution()) {
                    cout<< "Index " << i << "caused cancellation"<<endl;
                }
                return;
            }
        }
    }
};

int main() {
    Data.resize(1000);
    parallel_for(blocked_range<int>(0, 2000), Update());
    return 0;
}
