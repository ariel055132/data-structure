#include<iostream>
using namespace std;

int factorial(int n);

int main(){
    int input;
    while(cin >> input){
        cout << factorial(input) << endl;
    }
    return 0;
}

int factorial(int n){
    long long ans = 1;
    if (n == 0 || n == 1)
    {
        ans = 1;
        return ans;
    }
    else{
        for (int i = 2; i <= n; i++)
        {
            ans = ans * i;   
        }
        return ans;
    }
}