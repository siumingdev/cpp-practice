#include <iostream>

char read_from(char* str, size_t size, size_t idx)
{
    if (idx < size)
    {
        return str[idx];
    }
    // raise an error
}

void write_to(char* str, size_t size, size_t idx, char c)
{
    if (idx < size)
    {
        str[idx] = c;
    }
}


struct Element {
    Element* next{};
    Element* prev{};
    void insert_after(Element* new_element) {
        new_element->next = next;
        next->prev = new_element;

        next = new_element;
        new_element->prev = this;
    }
    char prefix[2];
    short operating_number;
};


int main(void) {
    std::cout << "Hello World!" << std::endl;

    char str[] {"ab?de"};
    size_t str_size {sizeof(str)/sizeof(char) - 1};

    std::cout << str << std::endl;
    std::cout << str_size << std::endl;

    std::cout << read_from(str, str_size, 2) << std::endl;
    write_to(str, str_size, 2, 'c');
    std::cout << read_from(str, str_size, 2) << std::endl;
    std::cout << str << std::endl;


    auto original = 100;
    auto& original_ref = original;
    printf("Original:  %d\n", original);
    printf("Reference: %d\n", original_ref);

    auto new_value = 200;
    original_ref = new_value;

    printf("Original:  %d\n", original);
    printf("New Value:  %d\n", new_value);
    printf("Reference: %d\n", original_ref);
}