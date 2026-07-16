#include <iostream>

using namespace std;

/*
This should function as follows: It will ask the user to input a key from their keyboard.
Then it will output data that corresponds to the pressed key. ASCII values, binary values, Hexadecimal values, ect.
*/

int keytranslation(char key){
    cout << "You pressed the key: " << key << endl;
    cout << "ASCII value: " << static_cast<int>(key) << endl;

    cout << "Binary value: ";
    for (int i = 7; i >= 0; --i) {
        cout << ((static_cast<int>(key) >> i) & 1);
    }
    cout << endl;

    cout << "Hexadecimal value: " << hex << static_cast<int>(key) << endl;

    cout << "Octal value: " << oct << static_cast<int>(key) << endl;

    cout << "Decimal value: " << dec << static_cast<int>(key) << endl;

    return 0;
}

int keymain() {
    char key;
    cout << "Press a key on your keyboard: ";
    cin >> key;

    return keytranslation(key);
}