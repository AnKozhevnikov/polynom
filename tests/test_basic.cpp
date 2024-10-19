#include "polynom.hpp"

#include <map>
#include <cassert>

int main() {
    std::map<std::map<char, int>, int> m;
    m[{{'x', 2}}] = 1;
    m[{{'y', 1}}] = 2;
    Polynom<int> p1(m);
    int ans = p1.apply(std::map<char, int>{
        {'x', 2},
        {'y', 3}
    });
    assert(ans == 10);
    return 0;
}