#include <iostream>
#include <queue>

using namespace std;

void oper_queue(int n){
    /*
    1. Use queue(FILO) to solve the problem
    2. The queue contain N integers from 1 to N
    3. Perform the two operations until only one integers remains repeatedly:
        a. First, remove the integer at the front of the queue
        b. Nect, remove the integer at the front of the queue to the bacl of the queue 
    */
    queue<int> q;
    for(int i=1;i<=n;++i){
        q.push(i);
    }
    cout << "Discarded integers: ";
    while(q.size() > 1){
        int front = q.front();
        q.pop();
        if(q.size() >= 2)
            cout << front << ", ";
        else
            cout << front << endl;
        front = q.front();
        q.pop();
        q.push(front);
   }
   cout << "Remaining integer: " << q.front() << endl;
}
int main(){
    int n;
    while(cin >> n && n != 0){
        oper_queue(n);
    }
    return 0;
}