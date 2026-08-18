#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

/*
An easily importable coin flip mechanic.

Last updated: 8/18/2026
Written on: 8/18/2026
Written by: AJ Utz
*/

void seedrandomnumber(){
    static bool seeded = false;
    if(!seeded){
        srand(time(0));
        seeded = true;
    }
}

int coinrandomizer(int min, int max){
    return(rand() % (max - min + 1) + min);
}

//Call this to flip a coin. Check who won with the bools. The more flips you add the less likely it will end in a tie. e.g. 1000 flips = 2.52% tie chance.
int coinWrapper(int flips, bool& headsWin, bool& tailsWin, bool& tie){
    int heads = 0;
    int tails = 0;
    
    for (int i = 0; i < flips; i++){
        seedrandomnumber();
        int coinrandnumber = coinrandomizer(0, 1);
        if(coinrandnumber == 1){
            heads++;
        }else{
            tails++;
        }
    }
    
    if(heads < tails){
        tailsWin = true;
        return tailsWin;
    }else if (tails < heads){
        headsWin = true;
        return headsWin;
    }else{
        tie = true;
        return tie;
    }
}

//Example of how to initialize the coinWrapper.
int coinMain(){

    int flips;
    bool headsWin = false;
    bool tailsWin = false;
    bool tie = false;

    cout << "How many coin flips would you like to do?\n";
    cin >> flips;
    
    coinWrapper(flips, headsWin, tailsWin, tie);

    if(tailsWin){
        cout << "Tails win!\n";
    }else if (headsWin){
        cout << "Heads win!\n";
    }else if (tie){
        cout << "It's a Tie!";
    }
    
    return 0;
}
