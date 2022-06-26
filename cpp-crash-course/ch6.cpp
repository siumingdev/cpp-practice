#include <iostream>
#include <unordered_map>
#include <concepts>
#include <type_traits>


template<typename K, typename V>
std::ostream &operator<<(std::ostream &os,
                        const std::unordered_map<K, V> &m) {
    for (const std::pair<K, V> &p: m) {
        os << "{" << p.first << ": " << p.second << "}\n";
    }
    return os;
}

template<typename T>
concept Integer = std::is_integral<T>::value;

template<Integer T, size_t Length>
T mode(T const (&values)[Length])
{
    auto counts = std::unordered_map<T, size_t> {};
    for (auto i = 0; i < Length; i++)
    {
        if (!counts.contains(values[i]))
        {
            counts.emplace(values[i], 1);
        }
        else
        {
            counts.at(values[i]) += 1;
        }
    }

    size_t max_count {0};
    T max_value {0};
    for (auto& [value, count] : counts)
    {
        if (count > max_count)
        {
            max_value = value;
            max_count = count;
        }
    }

    return max_value;
}

template<typename T, size_t Length>
double mean(T const (&values)[Length])
{
    double sum {0};
    for (auto value : values)
    {
        sum += value;
    }
    return sum / Length;
}

template<typename Id>
class Bank
{
public:
    Bank() : store{} {}
    
    void make_transfer(Id from, Id to, double amount)
    {
        set_amount(from, get_amount(from) - amount);
        set_amount(to, get_amount(to) + amount);

        std::cout << store << std::endl;
    }

    double get_amount(Id const& id) const
    {
        return store.at(id);
    }

    void set_amount(Id const& id, double amount)
    {
        store[id] = amount;
    }

private:
    std::unordered_map<Id, double> store;
};

int main(void)
{
    int values[] {1, 2, 2, 4};
    std::cout << mode(values) << std::endl;
    std::cout << mean(values) << std::endl;

    Bank<long> bank {};

    bank.set_amount(1, 1000);
    bank.set_amount(2, 2000);
    bank.make_transfer(1, 2, 300);
    std::cout << bank.get_amount(1) << std::endl;
    std::cout << bank.get_amount(2) << std::endl;
    return 0;
}