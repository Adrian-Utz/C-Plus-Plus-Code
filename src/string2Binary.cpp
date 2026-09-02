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
            //Shift the charater to the right by the current bit position and extract the lease significant bit using bitwise AND with 1
            binary += ((character >> bit) & 1) ? '1' : '0';
        }
        binary += ' ';
    }
    //If the binary string is not empty, remove the trailing space
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