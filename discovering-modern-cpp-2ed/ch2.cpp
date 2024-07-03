#include <vector>
#include <iostream>
#include <numeric>

class Polynomial
{
public:
    Polynomial(size_t degree) : coeff{std::vector<double>(degree)} {}
    Polynomial(std::initializer_list<double> coeff_) : coeff{coeff_} {}
    Polynomial(Polynomial const& that) = default;
    Polynomial(Polynomial&& that) : coeff{std::move(that.coeff)} {}
    ~Polynomial() { coeff.clear(); }

    Polynomial& operator=(Polynomial&& that)
    {
        if (this == &that) return *this;
        coeff = std::move(that.coeff);
        std::cout << "Move" << std::endl;
        return *this;
    }

    Polynomial& operator=(std::initializer_list<double> coeff_)
    {
        coeff.clear();
        for (double c : coeff_) {
            coeff.push_back(c);
        }
        std::cout << "initializer_list" << std::endl;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Polynomial& polynomial);
    std::vector<double> coeff;
};

std::ostream& operator<<(std::ostream& os, const Polynomial& polynomial)
{
    bool printed_anything = false;
    for (size_t i = 0; i < polynomial.coeff.size(); i++) {
        if (double c = polynomial.coeff[i]; c != 0) {
            if (printed_anything && c > 0) os << '+';
            printed_anything = true;
            if (c == 1) {
            } else if (c == -1) {
                os << '-';
            } else {
                os << c;
            }
            if (i > 0) os << 'x';
            if (i > 1) os << '^' << i;
        }
    }
    if (!printed_anything) os << '0';
    return os;
}

class Rational
{
public:
    Rational(int numerator_, int denominator_ = 1) : numerator{numerator_}, denominator{denominator_} { normalize(); }

    int const get_numerator() const { return numerator; }
    int const get_denominator() const { return denominator; }
    friend std::ostream& operator<<(std::ostream& os, const Rational& r);
    friend Rational operator+(Rational r1, Rational r2);
    friend Rational operator-(Rational r1, Rational r2);
    friend Rational operator*(Rational r1, Rational r2);
    friend Rational operator/(Rational r1, Rational r2);

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
        int _gcd = std::gcd(numerator, denominator);
        denominator /= _gcd;
        numerator /= _gcd;
    }
};

std::ostream& operator<<(std::ostream& os, Rational const& r)
{
    os << r.get_numerator();
    if (auto d = r.get_denominator(); d != 1) {
        os << '/' << d;
    }
    return os;
}

Rational operator+(Rational r1, Rational r2)
{
    return Rational(r1.numerator * r2.denominator + r2.numerator * r1.denominator, r1.denominator * r2.denominator);
}

Rational operator-(Rational r1, Rational r2)
{
    return Rational(r1.numerator * r2.denominator - r2.numerator * r1.denominator, r1.denominator * r2.denominator);
}

Rational operator*(Rational r1, Rational r2)
{
    return Rational(r1.numerator * r2.numerator, r1.denominator * r2.denominator);
}

Rational operator/(Rational r1, Rational r2)
{
    return Rational(r1.numerator * r2.denominator, r1.denominator * r2.numerator);
}

Polynomial make_polynomial(double c1, double c0)
{
    return Polynomial{c0, c1};
}

int main() {
    Polynomial y1{3, 2};
    std::cout << y1 << std::endl;

    y1 = make_polynomial(4, 5);
    std::cout << y1 << std::endl;

    y1 = {6, 7};
    std::cout << y1 << std::endl;

    Rational r1{6, -5}, r2{10, 7}, r3{r1/r2}, r4{r1+r2};
    std::cout << r1 << std::endl;
    std::cout << r2 << std::endl;
    std::cout << r3 << std::endl;
    std::cout << r4 << std::endl;

    r3 += 3;
    std::cout << r3 << std::endl;
    return 0;
}
