#include <cstddef>
#include <iostream>
#include <iterator>
#include <ranges>

class odd_iterator {
public:
    using difference_type = std::ptrdiff_t;
    using value_type = int;

    struct invalid_value{};

    odd_iterator(int value_ = 1) {
        if (!(value_ % 2)) throw invalid_value{};
        value = value_;
    }

    int operator*() const { return value; }

    odd_iterator& operator++() {
        value += 2;
        return *this;
    }

    odd_iterator operator++(int) {
        odd_iterator that = *this;
        value += 2;
        return that;        
    }

    bool operator==(odd_iterator const& rhs) const { return value == rhs.value; }
    bool operator!=(odd_iterator const& rhs) const { return value != rhs.value; }

private:
    int value;
};

class odd_range {
public:
    odd_range(int min_, int max_) : min_iter{min_}, max_iter{max_} {}

    odd_iterator begin() const { return min_iter; }
    odd_iterator end() const { return max_iter; }

private:
    odd_iterator min_iter;
    odd_iterator max_iter;
};

int main() {
    static_assert(std::input_iterator<odd_iterator>);
    static_assert(std::forward_iterator<odd_iterator>);
    static_assert(std::ranges::forward_range<odd_range>);

    std::cout << "Test odd_iterator" << std::endl;
    
    odd_iterator i1, i2;
    std::cout << *i1 << std::endl;
    std::cout << (i1 == i2) << std::endl;
    std::cout << *(i2++) << std::endl;
    std::cout << *(++i2) << std::endl;
    std::cout << *i2 << std::endl;
    i1 = i2;
    std::cout << *i1 << std::endl;
    
    std::cout << "Test odd_range" << std::endl;

    for (int i : odd_range(7, 27))
        std::cout << i << std::endl;
    return 0;
}
