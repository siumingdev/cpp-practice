#include <memory>
#include <iostream>
#include <vector>
#include <boost/type_index.hpp>

template< class T, class... Args >
std::unique_ptr<T> my_make_unique( Args&&... args ) {
    return std::unique_ptr<T>(new T{std::forward<Args>(args)...});
}

int main() {
    auto v = my_make_unique<std::vector<double>>(1.0, 2.0, 3.0);
    std::cout << (*v)[1] << std::endl;

    auto get_type_name = [](auto const& x){ return boost::typeindex::type_id_with_cvr<decltype(x)>().pretty_name(); };
    std::cout << get_type_name(v);
    return 0;
}
