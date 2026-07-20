#include <iostream>
using namespace std;

#include "binary2digit.cpp"
#include "helloworld.cpp"
#include "burgermaker.cpp"
#include "keytranslator.cpp"
#include "dinojump.cpp"
/*
Written on 7-15-2026
Written by: AJ Utz

Last Update: 7-20-2026
*/

//Starting location
int main(){
    int choice;
    do{
        cout << "0. Exit\n";
        cout << "1. Binary to Decimal Converter\n";
        cout << "2. Burger Maker\n";
        cout << "3. Hello World\n";
        cout << "4. Key Translator\n";
        cout << "5. Dino Jump\n";
        cout << "Enter what program you wish to run: ";
        cin >> choice;

        switch(choice){
            case 0:
                cout << "Exiting program.\n";
                break;
            case 1:
                b2dmain();
                cout << endl;
                break;
            case 2:
                burgermain();
                cout << endl;
                break;
            case 3:
                hellomain();
                cout << endl;
                break;
            case 4:
                keymain();
                cout << endl;
                break;
            case 5:
                dinoMain();
                cout << endl;
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }while(choice != 0);    
    return 0;
}

