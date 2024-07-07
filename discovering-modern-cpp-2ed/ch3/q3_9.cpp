#include <exception>
#include <initializer_list>
#include <iostream>
#include <vector>

template<typename T, size_t N = 4096>
class Stack 
{
public:
    struct overflow : std::exception {};
    struct underflow : std::exception {};

    Stack(std::initializer_list<T> l) { 
        if (l.size() > max_size) throw overflow{}; 
        data.insert(data.end(), l.begin(), l.end());
    }
    T const& top() const {
        if (data.empty()) throw underflow{};
        return data.back();
    }
    void pop() {
        if (data.empty()) throw underflow{};
        data.pop_back();
    }
    void push(T&& elem) { 
        if (data.size() == max_size) throw overflow{};
        data.push_back(elem); 
    }
    void clear() { data.clear(); }
    size_t size() const { return data.size(); }
    bool full() { return (data.size() == max_size); }
    bool empty() { return data.empty();}

private:
    std::vector<T> data;
    static size_t const max_size = N;
};

int main() {
    Stack<double> ds{1.1, 2.2, 3.3};
    std::cout << "init" << std::endl;
    std::cout << ds.top() << std::endl;
    std::cout << ds.size() << std::endl;
    std::cout << ds.full() << std::endl;
    std::cout << ds.empty() << std::endl;

    ds.pop();
    std::cout << "pop" << std::endl;
    std::cout << ds.top() << std::endl;
    std::cout << ds.size() << std::endl;
    std::cout << ds.full() << std::endl;
    std::cout << ds.empty() << std::endl;

    ds.push(4.4);
    std::cout << "push" << std::endl;
    std::cout << ds.top() << std::endl;
    std::cout << ds.size() << std::endl;
    std::cout << ds.full() << std::endl;
    std::cout << ds.empty() << std::endl;

    auto ds2 = ds;
    std::cout << "copy" << std::endl;
    std::cout << ds2.top() << std::endl;
    std::cout << ds.size() << std::endl;
    std::cout << ds2.size() << std::endl;
    
    ds.clear();
    std::cout << "clear" << std::endl;
    std::cout << ds.size() << std::endl;
    std::cout << ds.full() << std::endl;
    std::cout << ds.empty() << std::endl;
    std::cout << ds2.size() << std::endl;

    ds = std::move(ds2);
    std::cout << "move" << std::endl;
    std::cout << ds.size() << std::endl;
    std::cout << ds2.size() << std::endl;

    std::cout << "N" << std::endl;
    Stack<double, 3> ds3{1.1, 2.2, 3.3};
    std::cout << ds3.size() << std::endl;
    std::cout << ds3.full() << std::endl;
    return 0;
}
