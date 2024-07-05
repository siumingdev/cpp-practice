#include <iostream>
#include <sstream>

template <typename T>
std::string to_string(T const& x) {
    std::ostringstream os;
    os << x;
    return os.str();
}

int main() {
    std::cout << to_string(1.1) << std::endl;
    std::cout << to_string("abc") << std::endl;
    return 0;
}
