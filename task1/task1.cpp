#include <iostream>

// Напишите функцию, которая принимает на вход знаковое целое число и
// печатает его двоичное представление, не используя библиотечных классов или функций.
void printBinaryRepresentation(const int number) {
    std::cout << number << '\t';
    unsigned int mask = 1 << (sizeof(unsigned int) * 8 - 1);
    while (mask != 0) {
        std::cout << (int)((number & mask) != 0);
        mask = mask >> 1;
    }
    std::cout << '\n';
}


int main() {
    int n;
    std::cout << "Enter number: ";
    std::cin >> n;
    printBinaryRepresentation(n);
    return 0;
}
