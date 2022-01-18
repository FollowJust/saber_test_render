#include <iostream>
#include <limits>

// Напишите функцию, которая принимает на вход знаковое целое число и
// печатает его двоичное представление, не используя библиотечных классов или функций.
void printBinaryRepresentation(const int number) {
    std::cout << number << '\t';
    unsigned int bitshift = 1 << (sizeof(unsigned int) * 8 - 1);
    while (bitshift != 0) {
        std::cout << (int)((number & bitshift) != 0);
        bitshift = bitshift >> 1;
    }
    std::cout << '\n';
}


int main() {
    printBinaryRepresentation(10);
    printBinaryRepresentation(-10);
    printBinaryRepresentation(std::numeric_limits<int>::min());
    printBinaryRepresentation(std::numeric_limits<int>::max());
    return 0;
}
