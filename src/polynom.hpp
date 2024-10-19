#pragma once

#include <iostream>
#include <map>
#include <string>
#include <string_view>
#include <cmath>
#include <stdexcept>

template <typename T>
class Polynom {
public:
    Polynom(T val = T());
    Polynom(Polynom &other);
    Polynom(Polynom &&other);
    Polynom &operator=(Polynom &other);
    Polynom &operator=(Polynom &&other);
    ~Polynom() = default;

    Polynom(std::map<std::map<char, int>, T> otherCoef);

    Polynom(std::string_view str);
    Polynom(const char *str);

    template <typename U>
    U apply(std::map<char, U> m) const;

    template <typename U>
    friend Polynom<U> operator+(const Polynom<U> &lhs, const Polynom<U> &rhs);

    template <typename U>
    friend Polynom<U> operator-(const Polynom<U> &lhs, const Polynom<U> &rhs);

    template <typename U>
    friend Polynom<U> operator*(const Polynom<U> &lhs, const Polynom<U> &rhs);

    Polynom &operator+=(const Polynom &other);
    Polynom &operator-=(const Polynom &other);
    Polynom &operator*=(const Polynom &other);

    template <typename U>
    friend Polynom<U> operator*(const Polynom<U> &lhs, const U &rhs);

    template <typename U>
    friend Polynom<U> operator*(const U &lhs, const Polynom<U> &rhs);

    Polynom &operator*=(const T &other);

    template <typename U>
    friend Polynom<U> operator+(const Polynom<U> &lhs, const U &rhs);

    template <typename U>
    friend Polynom<U> operator+(const U &lhs, const Polynom<U> &rhs);

    Polynom &operator+=(const T &other);

    template <typename U>
    friend Polynom<U> operator-(const Polynom<U> &lhs, const U &rhs);

    template <typename U>
    friend Polynom<U> operator-(const U &lhs, const Polynom<U> &rhs);

    Polynom &operator-=(const T &other);

    Polynom operator-() const;

    template <typename U>
    friend Polynom<U> operator^(const Polynom<U> lhs, const unsigned long long rhs);

    Polynom &operator^=(const unsigned long long n);

private:
    void clean();
    std::map<std::map<char, int>, T> coef;
};

template <typename T>
Polynom<T>::Polynom(T val) {
    if (val != T()) {
        coef[{}] = val;
    }
    clean();
}

template <typename T>
Polynom<T>::Polynom(Polynom &other) : coef(other.coef) {}

template <typename T>
Polynom<T>::Polynom(Polynom &&other) : coef(std::move(other.coef)) {}

template <typename T>
Polynom<T> &Polynom<T>::operator=(Polynom &other) {
    if (this != &other) {
        coef = other.coef;
    }
    return *this;
}

template <typename T>
Polynom<T> &Polynom<T>::operator=(Polynom &&other) {
    if (this != &other) {
        coef = std::move(other.coef);
    }
    return *this;
}

template <typename T>
Polynom<T>::Polynom(std::map<std::map<char, int>, T> otherCoef) : coef(otherCoef) {}

template <typename T>
Polynom<T>::Polynom(std::string_view str) {
    // TODO: Implement this
}

template <typename T>
Polynom<T>::Polynom(const char *str) : Polynom(std::string_view(str)) {}

template <typename T>
T power(T base, unsigned long long exp) {
    if (exp == 1) {
        return base;
    }
    else {
        T temp = power(base, exp/2);
        if (exp % 2 == 0) {
            return temp * temp;
        }
        else {
            return base * temp * temp;
        }
    }
}

template <typename T>
template <typename U>
U Polynom<T>::apply(std::map<char, U> m) const {
    U result = U();
    for (auto it = coef.begin(); it != coef.end(); ++it) {
        U term = 1;
        for (auto jt = it->first.begin(); jt != it->first.end(); ++jt) {
            if (m.find(jt->first) == m.end()) {
                throw std::invalid_argument("Variable not found in map");
            }
            term *= power(m[jt->first], jt->second);
        }
        term *= it->second;
        result += term;
    }
    return result;
}

template <typename T>
Polynom<T> operator+(const Polynom<T> &lhs, const Polynom<T> &rhs) {
    lhs+=rhs;
    return lhs;
}

