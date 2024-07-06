#include <algorithm>
#include <iostream>
#include <vector>

auto find_first_multiple(std::vector<int> const &v, int i) {
    return std::ranges::find_if(v, [&i](int x){ return x % i == 0; });
}

int main() {
    std::vector<int> vi{12, 3, 15, 5, 7, 9};
    for (int i = 2; i < 10; ++i) {
        auto it = find_first_multiple(vi, i);
        if (it != vi.end())
            std::cout << "The first multiple of " << i << " is " << *it << std::endl;
        else
            std::cout << "There is no multiple of " << i << std::endl;
    }
    return 0;
}
