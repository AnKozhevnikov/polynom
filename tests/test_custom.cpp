#include "polynom.hpp"

#include <cassert>
#include <map>
#include <string>

class N5
{
  public:
    N5() : val(0)
    {
    }
    N5(unsigned int val) : val(val % 5)
    {
    }
    N5(const N5 &other) : val(other.val)
    {
    }
    N5(N5 &&other) : val(other.val)
    {
    }
    N5 &operator=(const N5 &other)
    {
        if (this != &other)
        {
            val = other.val;
        }
        return *this;
    }
    N5 &operator=(N5 &&other)
    {
        if (this != &other)
        {
            val = other.val;
        }
        return *this;
    }
    ~N5() = default;

    N5 operator+=(const N5 &other)
    {
        val = (val + other.val) % 5;
        return *this;
    }
    N5 operator-=(const N5 &other)
    {
        val = (val + 5 - other.val) % 5;
        return *this;
    }
    N5 operator*=(const N5 &other)
    {
        val = (val * other.val) % 5;
        return *this;
    }

    friend N5 operator+(N5 lhs, const N5 &rhs)
    {
        lhs += rhs;
        return lhs;
    }
    friend N5 operator-(N5 lhs, const N5 &rhs)
    {
        lhs -= rhs;
        return lhs;
    }
    friend N5 operator*(N5 lhs, const N5 &rhs)
    {
        lhs *= rhs;
        return lhs;
    }

    bool operator==(const N5 &other) const
    {
        return val == other.val;
    }

    N5 operator-() const
    {
        return N5((5 - val)%5);
    }

  private:
    unsigned int val;
};

N5 n5parser(const std::string &str)
{
    if (str == "zero")
        return N5(0);
    if (str == "one")
        return N5(1);
    if (str == "two")
        return N5(2);
    if (str == "three")
        return N5(3);
    if (str == "four")
        return N5(4);
    throw std::invalid_argument("Invalid argument");
}

class Matrix2x2
{
  public:
    Matrix2x2() : data{{N5(0), N5(0)}, {N5(0), N5(0)}}
    {
    }
    Matrix2x2(N5 a, N5 b, N5 c, N5 d) : data{{a, b}, {c, d}}
    {
    }
    Matrix2x2(unsigned int a)
    {
        data[0][0] = N5(a % 5);
        data[0][1] = N5(0);
        data[1][0] = N5(0);
        data[1][1] = N5(a % 5);
    }
    Matrix2x2(const Matrix2x2 &other) : data{{other.data[0][0], other.data[0][1]}, {other.data[1][0], other.data[1][1]}}
    {
    }
    Matrix2x2(Matrix2x2 &&other) : data{{other.data[0][0], other.data[0][1]}, {other.data[1][0], other.data[1][1]}}
    {
    }
    Matrix2x2 &operator=(const Matrix2x2 &other)
    {
        if (this != &other)
        {
            data[0][0] = other.data[0][0];
            data[0][1] = other.data[0][1];
            data[1][0] = other.data[1][0];
            data[1][1] = other.data[1][1];
        }
        return *this;
    }
    Matrix2x2 &operator=(Matrix2x2 &&other)
    {
        if (this != &other)
        {
            data[0][0] = other.data[0][0];
            data[0][1] = other.data[0][1];
            data[1][0] = other.data[1][0];
            data[1][1] = other.data[1][1];
        }
        return *this;
    }
    ~Matrix2x2() = default;

    Matrix2x2 operator+=(const Matrix2x2 &other)
    {
        data[0][0] += other.data[0][0];
        data[0][1] += other.data[0][1];
        data[1][0] += other.data[1][0];
        data[1][1] += other.data[1][1];
        return *this;
    }
    Matrix2x2 operator-=(const Matrix2x2 &other)
    {
        data[0][0] -= other.data[0][0];
        data[0][1] -= other.data[0][1];
        data[1][0] -= other.data[1][0];
        data[1][1] -= other.data[1][1];
        return *this;
    }
    friend Matrix2x2 operator+(Matrix2x2 lhs, const Matrix2x2 &rhs)
    {
        lhs += rhs;
        return lhs;
    }
    friend Matrix2x2 operator-(Matrix2x2 lhs, const Matrix2x2 &rhs)
    {
        lhs -= rhs;
        return lhs;
    }
    Matrix2x2 operator*=(const Matrix2x2 &other)
    {
        N5 a = data[0][0] * other.data[0][0] + data[0][1] * other.data[1][0];
        N5 b = data[0][0] * other.data[0][1] + data[0][1] * other.data[1][1];
        N5 c = data[1][0] * other.data[0][0] + data[1][1] * other.data[1][0];
        N5 d = data[1][0] * other.data[0][1] + data[1][1] * other.data[1][1];
        data[0][0] = a;
        data[0][1] = b;
        data[1][0] = c;
        data[1][1] = d;
        return *this;
    }
    friend Matrix2x2 operator*(Matrix2x2 lhs, const Matrix2x2 &rhs)
    {
        lhs *= rhs;
        return lhs;
    }
    Matrix2x2 operator*=(const N5 &other)
    {
        data[0][0] *= other;
        data[0][1] *= other;
        data[1][0] *= other;
        data[1][1] *= other;
        return *this;
    }
    friend Matrix2x2 operator*(Matrix2x2 lhs, const N5 &rhs)
    {
        lhs *= rhs;
        return lhs;
    }
    friend Matrix2x2 operator*(const N5 lhs, Matrix2x2 rhs)
    {
        rhs *= lhs;
        return rhs;
    }

    bool operator==(const Matrix2x2 &other) const
    {
        return data[0][0] == other.data[0][0] && data[0][1] == other.data[0][1] && data[1][0] == other.data[1][0] && data[1][1] == other.data[1][1];
    }

    Matrix2x2 operator-() const
    {
        return Matrix2x2(-data[0][0], -data[0][1], -data[1][0], -data[1][1]);
    }

  private:
    N5 data[2][2];
};

int main() {
    // Test 1: Custom polynomial
    {
        Polynom<N5> p1("[one]x^2+[two]y+[four]", n5parser);
        Matrix2x2 mx(N5(1), N5(2), N5(3), N5(4));
        Matrix2x2 my(N5(4), N5(3), N5(2), N5(1));
        Matrix2x2 res(N5(4), N5(1), N5(4), N5(3));
        Matrix2x2 ans = p1.apply(std::map<char, Matrix2x2>{
            {'x', mx},
            {'y', my}
        });
        assert(ans == res);
    }
    return 0;
}