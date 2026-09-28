# C-Plus-Plus-Code  
C++ Coding Practice


## Files:
```
src/
├── main.cpp                    - Main CLI 
├── binary2digit.cpp            - Convert a single binary value to a digit
├── binary2String.cpp           - Convert a binary string to a sentance
├── burgermaker.cpp             - Make your own burger
├── calculator.cpp              - Calculate simple math
├── coinflip.cpp                - Flip a coin('s)
├── dinojump.cpp                - Dino game in the terminal
├── helloworld.cpp              - Hello World!
├── keytranslator.cpp           - See what a specific key's value is
├── stopwatch.cpp               - Basic stopwatch
├── string2Binary.cpp           - Get the binary value of a sentance
├── timer.cpp                   - Set a timer
├── typingtest.cpp              - Test your typing skills 
├── typingtest.txt              - Text file for the typing test
└── README.md                   - This file
```

## CLI format:

```
                                ┌──────────────────────────────┐
                                │ 0. Exit                      │
                                │ 1. Binary to Decimal Tool    │
                                │ 2. Sentance to Binary Tool   │
                                │ 3. Binary to Sentance Tool   │
                                ├──────────────────────────────┘
                                │    ┌──────────────────────┐
                                │    │ 0. Exit              │
┌──────────────────────────┐    │    │ 1. Dino Jump Game    │
│ 0. Exit                  │    │    │ 2. Typing Test Game  │
│ 1. Binary Tools          ├────┘    │ 3. Burger Maker      │
│ 2. Hello World           │         │ 4. Asteroids         │
│ 3. Key Translator        │         ├──────────────────────┘
│ 4. Games                 ├─────────┘
│ 5. Time Tools            ├─────────┐
│ 6. Coin Flip             │         ├───────────────────┐
│ 7. Calculator            │         │ 0. Exit           │
└──────────────────────────┘         │ 2. Stopwatch Tool │
                                     │ 2. Timer Tool     │
                                     └───────────────────┘ 
```

## Changes:
- Added Unicode Box Drawing support.

## Descriptions:
#### [main.cpp](https://github.com/Adrian-Utz/C-Plus-Plus-Code/blob/main/src/main.cpp)
- Entrance point for the program.  

#### [binary2digit.cpp](https://github.com/Adrian-Utz/C-Plus-Plus-Code/blob/main/src/binary2digit.cpp)
- Convert a binary number to its decimal counterpart. (E.G. 10101111 = 175.) To activate call binaryToDecimal(int).

#### [burgermaker.cpp](https://github.com/Adrian-Utz/C-Plus-Plus-Code/blob/main/src/burgermaker.cpp) 
- Make your own burger.  

#### [helloworld.cpp](https://github.com/Adrian-Utz/C-Plus-Plus-Code/blob/main/src/helloworld.cpp)
- Classic  

#### [keytranslator.cpp](https://github.com/Adrian-Utz/C-Plus-Plus-Code/blob/main/src/keytranslator.cpp)
- Tells you the values of a pressed key. (E.G. "A" equals 97 in ASCII and 01100001 in binary.)

#### [dinojump.cpp](https://github.com/Adrian-Utz/C-Plus-Plus-Code/blob/main/src/dinojump.cpp)
- Command line Dino game. Space is jump.

#### [typingtest.cpp](https://github.com/Adrian-Utz/C-Plus-Plus-Code/blob/main/src/typingtest.cpp)
- Test you typing skills. Customize the txt file with the same name to your hearts content. I tried making a copy and paste anti-function, but I don't know if it worked. It didn't work in VScode's terminal.  

#### [stopwatch.cpp](https://github.com/Adrian-Utz/C-Plus-Plus-Code/blob/main/src/stopwatch.cpp)
- It's a stopwatch. What did you expect?  

#### [coinflip.cpp](https://github.com/Adrian-Utz/C-Plus-Plus-Code/blob/main/src/coinflip.cpp)
- Flip a coin a designated number of times. Can be used as a randomizer if your parameter is set to activate on 'tie'. 1000 flips gives you around a .253% chance to tie, or 1 in 395.

#### [calculator.cpp](https://github.com/Adrian-Utz/C-Plus-Plus-Code/blob/main/src/calculator.cpp)
- Type out a math problem and see what happens. It should follow PEMDAS. (or GEMDAS, but the only allowed grouping symbols are parenthesizes atm) 

#### [binary2String.cpp](https://github.com/Adrian-Utz/C-Plus-Plus-Code/blob/main/src/binary2String.cpp)
- Takes a string of binary numbers, seperated by spaces, and reverts them into a string.

#### [string2Binary.cpp](https://github.com/Adrian-Utz/C-Plus-Plus-Code/blob/main/src/string2Binary.cpp)
- Takes a string and returns the binary value of each charater.

#### [timer.cpp](https://github.com/Adrian-Utz/C-Plus-Plus-Code/blob/main/src/timer.cpp)
- Takes user input in this format: "HH:MM:SS". Then the thread sleeps. Good for delays or timers in multithreaded applications. Sleeping does not consume CPU cycles, and relinquishes control to the OS, avoiding bottlenecks.
