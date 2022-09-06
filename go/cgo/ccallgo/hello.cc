#include "libhello.h"
#include <string>

int main() {
    GoString gs;
    std::string ss("hello world");
    gs.p = ss.c_str();
    gs.n = ss.length();
    Hello(gs);
    return 0;
}
