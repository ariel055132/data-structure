#include <iostream>
//assignment 1
using namespace std;

void permutation(string input,int starter,int ending)
{
    for(int index=starter; index<ending; index++)
    {
       swap(input[starter],input[index]);
       permutation(input,starter+1,ending);
       swap(input[starter],input[index]);
    }
    if(starter==ending-1){
        cout << input <<" ";
    }
}
int main()
{
    string input;
    while(cin >> input)
    {
       permutation(input,0,input.length());
    }
    return 0;
}
