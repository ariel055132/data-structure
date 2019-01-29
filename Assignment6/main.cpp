#include <iostream
#include <malloc.h>
#include <stdlib.h>
#include <string>
#include <math.h>

using namespace std;

typedef struct polynode *polypointer;
typedef struct polynode
{
    int coef;   //coefficients of polynomial
    int expon;  //power of the coefficients
    polypointer link; //node
};
polypointer a,b,d; // a,b is input of polynomial, d is the result

//function that push first polynomial to a (record)
void push_a(polypointer *top,polynode temp_node)
{
    polypointer temp = (polypointer)malloc(sizeof(polynode));
    temp->coef = temp_node.coef;   // put the coef to linked list coef
    temp->expon = temp_node.expon; // put the exponential to linked list expon
    temp->link = *top;             // put the top to linked list node
    *top = temp;                  // top is the index of the stack
}

//function that push second polynomial to b (record)
void push_b(polypointer *top,polynode temp_node)
{
    polypointer temp = (polypointer)malloc(sizeof(polynode));
    temp->coef = temp_node.coef;   // put the coef to linked list coef
    temp->expon = temp_node.expon; // put the exponential to linked list expon
    temp->link = *top;             // put the top to linked list node
    *top = temp;                  // top is the index of the stack
}

//function that push the result polynomial to d
void push_d(polypointer *top,polynode temp_node)
{
    polypointer temp = (polypointer)malloc(sizeof(polynode));
    temp->coef = temp_node.coef;   // put the coef to linked list coef
    temp->expon = temp_node.expon; // put the exponential to linked list expon
    temp->link = *top;             // put the top to linked list node
    *top = temp;                  // top is the index of the stack
}

//compare the exponentials of a and b (the larger power will be put into the result, calculate when two of them are the same)
int compare(int a, int b)
{
    if(a>b)
    {
        return 1;
    }
    else if(a<b)
    {
        return -1;
    }
    else if(a==b)
    {
        return 0;
    }
}

//determine the input is positive or negative
int sign_test(char a)
{
    if(a=='+' || a=='(') //positive number situation
    {
        return +1;
    }
    else if(a=='-') //negative number situation
    {
        return -1;
    }
}

//erase the polynomial pointed to by ptr
void poly_erase(polypointer *ptr)
{
    polypointer temp;
    while(*ptr)
    {
        temp = *ptr;
        *ptr = (*ptr)->link;
        free(temp);
    }
}

//convert substitute from string to int
int str_to_int(string substitute)
{
    int sub_no=0;     // result of substitute
    int read_sub;   // read the digit in the string
    int times = 1;  // multiplier
    int sign = 1;    //1 is positive number , -1 is negative number

    if(substitute[0]=='-'){ //negative number
        sign = -1;
        for(int i=1;i<substitute.length();i++){
            sub_no*=10;
            sub_no+=substitute[i]-'0';
        }
    }
    else{ //positive number
         for(int i=0;i<substitute.length();i++){
            sub_no*=10;
            sub_no+=substitute[i]-'0';
         }
    }
    sub_no*=sign;
    return sub_no;
}

//determine the input is number or not
bool isNum(char a)
{
    if(a-'0'>= 0 && a-'0'<=9) //it is number
        return true;
    else // not number
        return false;
}

//add two polynomials (DS notes)
polypointer calculate(polypointer a, polypointer b, char op)
{
    //tempnode --> last --> null
    polypointer last = NULL;
    polynode tempnode;
    int sum = 0; //result
    last = (polypointer)malloc(sizeof(polynode));
    last = NULL; //last node is NULL
    while(a && b)    //pointer a and pointer b are not null
    {
        switch(compare(a->expon, b->expon))
        {
        case 1:  //exponential of b > exponential of a
            if(op=='+') //operator is + (add)
                tempnode.coef = b->coef;
            else if(op=='-') //operator is - (subtract)
                tempnode.coef = (b->coef)*-1;
            tempnode.expon = b->expon;
            push_d(&last, tempnode); //push to d , the container to cout the solution
            b = b->link;
            break;
        case 0:  //exponential a = exponential b
            if(op=='+') //operator is + (add)
                sum = a->coef + b->coef;
            else if(op=='-') //operator is - (subtract)
                sum = a->coef - b->coef;
            if(sum!=0)
            {
                tempnode.coef = sum;
                tempnode.expon = a->expon;
                push_d(&last, tempnode);
                sum=0;
            }
            a = a->link; //a link to next
            b = b->link; //b link to next
            break;
        case -1:  //ponexential a > exponential b
            tempnode.coef = a->coef;
            tempnode.expon = a->expon;
            push_d(&last, tempnode);
            a = a->link;
            break;
        }

    }
    //copy rest of list a and then list b
    for(; a; a = a->link)
    {
        tempnode.coef = a->coef;
        tempnode.expon = a->expon;
        push_d(&last, tempnode);
    }
    for(; b; b = b->link)
    {
        if(op=='+')
            tempnode.coef = b->coef;
        else if(op=='-')
            tempnode.coef = (b->coef)*-1;
        tempnode.expon = b->expon;
        push_d(&last, tempnode);
    }
    return last;
}

