#include <iostream>
using namespace std;

#ifdef _WIN32
#include <windows.h>
#endif

#include "binary2digit.cpp"
#include "helloworld.cpp"
#include "burgermaker.cpp"
#include "keytranslator.cpp"
#include "dinojump.cpp"
#include "typingtest.cpp"
#include "stopwatch.cpp"
#include "coinflip.cpp"
#include "calculator.cpp"
#include "timer.cpp"
#include "binary2String.cpp"
#include "string2Binary.cpp"
#include "memoryallocation.cpp"
#include "asteroids.cpp"
/*
Last Update: 9/23/2026
Written on 7/15/2026
Written by: AJ Utz

Starting point in the CLI.
*/

//Starting location
int main(){
    //Here just in case terminal does not support Unicode Box-drawing chars.
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    #endif

    int choice;
    do{
        cout << "┌──────────────────────────┐\n";
        cout << "│ 0. Exit                  │\n";
        cout << "│ 1. Binary Tools          │\n";    
        cout << "│ 2. Hello World           │\n";
        cout << "│ 3. Key Translator        │\n";
        cout << "│ 4. Games                 │\n";
        cout << "│ 5. Time Tools            │\n";
        cout << "│ 6. Coin Flip             │\n";
        cout << "│ 7. Calculator            │\n";
        cout << "└──────────────────────────┘\n";
        cout << "Enter what program you wish to run: ";
        cin >> choice;

        switch(choice){
            case 0:
                cout << "Exiting program.\n";
                break;
            case 1:
                int case1choice;
                cout << "┌──────────────────────────────┐\n";
                cout << "│ 0. Exit                      │\n";
                cout << "│ 1. Binary to Decimal Tool    │\n";
                cout << "│ 2. Sentance to Binary Tool   │\n";
                cout << "│ 3. Binary to Sentance Tool   │\n";
                cout << "└──────────────────────────────┘\n";
                cout << "What would you like to do: ";
                cin >> case1choice;

                switch(case1choice){
                    case 0:
                        break;
                    case 1:
                        b2dmain();
                        cout << endl;
                        break;
                    case 2:
                        S2Bmain();
                        cout << endl;
                        break;
                    case 3:
                        B2Smain();
                        cout << endl;
                        break;
                    default:
                        cout << "Invalid choice please try again.\n";
                }
                break;
            case 2:
                hellomain();
                cout << endl;
                break;
            case 3:
                keymain();
                cout << endl;
                break;
            case 4:
                int case4choice;
                cout << "┌──────────────────────────────┐\n";
                cout << "│ 0. Exit                      │\n";
                cout << "│ 1. Dino Jump Game            │\n";
                cout << "│ 2. Typing Test Game          │\n";
                cout << "│ 3. Burger Maker              │\n";
                cout << "│ 4. Asteroids                 │\n";
                cout << "└──────────────────────────────┘\n";
                cout << "What would you like to do: ";
                cin >> case4choice;
                
                switch(case4choice){
                    case 0:
                        break;
                    case 1:
                        dinoMain();
                        cout << endl;
                        break;
                    case 2:
                        typingMain();
                        cout << endl;
                        break;
                    case 3:
                        burgermain();
                        cout << endl;
                        break;
                    case 4:
                        asteroidsMain();
                        cout << endl;
                        break;
                    default:
                        cout << "Invalid choice. Please try again.\n";
                }
                break;
            case 5:
                int case5choice;
                cout << "┌──────────────────────────────┐\n";
                cout << "│ 0. Exit                      │\n";
                cout << "│ 1. Stopwatch Tool            │\n";
                cout << "│ 2. Timer Tool                │\n";
                cout << "└──────────────────────────────┘\n";
                cout << "What would you like to do: ";
                cin >> case5choice;

                switch(case5choice){
                    case 0:
                        break;
                    case 1:
                        stopwatchMain();
                        cout << endl;
                        break;
                    case 2:
                        timerMain();
                        cout << endl;
                        break;
                    default:
                        cout << "Invalid choice. Please try again.\n";
                }
                break;
            case 6:
                coinMain();
                cout << endl;
                break;
            case 7:
                calculatorMain();
                cout << endl;
                break;
            case 8:
                memoryAllocationMain();
                cout << endl;
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }while(choice != 0);    
    return 0;
}

