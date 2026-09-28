#include <iostream>
#include <memory>

using namespace std;

/*
Last Update: 9/18/2026
Written on 9/17/2026
Written by: AJ Utz
*/

/*Smart pointers are smart because the automatically release heap memory when they go out of scope*/
int smartPointer(){
    //Allocates an integer on the heap and inits it to 42
    unique_ptr<int> ptr = make_unique<int>(42);
    cout << ptr << endl;

    //Allocates a dynamic array of 5 ints on the heap
    int size = 5;
    auto arr = make_unique<int[]>(size);
    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;
    arr[3] = 40;
    arr[4] = 50;

    for(int i = 0; i < size; i++){
        cout << arr[i] << " is at: " << &arr[i] << endl;
    }
    return 0;
}

/*Legacy pointers manually allocate and free memeory with the new and delete keywords.*/
int legacyPointer(){
    //Allocate memory for one integer
    int* ptr = new int;
    *ptr = 100;//Assign value

    cout << ptr << endl;

    delete ptr;//Free the memory
    ptr = nullptr;//Clear pointer to avoid dangling references

    /*Using an array of pointers*/
    const int SIZE = 5;
    int* ptrArray[SIZE];

    //init values for each pointer in the array
    for(int i = 0; i < SIZE; i++){
        ptrArray[i] = new int(i * 10);
    }
    
    //Print out the pointer number and memory location
    for(int i = 0; i < SIZE; i++){
        cout << *ptrArray[i] << " : " << &*ptrArray[i] << endl;
    }

    // delete each item in the array
    for(int i = 0; i < SIZE; i++){
        delete ptrArray[i];
    }
    return 0;
}

int memoryAllocationMain(){
    smartPointer();
    legacyPointer();

    return 0;
}