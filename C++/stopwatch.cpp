#include <iostream>
#include <iomanip>
#include <chrono>

#ifdef min
#undef min
#endif

using namespace std;

std::chrono::time_point<std::chrono::steady_clock> start_time;
std::chrono::time_point<std::chrono::steady_clock> pause_time = std::chrono::time_point<std::chrono::steady_clock>::min();
std::chrono::time_point<std::chrono::steady_clock> end_time;
bool timerRunning = false;
bool timerStarted = false;

void startTimer(){
    if(!timerRunning){
        start_time = std::chrono::high_resolution_clock::now();
        timerRunning = true;
        timerStarted = true;
    }else{
        cout << "Timer is already Running." << '\n';
    }
}

void stopTimer(){
    if(timerStarted){
        end_time = std::chrono::high_resolution_clock::now();
        timerRunning = false;
    }else{
        cout << "Timer is Stopped" << '\n';
    }
}

void pauseTimer(){
    if(timerRunning){
        pause_time = std::chrono::high_resolution_clock::now();
        timerRunning = false;
        cout << "Timer paused. Press R to resume, or Q to quit." << '\n';
    }else{
        cout << "Timer is not running." << '\n';
    }
}

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

        if(activateTimer == 'S'){
            startTimer();
        }else if(activateTimer == 'P'){
            pauseTimer();
        }else if(activateTimer == 'R'){
            resumeTimer();
        }else if(activateTimer == 'E' || activateTimer == 'Q'){
            stopTimer();
            if(activateTimer == 'Q'){
                break;
            }
        }
    }

    cout << std::fixed;
    cout << std::setprecision(0);
    cout << "Elapsed Time: " << calculateTime() << " Milliseconds" << '\n';

    return 0;
}