#include <iostream>
#include <sstream>

template <typename T, typename ...P>
std::string to_tuple_string(T const& t, P const& ...p) {
    std::ostringstream oss;
    oss << '(' << t;
    ((oss << ',' << p), ...);  // because `,` is a fold-exp supported binary op, free func signature: `T2& operator,(const T &a, T2 &b);`
    oss << ')';
    return oss.str();
}

int main() {
    std::cout << to_tuple_string(1.1, "abc", "def") << std::endl;
    return 0;
}
