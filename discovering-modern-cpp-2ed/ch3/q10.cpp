#include <concepts>
#include <cmath>
#include <functional>
#include <iostream>
#include <boost/type_index.hpp>

template <typename Func, typename T>
concept UnaryFunction = requires(Func f, T t) {
    { f(t) } -> std::same_as<T>;
};

template<std::floating_point T, typename F>
    requires UnaryFunction<F, T>
T trapezoid(F const& f, T a, T b, size_t n = 1000) {
    T h = (b - a) / n;
    T result = (f(a) + f(b)) / 2;
    for (size_t i = 1; i < n; ++i)
        result += f(a + i * h);
    result *= h;
    return result;
}

double exp3f(double x) {
    return std::exp(3.0 * x);
}

struct exp3t {
    double operator() (double x) const {
        return std::exp(3.0 * x);
    }
};

template<std::floating_point T>
auto sin_t = static_cast<T(*)(T)>(&std::sin);

double constexpr default_step = 0.000000001;

template<std::floating_point T, typename F>
    requires UnaryFunction<F, T>
class derivative {
public:
    derivative(F const& f, T const& h) : f{f}, h{h} {}

    T operator()(T const& x) const {
        return (f(x+h) - f(x)) / h;
    }
private:
    F const& f;
    T h;
};

int main() {
    std::cout << trapezoid(exp3f, 0.0, 4.0) << std::endl;
    std::cout << trapezoid(exp3t{}, 0.0, 4.0) << std::endl;

    auto sin_cos = [](double x) { return (x < 1) ? std::sin(x) : std::cos(x); };
    std::cout << trapezoid(sin_cos, 0.0, 4.0) << std::endl;

    std::cout << trapezoid(sin_t<double>, 0.0, 2.0) << std::endl;

    auto get_type_name = [](auto const& x){ return boost::typeindex::type_id_with_cvr<decltype(x)>().pretty_name(); };
    std::cout << get_type_name(get_type_name) << std::endl;
    
    auto d_exp3f = derivative{exp3f, default_step};
    std::cout << get_type_name(d_exp3f) << std::endl;
    std::cout << trapezoid(d_exp3f, 0.0, 4.0) << std::endl;
    std::cout << exp3f(4.0) - exp3f(0.0) << std::endl;
    return 0;
}
