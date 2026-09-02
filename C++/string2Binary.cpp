#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*
A tool to convert a given string into a binary output.

Last Update: 9/2/2026
Written on: 9/2/2026
Writtne by: AJ Utz
*/

string convertStringToBinary(const string& input){
    string binary;

    for (unsigned char character : input){
        for (int bit = 7; bit >= 0; --bit){
            binary += ((character >> bit) & 1) ? '1' : '0';
        }
        binary += ' ';
    }

    if (!binary.empty()){
        binary.pop_back();
    }

    return binary;
}

int S2Bmain(){
    string input;
    char tempchar;

    while(true){
        cout << "Enter a sentance: ";
        getline(cin >> ws, input);

        cout << "Binary: " << convertStringToBinary(input) << '\n';

        cout << "Try Again? (y/n): ";
        cin >> tempchar;
        if(tolower(static_cast<unsigned char>(tempchar)) != 'y'){
            return 0;
        }
    }
}