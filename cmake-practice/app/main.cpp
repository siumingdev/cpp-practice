#include <iostream>
#include "myvector/vector.hpp"
#include <nlohmann/json.hpp>


using namespace std;
using json = nlohmann::json;


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

   json j = {
      {"pi", 3.141},
      {"happy", true},
      {"name", "Niels"},
      {"nothing", nullptr},
      {"answer", {
         {"everything", 42}
      }},
      {"list", {1, 0, 2}},
      {"object", {
         {"currency", "USD"},
         {"value", 42.99}
      }}
   };

   cout << j << endl;
}
