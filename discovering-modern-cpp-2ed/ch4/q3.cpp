#include <algorithm>
#include <iostream>
#include <map>
#include <optional>

std::optional<unsigned long> find_number_by_name(std::map<std::string, unsigned long> const& book, std::string const& name) {
    if (book.contains(name))
        return book.at(name);
    return std::nullopt;
}

std::optional<std::string> find_name_by_number(std::map<std::string, unsigned long> const& book, unsigned long number) {
    if (auto it = std::ranges::find_if(book, [&number](auto p){ return p.second == number; }); it != book.end())
        return it->first;
    return std::nullopt;
}

int main() {
    std::map<std::string, unsigned long> book{
        {"Peter", 69031234},
        {"Paul", 62103414},
        {"Mary", 91348715},
        {"Mike", 52310940},
    };

    std::cout << find_number_by_name(book, "Peter").value() << std::endl;
    std::cout << find_number_by_name(book, "Peter1").value_or(0) << std::endl;

    std::cout << find_name_by_number(book, 62103414).value() << std::endl;
    std::cout << find_name_by_number(book, 999).value_or("not found") << std::endl;
    return 0;
}
