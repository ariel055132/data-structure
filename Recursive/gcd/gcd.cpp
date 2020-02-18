#include<iostream>
// Eulicean Algorithm in recursive to find gcd
using namespace std;

int gcd(int no1, int no2);

int main(){
    int num1, num2;
    cin >> num1 >> num2;
    cout << gcd(num1, num2) << endl;
}

int gcd(int no1, int no2){
    if (no2 == 0){
        return no1;
    }
    if (no1 == 0 && no2 != 0){
        return no1;
    }
    else{
        return gcd(no2, no1%no2);
    }
}