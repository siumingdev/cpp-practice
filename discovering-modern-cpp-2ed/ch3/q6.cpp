#include <iostream>
#include <cstddef>
#include <iterator>

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

int main() {
    static_assert(std::forward_iterator<odd_iterator>);
    
    odd_iterator i1, i2;
    std::cout << *i1 << std::endl;
    std::cout << (i1 == i2) << std::endl;
    std::cout << *(i2++) << std::endl;
    std::cout << *(++i2) << std::endl;
    std::cout << *i2 << std::endl;
    i1 = i2;
    std::cout << *i1 << std::endl;
    return 0;
}
