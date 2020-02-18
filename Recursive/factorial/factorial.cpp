#include<iostream>
// Use recursive to solve factorial 
using namespace std;

int factorial(int n);
int main(){
    int input;
    while(cin >> input){
        if(input <= 0){
            cout << "Input a positive number" << endl;
            cin >> input;
        }
        else if(input > 12){
            cout << "Too large" << endl;
            cin >> input;
        }
        else{
            cout << factorial(input) << endl;
        }
    }
    return 0;
}

int factorial(int n){
    int ans; //answer
    if (n == 1){
        ans = 1;
    }
    else{
        ans = n * factorial(n-1);
    }
    return ans;
}