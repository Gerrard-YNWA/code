#include "oneapi/tbb/concurrent_hash_map.h"
#include "oneapi/tbb/blocked_range.h"
#include "oneapi/tbb/parallel_for.h"
#include <string>

using namespace oneapi::tbb;
using namespace std;

struct MyHashCompare {
    static size_t hash(const string& x) {
        size_t h = 0;
        for(const char* s= x.c_str(); *s; ++s) {
            h = (h*17)^*s;
        }
        return h;
    }

    static bool equal(const string& x, const string& y) {
        return x == y;
    }
};

typedef concurrent_hash_map<string, int, MyHashCompare> StringTable;

struct Tally {
    StringTable& table;
    Tally(StringTable& table_): table(table_) {}
    void operator() (const blocked_range<string*> range) const {
        for (string* p = range.begin(); p != range.end(); ++p) {
            StringTable::accessor a;
            table.insert(a, *p);
            a->second += 1;
        }
    }
};

const size_t N=1000000;
string Data[N];

void CountOccurrences() {
    StringTable table;
    parallel_for(blocked_range<string*>(Data, Data+N, 1000), Tally(table));

    for (StringTable::iterator i = table.begin(); i!=table.end(); ++i) {
        printf("%s %d\n", i->first.c_str(), i->second);
    }
}

int main() {
    CountOccurrences();
}
