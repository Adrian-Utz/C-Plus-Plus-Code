#include <iostream>
#include <cmath>
#include <cctype>
#include <string>
#include <stack>
#include <stdexcept>
#include <cctype>
#include <stdexcept>

using namespace std;

/*
A calculator through the command line.

Last Update: 8/27/2026
Written on 8/19/2026
Written by: AJ Utz
*/

//Check returns a check if a given char is a valid mathematical operator.
bool isOperator(char ch){
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

//Give each operator a value. Order of operations.
int precedence(char op){
    if(op == '^') return 3;
    if(op == '*' || op == '/') return 2;
    if(op == '+' || op == '-') return 1;
    return -1;
}

/* Because we use a string for input we can have multiple operators in one line */
double performOperation(double left, double right, char op){
    switch(op){
        case '+': return left + right;
        case '-': return left - right;
        case '*': return left * right;
        case '/': if(right == 0) throw runtime_error("Division by Zero"); //Division by 0 not allowed
                  return left / right;
        case '^': return pow(left, right);
        default: throw invalid_argument("Invalid operator");
    }
}

/* Take the string input and split the values from the operators */
double evaluateExpression(const string& input){
    stack<double> values;
    stack<char> ops;

    bool expectValue = true;
    //break down the string statement piece by piece
    for(size_t i = 0; i < input.size(); ++i){
        char ch = input[i];
        if(isspace(static_cast<unsigned char>(ch))) continue;

        if(isdigit(static_cast<unsigned char>(ch)) || ch == '.'){ //Watch out for decimals
            size_t end = i;
            bool decimalPoint = false;
            bool hasDigit = false;
            while(end < input.size() && (isdigit(static_cast<unsigned char>(input[end])) || input[end] == '.')){
                //Check for multiple '.' 
                if(input[end] == '.'){
                    if(decimalPoint) throw invalid_argument("Invalid number");
                    decimalPoint = true;
                }else{
                    hasDigit = true;
                }
                ++end;
            }
            if(!hasDigit) throw invalid_argument("Invalid number");
            values.push(stod(input.substr(i, end - i)));
            i = end - 1;
            expectValue = false;
        //Make sure there are operators before and after '()' else send a error message, also check for unmatched '()'
        }else if(ch == '('){
            if(!expectValue) throw invalid_argument("Missing operator before '('");
            ops.push(ch);
            expectValue = true;
        }else if(ch == ')'){
            if(expectValue) throw invalid_argument("Missing value before ')'");
            while(!ops.empty() && ops.top() != '('){
                if(values.size() < 2) throw invalid_argument("Missing value");
                double b = values.top();
                values.pop();
                double a = values.top();
                values.pop();

                char op = ops.top();
                ops.pop();

                values.push(performOperation(a, b, op));
            }
            if(ops.empty()) throw invalid_argument("Unmatched ')'");
            ops.pop();
            expectValue = false;
        }else if(isOperator(ch)){
            if(expectValue){
                if(ch != '-') throw invalid_argument("Unexpected operator");
                values.push(0);
                ops.push(ch);
                continue;
            }
            while(!ops.empty() && isOperator(ops.top()) &&
                  (precedence(ops.top()) > precedence(ch) ||
                   (precedence(ops.top()) == precedence(ch) && ch != '^'))){
                if(values.size() < 2) throw invalid_argument("Missing value");
                double b = values.top();
                values.pop();
                double a = values.top();
                values.pop();

                char op = ops.top();
                ops.pop();

                values.push(performOperation(a, b, op));
            }
            ops.push(ch);
            expectValue = true;
        }else{
            throw invalid_argument("Invalid character");
        }
    }

    if(input.empty() || expectValue) throw invalid_argument("Incomplete expression");
    while(!ops.empty()){
        if(ops.top() == '(') throw invalid_argument("Unmatched '('");
        if(values.size() < 2) throw invalid_argument("Missing value");
        double b = values.top();
        values.pop();
        double a = values.top();
        values.pop();

        char op = ops.top();
        ops.pop();

        values.push(performOperation(a, b, op));
    }
    if(values.size() != 1) throw invalid_argument("Invalid expression");
    return values.top();
}

int calculatorMain(){
    string input;
    char tempchar;
    bool validation = true; //Switch this to false if you don't want the "Is this correct?" prompt

    cout << "Accepted operators: +  -  *  /  ()  ^" << endl;
    while(true){
        cout << "Enter the calculation: ";
        getline(cin >> ws, input);

        if(validation == true){
            cout << "You entered: " << input << "\nIs this correct? y/n: ";
            cin >> tempchar;
            if(tolower(static_cast<unsigned char>(tempchar)) != 'y'){
                cout << "Try again y/n: ";
                cin >> tempchar;
                if(tolower(static_cast<unsigned char>(tempchar)) != 'y') return 0;
                continue;
            }
        }

        try{
            cout << "Result: " << evaluateExpression(input) << endl;
        }catch(const exception& e){
            cerr << "Error: " << e.what() << endl;
        }
        return 0;
    }
}