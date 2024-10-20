#include "polynom.hpp"

#include <map>
#include <cassert>
#include <string>

int main() {
    // Test 1: Simple polynomial
    {
        Polynom<int> p1("x^2+[2]y+[5]", pconverter::to_int);
        int ans = p1.apply(std::map<char, int>{
            {'x', 2},
            {'y', 3}
        });
        assert(ans == 15);
    }

    // Test 2: Polynomial with negative coefficients
    {
        Polynom<int> p2("x^2-[2]y-[5]", pconverter::to_int);
        int ans = p2.apply(std::map<char, int>{
            {'x', 2},
            {'y', 3}
        });
        assert(ans == -7);
    }

    // Test 3: Polynomial with multiple variables
    {
        Polynom<int> p3("x^2+y^2+z^2", pconverter::to_int);
        int ans = p3.apply(std::map<char, int>{
            {'x', 1},
            {'y', 2},
            {'z', 3}
        });
        assert(ans == 14);
    }

    // Test 4: Polynomial with zero coefficients
    {
        Polynom<int> p4("x^2+[0]y+[0]", pconverter::to_int);
        int ans = p4.apply(std::map<char, int>{
            {'x', 3},
            {'y', 4}
        });
        assert(ans == 9);
    }

    // Test 5: Polynomial with no variables
    {
        Polynom<int> p5("[5]", pconverter::to_int);
        int ans = p5.apply(std::map<char, int>{});
        assert(ans == 5);
    }

    // Test 6: Polynomial with higher powers
    {
        Polynom<int> p6("x^3+y^3", pconverter::to_int);
        int ans = p6.apply(std::map<char, int>{
            {'x', 2},
            {'y', 3}
        });
        assert(ans == 35);
    }

    // Test 7: Polynomial with mixed terms
    {
        Polynom<int> p7("x^2+y^2+[2]xy+[1]", pconverter::to_int);
        int ans = p7.apply(std::map<char, int>{
            {'x', 1},
            {'y', 2}
        });
        assert(ans == 10);
    }

    // Test 8: Polynomial with fractional coefficients
    {
        Polynom<double> p8("x^2+[1.5]y+[2.5]", pconverter::to_double);
        double ans = p8.apply(std::map<char, double>{
            {'x', 2},
            {'y', 2}
        });
        assert(ans == 9.5); // Assuming fractional part is truncated
    }

    // Test 9: Polynomial with large coefficients and variables
    {
        Polynom<int> p9("x^10+y^10", pconverter::to_int);
        int ans = p9.apply(std::map<char, int>{
            {'x', 2},
            {'y', 2}
        });
        assert(ans == 2048);
    }

    // Test 10: Polynomial with strange variable order
    {
        Polynom<int> p10("xyxyx", pconverter::to_int);
        int ans = p10.apply(std::map<char, int>{
            {'x', 3},
            {'y', 2}
        });
        assert(ans == 108);
    }

    // Test 11: constant polynomial
    {
        Polynom<int> p11("[5]", pconverter::to_int);
        int ans = p11.apply(std::map<char, int>{
            {'x', 3},
            {'y', 2}
        });
        assert(ans == 5);
    }

    // Test 12: adding constant to polynomial
    {
        Polynom<int> p12_0("x^2+y^2", pconverter::to_int);
        Polynom<int> p12_1("[5]", pconverter::to_int);
        Polynom<int> p12_2 = p12_0 + p12_1;
        int ans = p12_2.apply(std::map<char, int>{
            {'x', 3},
            {'y', 2}
        });
        assert(ans == 18);
    }

    // Test 13: multiplying constant to polynomial
    {
        Polynom<int> p13_0("x^2+y^2", pconverter::to_int);
        Polynom<int> p13_1("[5]", pconverter::to_int);
        Polynom<int> p13_2 = p13_0 * p13_1;
        int ans = p13_2.apply(std::map<char, int>{
            {'x', 3},
            {'y', 2}
        });
        assert(ans == 65);
    }

    // Test 14: subtracting constant from polynomial
    {
        Polynom<int> p14_0("x^2+y^2", pconverter::to_int);
        Polynom<int> p14_1("[5]", pconverter::to_int);
        Polynom<int> p14_2 = p14_0 - p14_1;
        int ans = p14_2.apply(std::map<char, int>{
            {'x', 3},
            {'y', 2}
        });
        assert(ans == 8);
    }

    // Test 15: adding polynomials
    {
        Polynom<int> p15_0("x^2+y^2", pconverter::to_int);
        Polynom<int> p15_1("x^2-y^2", pconverter::to_int);
        Polynom<int> p15_2 = p15_0 + p15_1;
        int ans = p15_2.apply(std::map<char, int>{
            {'x', 3},
            {'y', 2}
        });
        assert(ans == 18);
    }

    // Test 16: subtracting polynomials
    {
        Polynom<int> p16_0("x^2+y^2", pconverter::to_int);
        Polynom<int> p16_1("x^2-y^2", pconverter::to_int);
        Polynom<int> p16_2 = p16_0 - p16_1;
        int ans = p16_2.apply(std::map<char, int>{
            {'x', 3},
            {'y', 2}
        });
        assert(ans == 8);
    }

    // Test 17: multiplying polynomials
    {
        Polynom<int> p17_0("x^2+y^2", pconverter::to_int);
        Polynom<int> p17_1("x^2-y^2", pconverter::to_int);
        Polynom<int> p17_2 = p17_0 * p17_1;
        int ans = p17_2.apply(std::map<char, int>{
            {'x', 3},
            {'y', 2}
        });
        assert(ans == 65);
    }

    return 0;
}