#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <ctime>


#ifdef _WIN32 //Check if the operating sys is windows
#include <windows.h> //Include windows header files
#include <conio.h> //include console in/out functions
#endif

using namespace std;

/*
Picks a random sentance from the txt file. Then give the user 60 seconds to complete as many sentances as possible.

I tried to make a windows anti-copy-paste deterant but it doesn't work in VScode's terminal.

Written on 7/26/2026
Written by: AJ Utz

Last Update: 8/5/2026
*/

void seedRandomNumberGenerator(){
    srand(time(0));
}

int randomizer(int min, int max){
    return (rand() % (max - min + 1) + min);
}


int countWords(const string& text){
    /* this function counts the number of words in a given string by using an input string stream to itterate through each word */
    istringstream stream(text);
    int count = 0;
    string word;
    while(stream >> word){
        ++count;
    }
    return count;
}

//not sure this worked. it didn't in vscode
#ifdef _WIN32
bool enableAntiPasteMode(){
    /* Modify the windows console mode flags to disable common paste operations */
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    if(hInput == INVALID_HANDLE_VALUE){
        return false;
    }

    DWORD mode = 0;
    if(!GetConsoleMode(hInput, &mode)){
        return false;
    }
    //modify and disable paste operations
    DWORD newMode = mode;
    newMode |= ENABLE_EXTENDED_FLAGS;
    newMode &= ~ENABLE_QUICK_EDIT_MODE;
    newMode &= ~ENABLE_INSERT_MODE;
    newMode &= ~ENABLE_MOUSE_INPUT;

    return SetConsoleMode(hInput, newMode) != 0;
}

string readTypedLineNoPaste(){
    string input; //Storage for the typed chars

    while(true){
        int ch = _getch(); //read char from console
        
        //if pressed key is enter
        if(ch == 13){ 
            cout << '\n';
            break;
        }

        //if pressed key is backspace
        if(ch == 8){ 
            if(!input.empty()){
                input.pop_back();
                cout << "\b \b";
            }
            continue;
        }

        // If key pressed is ctrl+A
        if(ch == 22){
            continue;
        }

        // If key presed is a special control char
        if(ch == 0 || ch == 224){
            (void)_getch();
            continue;
        }

        // If the pressed key is a printable char or space
        if(isprint(static_cast<unsigned char>(ch)) || ch == ' '){
            input.push_back(static_cast<char>(ch));
            cout << static_cast<char>(ch);
        }
    }

    return input; //Return the complete typed line as a string
}
#endif

//function to read all lines from a file into memory
std::vector<std::string> readFile(const std::string& filename){
    std::ifstream file(filename);
    if(!file){
        cerr << "Error opening file: " << filename << '\n';
        exit(EXIT_FAILURE);
    }

    vector<string> lines;
    string line;
    
    while(getline(file, line)){
        lines.push_back(line);
    }
    file.close();

    return lines;
}

int typingMain(){
    const string filename = "typingtest.txt";
    int min = 0;
    const int testDurationSeconds = 60;
    seedRandomNumberGenerator();

#ifdef _WIN32
    if(!enableAntiPasteMode()){
        cerr << "Warning: Could not enable anti-paste console mode." << '\n';
    }
#endif

    try{
        vector<string> lines = readFile(filename); // read the contents of the file into a vector of strings
        if(lines.empty()){
            cerr << "No lines found in file." << '\n';
            return EXIT_FAILURE;
        }

        int max = static_cast<int>(lines.size()) - 1;// get the max index for random selection
        int totalWordsTyped = 0;
        int roundsCompleted = 0;

        cout << "Typing test started. You have " << testDurationSeconds << " seconds." << '\n';
        cout << "Type each sentence and press Enter." << '\n';

        auto testStart = chrono::steady_clock::now();

        while(true){
            double elapsedSeconds = chrono::duration<double>(chrono::steady_clock::now() - testStart).count();
            if(elapsedSeconds >= testDurationSeconds){
                break;
            }

            int lineIndex = randomizer(min, max);
            int secondsRemaining = static_cast<int>(testDurationSeconds - elapsedSeconds);

            cout << "\n[" << secondsRemaining << "s left] " << lines[lineIndex] << '\n';

            string input;
#ifdef _WIN32
            input = readTypedLineNoPaste();
#else
            getline(cin >> ws, input);
#endif

            totalWordsTyped += countWords(input);
            ++roundsCompleted;
        }

        double totalElapsedSeconds = chrono::duration<double>(chrono::steady_clock::now() - testStart).count();
        double wpm = 0.0;
        if(totalElapsedSeconds > 0.0){
            wpm = totalWordsTyped * (60.0 / totalElapsedSeconds);
        }

        cout << "\nTime is up!" << '\n';
        cout << "Sentences completed: " << roundsCompleted << '\n';
        cout << "Total words typed: " << totalWordsTyped << '\n';
        cout << "Your WPM: " << wpm << '\n';
    }catch(const exception& e){
        cerr << "Error: " << e.what() << '\n';
        return EXIT_FAILURE;
    }

    return 0;
}