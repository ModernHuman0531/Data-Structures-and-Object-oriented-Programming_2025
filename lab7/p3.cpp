#include <iostream>
#include <cmath>
using namespace std;

// TODO
/*
Inplement the sum_digit and factorial functions in int by recursion
As for the double type, we first convert the double to int using static_cast, 
Then we call the int function

<hint> double can't use %, instead we can use fmod(n, 10) to get the remainder
*/
int factorial(int n){
    if(n == 0 || n == 1)
        return 1;
    else
        return n*factorial(n-1);
}
double factorial(double n){
    int num = static_cast<int>(n);
    return factorial(num);
}
int sumDigits(int n){
    if(n == 0)
        return 0;
    else
        return n%10 + sumDigits(n/10);
}

// Get the double sum of digits to the 2 decimal places
double sumDigits(double n){
    int num = static_cast<int>(floor(n*100));
    return sumDigits(num);
}




int main() {
    int int_factorial_input, int_factorial_output;
    double double_factorial_input, double_factorial_output;

    cin >> int_factorial_input;
    cin >> double_factorial_input;

    double_factorial_output = factorial(int_factorial_input);
    int_factorial_output = factorial(double_factorial_input);
    cout << double_factorial_output << endl;
    cout << int_factorial_output << endl;

    int int_sum_input, int_sum_output;
    double double_sum_input, double_sum_output;

    cin >> int_sum_input;
    cin >> double_sum_input;
    
    double_sum_output = sumDigits(int_sum_input);
    int_sum_output = sumDigits(double_sum_input);
    cout << double_sum_output << endl;
    cout << int_sum_output << endl;

    return 0;
}