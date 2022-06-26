#include<iostream>
#include <limits>

template<typename Fn, typename In, size_t Length, typename Out>
constexpr Out fold(Fn function, In (&input)[Length], Out initial)
{
    auto cur = initial;
    for (auto x : input)
    {
        cur = function(cur, x);
    }
    return cur;
}

int main(void)
{
    int data[]{ 100, 200, 300, 400, 500 };
    auto sum = fold([](auto x, auto y) { return x + y; }, data, 0);
    std::cout << sum << std::endl;
    auto maximum = fold([](auto x, auto y) { return (x > y) ? x : y; }, data, std::numeric_limits<int>::min());
    std::cout << maximum << std::endl;
    auto minimum = fold([](auto x, auto y) { return (x < y) ? x : y; }, data, std::numeric_limits<int>::max());
    std::cout << minimum << std::endl;
    auto count = fold([](auto acc, auto x) { return (x > 200) ? acc + 1 : acc; }, data, 0);
    std::cout << count << std::endl;
    return 0;
}