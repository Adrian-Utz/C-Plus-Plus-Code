#include <iostream>
using namespace std;

#include "binary2digit.cpp"
#include "helloworld.cpp"
#include "burgermaker.cpp"
/*
Written on 7-15-2026
Written by: AJ Utz

Last Update: 7-16-2026
*/

//Starting location
int main(){
    int choice;
    do{
        cout << "0. Exit\n";
        cout << "1. Binary to Decimal Converter\n";
        cout << "2. Burger Maker\n";
        cout << "3. Hello World\n";
        cout << "Enter what program you wish to run:\n";
        cin >> choice;

        switch(choice){
            case 0:
                cout << "Exiting program.\n";
                break;
            case 1:
                b2dmain();
                break;
            case 2:
                burgermain();
                break;
            case 3:
                hellomain();
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }while(choice != 0);    
    return 0;
}

