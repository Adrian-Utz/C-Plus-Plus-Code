#include <iostream>
#include <chrono>
#include <string>
#include <thread>

using namespace std;

/*
Ask the user how long they want the timer to run in the HH:MM:SS format.

last Update: 8/27/2026
Written on: 8/27/2026
Written by: AJ Utz
*/

void timer(int hours, int minutes, int seconds){
    auto totalDuration = chrono::hours(hours) + chrono::minutes(minutes) + chrono::seconds(seconds);

    auto startTime = chrono::steady_clock::now();
    while(chrono::steady_clock::now() - startTime < totalDuration){
        this_thread::sleep_for(chrono::milliseconds(10));
    }
}

// Example of how to call the timer. 
int timerMain(){
    string userInput;
    int hours;
    int minutes;
    int seconds;

    cout << "Enter time in the HH:MM:SS format.\n";
    cout << "Enter how long you want the timer to run for: ";

    cin >> userInput;
    sscanf(userInput.c_str(), "%d:%d:%d", &hours, &minutes, &seconds);

    timer(hours, minutes, seconds);
    cout << "Time is up!\n";
    return 0;
}