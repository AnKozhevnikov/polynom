#include "polynom.hpp"

#include <map>
#include <cassert>
#include <string>

int main() {
    Polynom<int> p1("x^2+[2]y+[5]", pconverter::to_int);
    int ans = p1.apply(std::map<char, int>{
        {'x', 2},
        {'y', 3}
    });
    assert(ans == 15);
    return 0;
}