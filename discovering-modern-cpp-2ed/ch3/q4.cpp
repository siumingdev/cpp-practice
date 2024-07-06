#include <concepts>
#include <iostream>
#include <numeric>

template<std::signed_integral T>
class Rational
{
public:
    Rational(T numerator_, T denominator_ = 1) : numerator{numerator_}, denominator{denominator_} { normalize(); }

    T const get_numerator() const { return numerator; }
    T const get_denominator() const { return denominator; }

    Rational& operator+=(Rational const& r2)
    {
        numerator = numerator * r2.denominator + r2.numerator * denominator;
        denominator = denominator * r2.denominator;
        normalize();
        return *this;
    }

    Rational& operator-=(Rational const& r2)
    {
        numerator = numerator * r2.denominator - r2.numerator * denominator;
        denominator = denominator * r2.denominator;
        normalize();
        return *this;
    }

    Rational& operator*=(Rational const& r2)
    {
        numerator *= r2.numerator;
        denominator *= r2.denominator;
        normalize();
        return *this;
    }

    Rational& operator/=(Rational const& r2)
    {
        numerator *= r2.denominator;
        denominator *= r2.numerator;
        normalize();
        return *this;
    }

private:
    int numerator;
    int denominator;

    void normalize()
    {
        if (denominator < 0) {
            denominator *= -1;
            numerator *= -1;
        }
        T _gcd = std::gcd(numerator, denominator);
        denominator /= _gcd;
        numerator /= _gcd;
    }
};

template<std::signed_integral T>
std::ostream& operator<<(std::ostream& os, Rational<T> const& r)
{
    os << r.get_numerator();
    if (auto d = r.get_denominator(); d != 1) {
        os << '/' << d;
    }
    return os;
}

template<std::signed_integral T>
auto operator+(Rational<T> r1, Rational<T> r2)
{
    return Rational(r1.get_numerator() * r2.get_denominator() + r2.get_numerator() * r1.get_denominator(), r1.get_denominator() * r2.get_denominator());
}

template<std::signed_integral T>
auto operator-(Rational<T> r1, Rational<T> r2)
{
    return Rational(r1.get_numerator() * r2.get_denominator() - r2.get_numerator() * r1.get_denominator(), r1.get_denominator() * r2.get_denominator());
}

template<std::signed_integral T>
auto operator*(Rational<T> r1, Rational<T> r2)
{
    return Rational(r1.get_numerator() * r2.get_numerator(), r1.get_denominator() * r2.get_denominator());
}

template<std::signed_integral T>
auto operator/(Rational<T> r1, Rational<T> r2)
{
    return Rational(r1.get_numerator() * r2.get_denominator(), r1.get_denominator() * r2.get_numerator());
}

int main() {
    Rational r1{6, -5}, r2{10, 7}, r3{r1/r2}, r4{r1+r2};
    std::cout << r1 << std::endl;
    std::cout << r2 << std::endl;
    std::cout << r3 << std::endl;
    std::cout << r4 << std::endl;

    r3 += 3;
    std::cout << r3 << std::endl;
    return 0;
}
