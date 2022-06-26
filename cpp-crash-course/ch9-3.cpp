#include<iostream>
#include <limits>

template<typename Fn, typename In, size_t Length>
constexpr bool all(Fn function, In (&input)[Length])
{
    for (auto x : input)
    {
        if (!function(x)) return false;
    }
    return true;
}

int main(void)
{
    int data[]{ 100, 200, 300, 400, 500 };
    auto all_gt50 = all([](auto x) { return x > 50; }, data);
    auto all_gt100 = all([](auto x) { return x > 100; }, data);
    std::cout << all_gt50 << std::endl;
    std::cout << all_gt100 << std::endl;
    return 0;
}