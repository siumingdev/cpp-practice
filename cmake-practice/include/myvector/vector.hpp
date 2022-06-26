#include <string>
#include <initializer_list>

// using namespace std;

void print_hello_world();

template<typename T>
class Vector
{
private:
   int sz;
   T* elem;
public:
    Vector(int s);
    Vector(std::initializer_list<T> l);
    Vector(const Vector<T> &vec);
    Vector(Vector<T> &&vec);
    ~Vector();
    T& operator[](int i);
    const T& operator[](int i) const;
    int size() const;
};

template<typename T>
Vector<T>::Vector(int s) : elem{new T[s]{}}, sz{s}
{
}

template<typename T>
Vector<T>::Vector(std::initializer_list<T> l) : elem{new T[l.size()]}, sz{static_cast<int>(l.size())}
{
   int i = 0;
   for (auto e : l)
   {
      elem[i++] = e;
   }
}

template<typename T>
Vector<T>::Vector(const Vector<T> &vec) : elem{new T[vec.size()]{}}, sz{vec.size()}
{
   std::cout << "test" << std::endl;
   for (auto i = 0; i < sz; ++i)
   {
      elem[i] = vec.elem[i];
   }
}

template<typename T>
Vector<T>::Vector(Vector<T> &&vec)
{
   std::cout << "move" << std::endl;
   sz = vec.sz;
   elem = vec.elem;
   vec.elem = nullptr;
}

template<typename T>
Vector<T>::~Vector()
{
    delete[] elem;
}

template<typename T>
T& Vector<T>::operator[](int i)
{
    return elem[i];
}

template<typename T>
const T& Vector<T>::operator[](int i) const
{
    return elem[i];
}

template<typename T>
int Vector<T>::size() const
{
    return sz;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T> &vec)
{
   for (int i = 0; i < vec.size(); ++i)
   {
      os << vec[i] << " ";
   }
   return os;
}


