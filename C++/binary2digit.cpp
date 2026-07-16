#include <iostream>
using namespace std;
//This function converts a binary number to a decimal number

int binaryToDecimal(int n) {
    int decimalNumber = 0;
    int base = 1; // Initialize base value to 1 (2^0)
    
    while (n){
        int lastDigit = n % 10; // Get the last digit of the binary number

        if(lastDigit != 0 && lastDigit !=1){
            cerr << "Invalid Binary Number\n";
            return -1; // Return -1 to indicate an error
        }

        decimalNumber += lastDigit * base; // Add the last digit multiplied by its base value to the decimal number
        base *= 2; // Update the base value to the next power of 2
        n /= 10; // Remove the last digit from the binary number
    }

    return decimalNumber; // Return the final decimal number
}

int b2dmain(){
    int n;
    cout << "Enter a binary number: ";
    cin >> n;

    int decimalNumber = binaryToDecimal(n);
    cout << "The decimal equivalent of binary " << n << " is: " << decimalNumber << endl;

    return 0;
}