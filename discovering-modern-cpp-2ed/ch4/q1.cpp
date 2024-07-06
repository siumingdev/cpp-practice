#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

struct compare_by_magnitude {
    bool operator()(double a, double b) { return std::abs(a) < std::abs(b); }
};

int main() {
    std::vector<double> v{-9.3, -7.4, -3.8, -0.4, 1.3, 3.9, 5.4, 8.2};
    std::ranges::sort(v, [](double a, double b){ return std::abs(a) < std::abs(b); });
    for (auto x : v)
        std::cout << x << std::endl;
    
    std::vector<double> v2{-9.3, -7.4, -3.8, -0.4, 1.3, 3.9, 5.4, 8.2};
    std::ranges::sort(v2, compare_by_magnitude{});
    for (auto x : v2)
        std::cout << x << std::endl;
    return 0;
}
