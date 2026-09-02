#include <iostream>
#include <vector>
#include <string>

using namespace std;

int hellomain() {
    
    vector<string> msg {"Hello", "C++", "World", "from", "VS Code", "and the C++ extension!"};
    //As long as there is a string in msg print then add a space.
    for (const string& word : msg)
    {
        cout << word << " ";
    }
    cout << endl;
    return 0;
}