#include <iostream>
#include <iomanip>
#include <chrono>
#include <ctype.h>

#ifdef min
#undef min
#endif

using namespace std;

//Initialize varaibles
std::chrono::time_point<std::chrono::steady_clock> start_time;
std::chrono::time_point<std::chrono::steady_clock> pause_time = std::chrono::time_point<std::chrono::steady_clock>::min();
std::chrono::time_point<std::chrono::steady_clock> end_time;
bool timerRunning = false;
bool timerStarted = false;

//If the timer is not running, activate it. 
void startTimer(){
    if(!timerRunning){
        start_time = std::chrono::high_resolution_clock::now();
        timerRunning = true;
        timerStarted = true;
    }else{
        cout << "Timer is already Running." << '\n';
    }
}

//If timer is running, stop it and record the current end time.
void stopTimer(){
    if(timerStarted){
        end_time = std::chrono::high_resolution_clock::now();
        timerRunning = false;
    }else{
        cout << "Timer is Stopped" << '\n';
    }
}

// If the timer is running, record the time at which it was paused, and set the running bool to false.
void pauseTimer(){
    if(timerRunning){
        pause_time = std::chrono::high_resolution_clock::now();
        timerRunning = false;
        cout << "Timer paused. Press R to resume, or Q to quit." << '\n';
    }else{
        cout << "Timer is not running." << '\n';
    }
}

//If the timer has started, and is not running, and paused is != Minimum time value, start the timer.
void resumeTimer(){
    if(timerStarted && !timerRunning && pause_time != std::chrono::time_point<std::chrono::steady_clock>::min()){
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(pause_time - start_time);
        
        start_time += duration;
        pause_time = std::chrono::time_point<std::chrono::steady_clock>::min();
        timerRunning = true;

        cout << "Resume Timer. Elapsed Time: " << (double)duration.count() << " Milliseconds" << '\n';
    }else{
        cout << "Timer is not running or paused." << '\n';
    }
}

double calculateTime(){
    if(!timerStarted){
        return 0;
    }

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    return duration.count();
}

int stopwatchMain(){
    char activateTimer = 'N';

    while(activateTimer != 'Q'){
        cout << "Press S to start the timer, P to pause the timer, R to resume the timer, E to stop the timer, or Q to quit: ";
        cin >> activateTimer;

        if(tolower((unsigned char)activateTimer) == 's'){
            startTimer();
        }else if(tolower((unsigned char)activateTimer) == 'p'){
            pauseTimer();
        }else if(tolower((unsigned char)activateTimer) == 'r'){
            resumeTimer();
        }else if(tolower((unsigned char)activateTimer) == 'e'){
            stopTimer();
        }else if(tolower((unsigned char)activateTimer) == 'q'){
            stopTimer();
            break;
        }
    }

    cout << std::fixed;
    cout << std::setprecision(0);
    cout << "Elapsed Time: " << calculateTime() << " Milliseconds" << '\n';

    return 0;
}