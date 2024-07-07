// based on https://github.com/petergottschling/dmc3/blob/master/c%2B%2B03/vector_test.cpp
// with sum_in_threads and sum_async member functions added

#include <cassert>
#include <future>
#include <iostream>
#include <vector>
#include <thread>


class vector {
public:
    vector(int size) : my_size(size), data(new double[size]) {}

    vector() : my_size(0), data(0) {}

    ~vector() { delete[] data; }

    vector(const vector& that) : my_size(that.my_size), data(new double[my_size]) {
        for (int i = 0; i < my_size; ++i) data[i] = that.data[i];
    }

    void operator=(const vector& that) {
        assert(that.my_size == my_size);
        for (int i = 0; i < my_size; ++i) data[i] = that.data[i];
    }

    int size() const { return my_size; }
    int size() { return my_size; }

    double& operator[](int i) const {
        assert(i >= 0 && i < my_size);
        return data[i];
    }

    double& operator[](int i) {
        assert(i >= 0 && i < my_size);
        return data[i];
    }

    vector operator+(const vector& that) const {
        assert(that.my_size == my_size);
        vector sum(my_size);
        for (int i = 0; i < my_size; ++i) sum[i] = (*this)[i] + that[i];
        return sum;
    }

    vector sum_in_threads(const vector& that, size_t num_threads = 2) const {
        assert(that.my_size == my_size);
        vector sum(my_size);

        std::vector<std::thread> threads;
        for (size_t i = 0; i < num_threads; ++i)
            threads.emplace_back([&, i, this]() {
               for (size_t j = i; j < my_size; j += num_threads) {
                   sum[j] = (*this)[j] + that[j];
               }
            });

        for (size_t i = 0; i < num_threads; ++i) threads[i].join();
        return sum;
    }

    vector sum_async(const vector& that) const {
        assert(that.my_size == my_size);
        vector sum(my_size);

        std::vector<std::future<double>> futures;
        for (size_t i = 0; i < my_size; ++i)
            futures.push_back(std::async([&, i, this]() { return (*this)[i] + that[i]; }));
        
        for (size_t i = 0; i < my_size; ++i) {
            futures[i].wait();
            sum[i] = futures[i].get();
        }
        return sum;
    }

private:
    int my_size;
    double* data;
};

std::ostream& operator<<(std::ostream& os, const vector& v) {
    os << '[';
    if (v.size() > 0) os << v[0];
    for (int i = 1; i < v.size(); ++i) os << ", " << v[i];
    return os << ']';
}

double dot(const vector& v, const vector& w) {
    double s = 0.0;
    for (int i = 0; i < v.size(); i++) s += v[i] * w[i];
    return s;
}

int main() {
    vector v1(4);
    v1[0] = v1[1] = 1.0;
    v1[2] = 2.0;
    v1[3] = -3.0;
    std::cout << v1 << std::endl;

    vector w(v1.size());
    w = v1;

    const vector v2(v1);
    std::cout << "v2[3] is " << v2[3] << '\n';

    v1[3] = 3.14;
    std::cout << "v2[3] is " << v2[3] << '\n';

    std::cout << "w is " << w << '\n';
    v1[1] = 9.;
    std::cout << "w is " << w << '\n';

    vector sum(w + v1);
    std::cout << sum << std::endl;
    
    vector sum2{w.sum_in_threads(v1, 3)};
    std::cout << sum2 << std::endl;
    
    vector sum3{w.sum_async(v1)};
    std::cout << sum3 << std::endl;
    return 0;
}
