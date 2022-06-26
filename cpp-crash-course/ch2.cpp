#include <iostream>

enum class Operation { add, subtract, multiply, divide };

class Calculator
{
public:
    Calculator(Operation op_in) : op{op_in} {}
    
    int calculate(int a, int b)
    {
        int result {0};
        
        switch(op)
        {
            case Operation::add:
            {
                result = a + b;
            } break;
            case Operation::subtract:
            {
                result = a - b;
            } break;
            case Operation::multiply:
            {
                result = a * b;
            } break;
            case Operation::divide:
            {
                result = a / b;
            } break;
            default:
            {
                std::cout << "Error!";
            }
        }

        return result;
    }

private:
    Operation op;
};


int main(void) {
    std::cout << "Hello World!" << std::endl;

    std::cout << Calculator(Operation::add).calculate(1, 2) << std::endl;
    std::cout << Calculator(Operation::subtract).calculate(1, 2) << std::endl;
    std::cout << Calculator(Operation::divide).calculate(6, 2) << std::endl;
    std::cout << Calculator(Operation::multiply).calculate(6, 2) << std::endl;
}