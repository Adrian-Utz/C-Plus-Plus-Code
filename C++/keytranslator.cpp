#include <iostream>
#include <bitset>

using namespace std;

/*
This should function as follows: It will ask the user to input a key from their keyboard.
Then it will output data that corresponds to the pressed key. ASCII values, binary values, Hexadecimal values, ect.
*/

void displayKeyInfo() {
    char key;

    // Prompt the user to press a key
    cout << "Press any key to see its ASCII, binary, and decimal values: ";
    cin >> key; // Read a single character from the keyboard

    // Display the ASCII value
    cout << "ASCII Value: " << static_cast<int>(key) << "\n";

    // Display the binary representation using std::bitset
    cout << "Binary Representation: " << std::bitset<8>(static_cast<unsigned char>(key)) << "\n";

    // Note: The above uses 8 bits because std::bitset is designed for fixed-width binary representations.
    // If you need a different number of bits, adjust the template parameter accordingly (e.g.,`bitset<16>`).
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