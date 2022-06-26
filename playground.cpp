#include <iostream>

struct BaseClass {
    virtual char const* final_message() const {
        return "TestBase";
    }
};

struct DerivedClass : BaseClass {
    char const* final_message2() const {
        return "Test";
    }
};

int main(void) {
    // using std::string_literals;
    DerivedClass derived;
    
    std::cout << derived.final_message2() << std::endl;
}