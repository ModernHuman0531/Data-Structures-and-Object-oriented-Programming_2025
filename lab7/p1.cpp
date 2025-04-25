#include <iostream>
#include <stack>
#include <string>

using namespace std;
bool check_if_balanced(string str){
    /*
    1. Design a stack that contain the characters
    2. Divide the input into characters and check the item using following rules:
        a. If the input is '(' or '{' or '[' then push it into the stack
        b. If the input is ')' or '}' or ']', then check if the stack is empty,
            -> if true, then return false
            -> if false, check and pop out the item in the stack
                if it's pair with the current charcter, then continue
                else return false
        c. Return the stack is empty or not.
    */
    stack<char> s;
    for(char c : str){
        if(c == '{' || c == '(' || c == '['){
            s.push(c);
        }
        else if(c == '}' || c == ']' || c == ')'){
            if(s.empty()){
                return false;
            }
        
            char top = s.top();
            s.pop();
            if((top == '{' && c == '}') || (top == '(' && c == ')') || (top == '[' && c == ']') ) {
                continue;
            }
            else
                return false;
        }
    }
    return s.empty();
}


int main(){
    string input;
    bool is_string;
    cin >> input;
    is_string = check_if_balanced(input);
    if(is_string == true){
        cout << "true" << endl;
    }
    else{
        cout << "false" << endl;
    }
    return 0;
}