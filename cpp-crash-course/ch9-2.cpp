#include<iostream>
#include<string.h>
#include<unordered_map>

template<typename K, typename V>
std::ostream &operator<<(std::ostream &os,
                        const std::unordered_map<K, V> &m) {
    for (const std::pair<K, V> &p: m) {
        os << "{" << p.first << ": " << p.second << "}\n";
    }
    return os;
}

int main(int argc, char* argv[])
{
    std::unordered_map<size_t, size_t> counts;
    size_t size_of_argv {};
    for (int i {}; i < argc; i++)
    {
        size_of_argv = strlen(argv[i]);
        std::cout << argv[i] << " " << size_of_argv << std::endl;
        if (!counts.contains(size_of_argv))
        {
            counts.emplace(size_of_argv, 1);
        }
        else
        {
            counts.at(size_of_argv) += 1;
        }
    }
    std::cout << counts;
    return 0;
}