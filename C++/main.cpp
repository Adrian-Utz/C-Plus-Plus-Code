#include <iostream>

#include "binary2digit.cpp"
//Starting file
int main(){
    int n;
    std::cout << "Enter a binary number: ";
    std::cin >> n;

    int decimalNumber = binaryToDecimal(n);
    std::cout << "The decimal equivalent of binary " << n << " is: " << decimalNumber << std::endl;

    return 0;
}

