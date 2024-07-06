#include <iostream>
#include <sstream>

template <typename T, typename ...P>
void to_tuple_string_aux(std::ostringstream& oss, T const& x, P const& ...p) {
    if constexpr (sizeof...(P)) {
        oss << x << ',';
        to_tuple_string_aux(oss, p...);
    } else {
        oss << x;
    }
}

template <typename ...P>
std::string to_tuple_string(P const& ...p) {
    std::ostringstream oss;
    oss << '(';
    to_tuple_string_aux(oss, p...);
    oss << ')';
    return oss.str();
}

template <typename ...P>
std::string to_tuple_string_lambda(P const& ...p) {
    std::ostringstream oss;
    oss << '(';

    auto helper = [&oss](auto& self_ref, auto const& x, auto const& ...p_) {
        if constexpr (sizeof...(p_)) {
            oss << x << ',';
            self_ref(self_ref, p_...);
        } else {
            oss << x;
        }
    };
    
    helper(helper, p...);
    
    oss << ')';
    return oss.str();
}

int main() {
    std::cout << to_tuple_string(1.1, "abc", "def") << std::endl;
    std::cout << to_tuple_string_lambda(1.1, "abc", "def") << std::endl;
    return 0;
}
