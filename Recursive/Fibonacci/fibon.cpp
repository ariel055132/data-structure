#include<iostream>
using namespace std;

int fibon(int n);

int main(){
    int n;
    cin >> n;
    cout << fibon(n) << endl;
}

int fibon(int n){
    int ans;
    if(n == 0 || n == 1){
        ans = 1;
    }
    else{
        ans = fibon(n-1) + fibon(n-2);
    }
    return ans;
}