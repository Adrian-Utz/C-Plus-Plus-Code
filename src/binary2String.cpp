#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*
A tool to convert a given binary into a string output.

Last Update: 9/2/2026
Written on: 9/2/2026
Writtne by: AJ Utz
*/

string convertBinaryToString(const string& input){
    string output;
    unsigned char character = 0;
    int bitCount = 0;

    for (char bit : input){
        if (bit == ' ' || bit == '\t'){
            continue; //Skip spaces and tabs
        }

        if (bit != '0' && bit != '1'){
            return "Invalid binary input."; // Return error if bit is not '0' or'1'
        }

        character = static_cast<unsigned char>((character << 1) | (bit - '0')); //Shift char left and set the new bit
        ++bitCount;

        if (bitCount == 8){
            output += static_cast<char>(character); //convert char to ASCII and add to output
            character = 0; //Reset char
            bitCount = 0; //Reset count
        }
    }

    if (bitCount != 0){
        return "Binary input must contain complete 8-bit bytes."; //Error if there are leftover bits
    }

    return output;
}

int B2Smain(){
    string input;
    char tempchar;

    while(true){
        cout << "Enter a binary sequence: ";
        getline(cin >> ws, input);

        cout << "String: " << convertBinaryToString(input) << '\n';

        cout << "Try Again? (y/n): ";
        cin >> tempchar;
        if(tolower(static_cast<unsigned char>(tempchar)) != 'y'){
            return 0;
        }
    }

    return 0;
}