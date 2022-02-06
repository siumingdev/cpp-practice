#include <iostream>
#include "myvector/vector.hpp"
#include <nlohmann/json.hpp>


using namespace std;

int main()
{
   print_hello_world();
   Vector<std::string> msg {"Hello", "C++", "World", "from", "VS Code", "and the C++ extension!"};
   auto msg2 = msg;
   msg2[0] = "Test";
   cout << msg << endl;
   cout << msg2 << endl;
   cout << Vector<string>{"Test", "2"} << endl;

   int y = 10;
   // int &&x = y;
   // cout << x;
}
