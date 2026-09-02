#include <iostream>
#include <bitset>
#include <sstream>

using namespace std;

/*
This should function as follows: It will ask the user to input a key from their keyboard.
Then it will output data that corresponds to the pressed key. ASCII values, binary values, Hexadecimal values, ect.
*/

void displayKeyInfo() {
    char key;

    // Prompt the user to press a key
    cout << "Press any key to see its ASCII, binary, and Hexadecimal values: ";
    cin >> key; // Read a single character from the keyboard

    // Calculate the ASCII value
    int asciiValue = static_cast<int>(key);
    
    // Calculate the binary representation using std::bitset
    std::bitset<8> binaryValue(asciiValue);
    std::string binaryString = binaryValue.to_string();
    // Note: The above uses 8 bits because std::bitset is designed for fixed-width binary representations.
    // If you need a different number of bits, adjust the template parameter accordingly (e.g.,`bitset<16>`).

    //Calculate the Hexadecimal value
    std::stringstream ss;
    ss << std::hex << asciiValue;
    std::string hexString = ss.str();
    
    //Display all Values
    cout << "ASCII Value: " << static_cast<int>(key) << "\n";
    cout << "Binary Representation: " << binaryString << "\n";
    cout << "Hexadecimal Representation: $" << hexString << "$" << "\n";
}

int keymain() {
    displayKeyInfo();
    while(true){
        char retry;
        cout << "Try Again? (y/n): ";
        cin >> retry;

        if(retry == 'y'){
            displayKeyInfo();
        }else if (retry == 'n'){
            return 0;
        }else{
            cout << "Please reply with y or n." << '\n';
            continue;
        }
    }
    return 0;
}