int main()
{
    int no_case = 3; // maximum number of case is 3
    string polynomial; // the polynomial needs to be input
    string substitute; //value that need to substitute to get result in line 2
    int a_ends = 0;        //store the position where input a ends;
    bool derivateA = false; //need to derivate A?
    bool derivateB = false; //need to derivate B?
    polypointer d = NULL; //pointer d (result) is null
    polypointer top_a=NULL,top_b = NULL; //stack index for a and b
    polynode tempnode;  //the node that is going to have input temporarily (book)
    int sign = 1;         //1 is positive, -1 is negative number
    char op;            //operator, add / subtract

    while(no_case>0)
    {
        no_case--;
        int s2; //save the result after turn substitute into int from string
        while(getline(cin,polynomial))
        {
            getline(cin,substitute);
            //test cout << polynomial; no problem
            //test cout << substitute; no problem
            s2 = str_to_int(substitute);
            //test cout << s2 << endl; no problem
            break;
        }
        derivateA =false, derivateB =false;
        //determine whether A/B need derivate and do addition and subtraction
        //need to derivate when it meets ' in the final of the polynomial
        //add when meet + , subtract when meet -
        for(int i=0; i<polynomial.length(); i++)
        {
            if(polynomial[i]=='\'' && i!=polynomial.length()-2) //situation to derivate A
            {
                derivateA = true;
                //cout <<"Y";
            }
            else if(polynomial[i]==')' && polynomial[i+1]==' ' && (polynomial[i+2]=='+' || polynomial[i+2]=='-') && polynomial[i+3]==' ' && polynomial[i+4]=='(')
            {
                a_ends = i+4;
            }
            else if(polynomial[i]==')' && polynomial[i+1]=='\'' &&polynomial[i+2]==' ' && (polynomial[i+3]=='+' || polynomial[i+3]=='-') && polynomial[i+4]==' ' && polynomial[i+5]=='(')
            {
                a_ends = i+5;
            }
            else if(polynomial[i]=='\'' && i==polynomial.length()-2 && polynomial[i-1]==')') //situation to derivate B
            {
                derivateB = true;
            }
            else if(polynomial[i]=='+' && polynomial[i-1]==' ') //meet + in expression
            {
                op = '+';
            }
            else if(polynomial[i]=='-' && polynomial[i-1]==' ') //meet - in expression
            {
                op = '-';
            }
        }

        //running process
        for(int i=1; i<polynomial.length(); i++) //record the first polynomial (a), i=0 is ( and I ignore it
        {
            if(polynomial[i]==')')  //end the action when it faces )
            {
                break;
            }
            if(isNum(polynomial[i])) //check whether the input is number, go into the loop when it is true, otherwise skip
            {
                sign = sign_test(polynomial[i-1]); //determine the number is positive or negative by function sign test
                if(polynomial[i+1]!='x') //constants, exponential = 0
                {
                    tempnode.coef = (polynomial[i]-'0')*sign; //tempnode->coef is wrong (not point to a pointer??)
                    tempnode.expon = 0;                       //constants exponential is 0
                }
                else if(polynomial[i+1]=='x' &&polynomial[i+2]!='^') //exponential = 1 , not show exponential
                {
                    tempnode.coef = (polynomial[i]-'0') *sign;
                    tempnode.expon = 1;     // x with 1 power
                    i = i+1;
                }
                else //exponential >1str_to_int(substitute);
                {
                    tempnode.coef = (polynomial[i]-'0') *sign;
                    tempnode.expon = polynomial[i+3]-'0';
                    i = i+3;
                }
                if(derivateA == true)      //need to derivate A
                {
                    tempnode.coef = tempnode.coef * tempnode.expon; //derivate: coef = coefficient*exponential
                    tempnode.expon--;                               //derivation steps
                    if(tempnode.expon==-1)                          //process that need to stop derivation immediately
                        break;
                }
                push_a(&top_a,tempnode); //push it to a by function push_a
            }
            else if(polynomial[i]=='x' && (polynomial[i-1]=='(' || polynomial[i-1]=='+' || polynomial[i-1]=='-'))   //coefficient is 1
            {
                sign = sign_test(polynomial[i-1]);
                if(polynomial[i+1]!='^')  //exponential = 1
                {
                    tempnode.coef = sign;
                    tempnode.expon = 1;
                }
                else  //exponential >1
                {
                    tempnode.coef = sign;
                    tempnode.expon = polynomial[i+2]-'0';
                    i = i+2;
                }
                if(derivateA == true)
                {
                    tempnode.coef = tempnode.coef * tempnode.expon;
                    tempnode.expon--;
                    if(tempnode.expon==-1)
                    {
                        break;
                    }
                }
                push_a(&top_a, tempnode);
            }
        }

        for(int i=a_ends; i<polynomial.length(); i++) //record the second polynomial (b)
        {
            if(polynomial[i]==')')
            {
                break;
            }
            if(isNum(polynomial[i]))
            {
                sign = sign_test(polynomial[i-1]); //determine the number is positive or negative by function sign test
                if(polynomial[i+1]!='x') //constants, exponential = 0
                {
                    tempnode.coef = (polynomial[i]-'0')*sign; //tempnode->coef is wrong (not point to a pointer??)
                    tempnode.expon = 0;
                }
                else if(polynomial[i+1]=='x' &&polynomial[i+2]!='^') //exponential = 1 , not show exponential
                {
                    tempnode.coef = (polynomial[i]-'0') *sign;
                    tempnode.expon = 1;
                    i = i+1;
                }
                else  //exponential >1
                {
                    tempnode.coef = (polynomial[i]-'0') *sign;
                    tempnode.expon = polynomial[i+3]-'0';
                    i=i+3;
                }
                if(derivateB == true)
                {
                    tempnode.coef = tempnode.coef * tempnode.expon;
                    tempnode.expon--;
                    if(tempnode.expon==-1)
                    {
                        break;
                    }
                }
                push_b(&top_b,tempnode);
            }
            else if(polynomial[i]=='x' && (polynomial[i-1]=='(' || polynomial[i-1]=='+' || polynomial[i-1]=='-'))
            {
                sign = sign_test(polynomial[i-1]);
                if(polynomial[i+1]!='^')
                {
                    tempnode.coef = sign;
                    tempnode.expon = 1;
                }
                else
                {
                    tempnode.coef = sign;
                    tempnode.expon = polynomial[i+2]-'0';
                    i+=2;
                }
                if(derivateB == true)
                {
                    tempnode.coef = tempnode.coef * tempnode.expon;
                    tempnode.expon--;
                    if(tempnode.expon==-1)
                    {
                        break;
                    }

                }
                push_b(&top_b, tempnode);
            }

        }
        d = calculate(top_a, top_b, op);   //do the addition / subtraction

        bool highest_expon = true;     //highest exponential
        int sum = 0;
        for(; d; d = d->link) //list out d
        {
            int coef = d->coef;   //coef = d points to coef
            int expon = d->expon; //exponential = d points to expon
            if(highest_expon == true)
            {
                if(expon==0) //constants
                {
                    cout<<coef;
                }
                else if(expon==1) //power is 1
                    if(coef==1)
                        cout<<"x";
                    else if(coef==-1) //negative number
                        cout<<"-x";
                    else
                        cout<<coef<<"x";
                else if(coef==1) //coef is 1
                    cout<<"x^"<<expon;
                else if(coef==-1) //coef is -1
                    cout<<"-x^"<<expon;
                else //situation besides the above 2 situation
                    cout<<coef<<"x^"<<expon;
                highest_expon=false;
            }
            else if(expon == 0) //expon is 0
            {
                if(coef>0)
                    cout<<"+"<<coef;
                else
                    cout<<coef;
            }
            else if(expon == 1)
            {
                if(coef>0)
                {
                    if(coef==1)
                        cout<<"+x";
                    else
                        cout<<"+"<<coef<<"x";
                }
                else
                {
                    if(coef==-1)
                        cout<<"-x";
                    else
                        cout<<coef<<"x";
                }
            }
            else if(expon > 1)
            {
                if(coef>0)
                    if(coef==1)
                        cout<<"+x^"<<expon;
                    else
                        cout<<"+"<<coef<<"x^"<<expon;
                else if(coef==-1)
                    cout<<"-x^"<<expon;
                else
                    cout<<coef<<"x^"<<expon;
            }
            sum += coef * pow(s2, expon);
            // cout<<"@"<<coef<<" "<<s2<<" "<<expon<<endl;
        }
        cout<<endl;
        cout<<sum<<endl;
        poly_erase(&top_a);
        poly_erase(&top_b);
        poly_erase(&d);
    }
    return 0;

}