template <typename T>
Polynom<T> operator-(const Polynom<T> &lhs, const Polynom<T> &rhs) {
    lhs-=rhs;
}

template <typename T>
Polynom<T> operator*(const Polynom<T> &lhs, const Polynom<T> &rhs) {
    lhs*=rhs;
    return lhs;
}

template <typename T>
Polynom<T> &Polynom<T>::operator+=(const Polynom &other) {
    for (auto it = other.coef.begin(); it != other.coef.end(); ++it) {
        if (coef.find(it->first) == coef.end()) {
            coef[it->first] = it->second;
        } else {
            coef[it->first] += it->second;
        }
    }
    clean();
    return *this;
}

template <typename T>
Polynom<T> &Polynom<T>::operator-=(const Polynom &other) {
    for (auto it = other.coef.begin(); it != other.coef.end(); ++it) {
        if (coef.find(it->first) == coef.end()) {
            coef[it->first] = -it->second;
        } else {
            coef[it->first] -= it->second;
        }
    }
    clean();
    return *this;
}

template <typename T>
Polynom<T> &Polynom<T>::operator*=(const Polynom &other) {
    std::map<std::map<char, int>, T> temp;
    for (auto it1 = coef.begin(); it1 != coef.end(); ++it1) {
        for (auto it2 = other.coef.begin(); it2 != other.coef.end(); ++it2) {
            std::map<char, int> new_key = it1->first;
            for (auto jt = it2->first.begin(); jt != it2->first.end(); ++jt) {
                if (new_key.find(jt->first) == new_key.end()) {
                    new_key[jt->first] = jt->second;
                } else {
                    new_key[jt->first] += jt->second;
                }
            }
            if (temp.find(new_key) == temp.end()) {
                temp[new_key] = it1->second * it2->second;
            } else {
                temp[new_key] += it1->second * it2->second;
            }
        }
    }
    coef = temp;
    clean();
    return *this;
}

template <typename T>
Polynom<T> operator*(const Polynom<T> &lhs, const T &rhs) {
    lhs*=rhs;
    return lhs;
}

template <typename T>
Polynom<T> operator*(const T &lhs, const Polynom<T> &rhs) {
    rhs*=lhs;
    return rhs;
}

template <typename T>
Polynom<T> &Polynom<T>::operator*=(const T &other) {
    for (auto it = coef.begin(); it != coef.end(); ++it) {
        it->second *= other;
    }
}

template <typename T>
Polynom<T> operator+(const Polynom<T> &lhs, const T &rhs) {
    lhs+=rhs;
    return lhs;
}

template <typename T>
Polynom<T> operator+(const T &lhs, const Polynom<T> &rhs) {
    rhs+=lhs;
    return rhs;
}

template <typename T>
Polynom<T> &Polynom<T>::operator+=(const T &other) {
    if (coef.find({}) == coef.end()) {
        coef[{}] = other;
    } else {
        coef[{}] += other;
    }
}

template <typename T>
Polynom<T> operator-(const Polynom<T> &lhs, const T &rhs) {
    lhs-=rhs;
    return lhs;
}

template <typename T>
Polynom<T> operator-(const T &lhs, const Polynom<T> &rhs) {
    rhs-=lhs;
    return rhs;
}

template <typename T>
Polynom<T> &Polynom<T>::operator-=(const T &other) {
    if (coef.find({}) == coef.end()) {
        coef[{}] = -other;
    } else {
        coef[{}] -= other;
    }
}

template <typename T>
Polynom<T> operator^(const Polynom<T> lhs, const unsigned long long rhs) {
    lhs^=rhs;
    return lhs;
}

template <typename T>
Polynom<T> &Polynom<T>::operator^=(const unsigned long long n) {
    *this = power(*this, n);
    return *this;
}

template <typename T>
Polynom<T> Polynom<T>::operator-() const {
    Polynom result = *this;
    for (auto it = result.coef.begin(); it != result.coef.end(); ++it) {
        it->second = -it->second;
    }
    return result;
}

template <typename T>
void Polynom<T>::clean() {
    for (auto it = coef.begin(); it != coef.end();) {
        if (it->second == T()) {
            coef.erase(it++);
        }
        else {
            ++it;
        }
    }
}
