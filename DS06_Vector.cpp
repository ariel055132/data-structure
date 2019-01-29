#include <iostream>
#include <vector>
using namespace std;

typedef struct node{
    int num ;
    int expon ;
} ;

vector<node> A ;
vector<node> B ;
vector<node> C ;

void attach(int x , int y ,bool sec){
    node subnode ;
    subnode.num = x ;subnode.expon = y ;
    if(!sec){
       A.push_back(subnode) ;
    }
    else{
       B.push_back(subnode) ;
    }

}
int compare (int a1 , int b1 ){
    cout<<a1<<" "<<b1<<endl ;
    if(a1 > b1){
        return 1 ;
    }
    else if(a1<b1){
        return -1 ;
    }
    else{
        return 0 ;
    }
}
void calculate(bool sub2){
    while(!A.empty() && !B.empty()){
        switch(compare(A.front().expon , B.front().expon )){
        case 1 :
            C.push_back(A.front()) ;
            A.erase(A.begin()+0) ;
            break ;
        case 0 :
            if(!sub2){
                node summ ;
                summ.num = A.front().num + B.front().num ;
                summ.expon = A.front().expon ;
                C.push_back(summ) ;
                A.erase(A.begin()+0) ;B.erase(B.begin()+0) ;
            }
            else{
                node summ2 ;
                summ2.num = A.front().num - B.front().num ;
                summ2.expon = A.front().expon ;
                C.push_back(summ2) ;
                A.erase(A.begin()+0) ;B.erase(B.begin()+0) ;
            }
            break ;

        case -1 :
            if(!sub2){
                C.push_back(B.front()) ;
                B.erase(B.begin()+0) ;
            }
            else{
                B.front().num = -B.front().num ;
                C.push_back(B.front()) ;
                B.erase(B.begin()+0) ;
            }
            break ;
        }
    }
    while(!A.empty()){
        C.push_back(A.front()) ;
        A.erase(A.begin()+0) ;
    }
    while(!B.empty()){
            if(!sub2){
                C.push_back(B.front()) ;
                B.erase(B.begin()+0) ;
            }
            else{
                B.front().num = -B.front().num ;
                C.push_back(B.front()) ;
                B.erase(B.begin()+0) ;
            }

    }


}
void print(){

}
int main()
{
    string str ;
    bool minus = false  , secondPoly = false , sub = false ;
    int data = 0 , expo = 0 , counter = 0;

    while(getline(cin , str)){
        minus = false ; data = 0 ; expo = 0 ;
        counter = 0;secondPoly = false ;sub = false ;
        for(int i = 0 ; i < str.length() ; i++){

            if(str[i]<='9'&&str[i]>='0'){//number
                data = str[i]-'0' ;
                if(minus){
                    data = data - 2*data ;
                    minus = false ;
                }
                if(str[i+1]!='x'){expo = 0 ;attach(data , expo , secondPoly) ;data = 0 ;expo = 0 ;}
            }
            else if(str[i] == '-'){//not number
                minus = true ;
            }
            else if(str[i] == 'x'){
                if(str[i-1] == '+' || str[i-1] == '-' || str[i-1] == '('){
                    if(minus){data = -1 ; minus = false ;}
                    else{data = 1 ;}
                }
                if(str[i+1] == '^'){
                    i+=2 ;
                    expo = str[i]-'0' ;
                }
                else{
                    expo = 1 ;
                }
                attach(data , expo , secondPoly) ;
                data = 0 ;expo = 0 ;

            }
            else if(str[i] == '('){
                   if(counter > 0){
                        secondPoly = true ;
                    }
                    counter ++ ;
            }
            else if(str[i] == ')'){
                if(str[i+2]=='+'|| str[i+2]=='-'){
                    if(str[i+2]=='-'){sub = true ;}
                    i+=3 ;
                }
            }
            if(i == str.length()-1) {
                calculate(sub) ;
            }
        }
    }
    for(int y = 0 ; y < A.size() ; y++){
        cout << A[y].num<<"x^"<<A[y].expon <<" ";
    }
    cout<<endl ;

    for(int y = 0 ; y < B.size() ; y++){
        cout << B[y].num<<"x^"<<B[y].expon <<" ";
    }
    cout<<endl ;
    for(int y = 0 ; y < C.size() ; y++){
        cout << C[y].num<<"x^"<<C[y].expon <<" ";
    }
    return 0;
}
