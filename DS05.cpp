#include<iostream>
#include<string>

#define MAX_STACK_SIZE 100  /* maximum stack size */

using namespace std;

/** �ŧi�����ܼ� **/
typedef enum {
    Lparen, Rparen, Plus, Minus, Times, Divide, Mod, Eos, Operand
} precedence;

int Stack[MAX_STACK_SIZE];  /* global stack */
string expr;                /* �s������J�Afunction�D�n�B�檺�r�� */
string postfix_expr;        /* �s��postfix��ܦ� */
int top;

int isp[8] = {0,19,12,12,13,13,13,0};           /* in-stack precedence */
int icp[8] = {20,19,12,12,13,13,13,0};          /* incoming precedence */

/** �Ҧ��|�Ψ쪺function **/
bool check();                                   /* �ˬd�B�⦡�O�_�X�k */
precedence get_token( char *symbol, int *n );   /* �q�B�⦡��token */
precedence get_remaining_token( int n );        /* �B�⦡�짹����,stack���i���٦��ѤU���B��Ÿ�,�@�ֿ�X */
void stack_full();
void stack_empty();
void push(int item);
int pop();
void print_token(int token_num);                /* ��X��Ǫ�ܦ���token,�o��ڪ��{�������ӿ�X,���ӱ��r���,����@�ֿ�X,�P�Ǥ]�i�H�b�o�����X */
void postfix();                                 /* ���Ǫ�ܦ����Ǫ�ܦ� */
int eval();                                     /* �p���Ǫ�ܦ������� */

/********************************************************************************************/
/** �ϥ� while( getline() )�@��@������,�C��@�����@���H�U�ʧ@�G                    **/
/** (1) �ˬd��J���B�⦡�O�_�X�k,���X�k�N��X"The expression is invalid." �õ����{��    **/
/** (2) �O�X�k�B�⦡,�I�spostfix()�ন��Ǫ�ܦ�                                         **/
/** (3) �I�seval()�p���Ǫ�ܦ�������,�ÿ�X�D�حn�D����X�榡                         **/
/********************************************************************************************/
int main(){

    while( getline(cin,expr) ) {
        if( check() == true ) {                 /* �I�scheck()�ˬdexpr�O�_�����ĹB�⦡�A�O���ܤ~�|���ഫ�M�B�� */
            int answer = 0;                     /* �s�񵪮�,�C��@����곣�n�k�s */

            postfix();                          /* �������� (expr -> postfix_expr) */
            expr = "";                          /* �M��expr */
            expr = postfix_expr + ' ' ;         /* �b��Ǫ�ܦ��̫᭱��eos�A�����s��expr (�����B�O�]��eval()�]�O�ϥ�expr�ӹB��) */
            answer = eval();                    /* �p���Ǫ�ܦ������� */

            cout<< postfix_expr << " = " << answer << endl;  /* ��X�D�سW�w���榡 */
        }
        else  /* �D�k�B�⦡ */
            cout<< "The expression is invalid." << endl;
    }
    return 0;
};
/**************************************************************************************/
/** �ˬdexpr�O�_�X�k                                                                **/
/** "²���ˬd"���ˬd�B�⦡���r���O�_�X�k,�H�άA�����S�����k�t��                  **/
/** "�i���ˬd"�|�i�@�B�ˬd�r���e�᪺���Y�B�榡�O�_�X�k,�Ҧp����s���ӹB��Ÿ� **/
/** �`�N: �i���ˬd�u�A�Φb�Ӧ�ƪ����p�U                                          **/
/*************************************************************************************/
bool check(){
    bool valid = true;
    int operand_num = 0, operator_num = 0, paren_num = 0;    /** �Ʀr���ƶq�B�B��Ÿ����ƶq�B�A�����ƶq **/
    int tokenType[expr.size()] = {0};                        /** �ΨӦs��expr�C�Ӧr����type: '('=0, ')'=1, �B��Ÿ�=2, �Ʀr=3, Eos=4 **/

/** ²���ˬd **/
    if( expr.size() < 4 || expr[expr.size()-1] != ' ' )      /** expr�����פp��4�A�άO�̫᭱�S��Eos,�D�k **/
        valid = false;
    /** �ھڦr���B�z�A�s��r���������H�έp���������ƶq�A�p�G���D�k�r���N��valid�]��false�����ˬd **/
    for( int i = 0 ; ( valid && i < expr.size() ) ; i++ ){
        switch( expr[i] ){
            case '(' : tokenType[i] = 0;  paren_num++;     break;
            case ')' : tokenType[i] = 1;  paren_num--;     break;
            case '+' : tokenType[i] = 2;  operator_num++;  break;
            case '-' : tokenType[i] = 2;  operator_num++;  break;
            case '/' : tokenType[i] = 2;  operator_num++;  break;
            case '*' : tokenType[i] = 2;  operator_num++;  break;
            case '%' : tokenType[i] = 2;  operator_num++;  break;
            case '0' : tokenType[i] = 3;  operand_num++;   break;
            case '1' : tokenType[i] = 3;  operand_num++;   break;
            case '2' : tokenType[i] = 3;  operand_num++;   break;
            case '3' : tokenType[i] = 3;  operand_num++;   break;
            case '4' : tokenType[i] = 3;  operand_num++;   break;
            case '5' : tokenType[i] = 3;  operand_num++;   break;
            case '6' : tokenType[i] = 3;  operand_num++;   break;
            case '7' : tokenType[i] = 3;  operand_num++;   break;
            case '8' : tokenType[i] = 3;  operand_num++;   break;
            case '9' : tokenType[i] = 3;  operand_num++;   break;
            case ' ' : if( i != expr.size()-1 )  valid = false;  tokenType[i] = 4;  break;   /** Eos���O�bexpr�̫᭱�A�N�O�D�k **/
            default  : valid = false;                                                        /** ���F�W�z�o�Ǧr���H�~�A�]�N�O�S���i�J�䤤�@��case�A�N�O�D�k�r�� **/
        }
    }
    if( valid && ( paren_num!=0 || (operand_num - operator_num)!=1 ))   /** �A���S�����t��B�άO�B�⤸�S����n��B��l�h�@�ӡA�D�k **/
        valid = false;

    if( valid == false )    /** �p�G²���ˬd�N�D�k�F�A����return�D�k **/
        return false;

/** �i���ˬd�A�ˬd�r������m�P�e�����Y�A�ϥ�tokenType���ˬd **/
/** '(' = 0 , ')' = 1 , �B��Ÿ� = 2 , �Ʀr = 3               **/
    if( ( tokenType[0]==1 || tokenType[0]==2 ) )                            /** expr�Ĥ@�Ӧr�����O���A���μƦr,�D�k **/
        return false;
    if( tokenType[expr.size()-2] == 0 || tokenType[expr.size()-2] == 2 )    /** Eos�e�@�Ӧr�����O�k�A���μƦr,�D�k **/
        return false;
    /** �qexpr�ĤG�Ӧr���}�l�ˬd�e�����Y�A�ˬd��Eos�e�@�Ӧr������A�Y�o�{�D�k�N�פ�j�� **/
    for( int i = 1 ; ( valid && i < expr.size()-1 ) ; i++ ){
        switch( tokenType[i] ){
            case 0: /** '(' ���A���A�e���Y�O�k�A���μƦr�A�᭱�Y�O�k�A���ιB��Ÿ��A�D�k **/
                    if( tokenType[i-1] == 1 || tokenType[i-1] == 3 )  valid = false;
                    if( tokenType[i+1] == 1 || tokenType[i+1] == 2 )  valid = false;
                    break;
            case 1: /** ')' �k�A���A�e���Y�O���A���ιB��Ÿ��A�᭱�Y�O���A���μƦr�A�D�k **/
                    if( tokenType[i-1] == 0 || tokenType[i-1] == 2 )  valid = false;
                    if( tokenType[i+1] == 0 || tokenType[i+1] == 3 )  valid = false;
                    break;
            case 2: /** �B��Ÿ� �A�e���Y�O���A���ιB��Ÿ��A�᭱�Y�O�k�A���ιB��Ÿ��A�D�k **/
                    if( tokenType[i-1] == 0 || tokenType[i-1] == 2 )  valid = false;
                    if( tokenType[i+1] == 1 || tokenType[i+1] == 2 )  valid = false;
                    break;
            case 3: /** �Ʀr �A�e���Y�O�k�A���μƦr�A�᭱�Y�O���A���μƦr�A�D�k **/
                    if( tokenType[i-1] == 1 || tokenType[i-1] == 3 )  valid = false;
                    if( tokenType[i+1] == 0 || tokenType[i+1] == 3 )  valid = false;
                    break;
        }
    }

    return valid;   /* �i���ˬd�����A�^�ǬO�_�X�k */
};
/*************************************************************************************************/
/** �qexpr����token��return                                                                     **/
/** �ϥ�pass by reference���n����,�Ӹ`�аѦ� https://openhome.cc/Gossip/CppGossip/PassBy.html **/
/*************************************************************************************************/
precedence get_token( char *symbol, int *n ) {
    *symbol = expr[(*n)++];         /* �qexpr���@�Ӥ@�ӧ�r��,�ھڦr��return */
    switch( *symbol ) {
        case '(' : return Lparen;
        case ')' : return Rparen;
        case '+' : return Plus;
        case '-' : return Minus;
        case '/' : return Divide;
        case '*' : return Times;
        case '%' : return Mod;
        case ' ' : return Eos;
        default  : return Operand;
    }
};
/*******************************************************************************/
/** �ഫ����Ǫ�ܦ���,�B�z��expr��stack���i���٦��Ѿl��operator�Spop�X��  **/
/** �o�̱Npop�X�Ӫ��F���ഫ���O�ܦ�precedence��type                         **/
/*******************************************************************************/
precedence get_remaining_token( int n ){
    switch( n ){
        case 0 : return Lparen;
        case 1 : return Rparen;
        case 2 : return Plus;
        case 3 : return Minus;
        case 4 : return Times;
        case 5 : return Divide;
        case 6 : return Mod;
        case 7 : return Eos;
    }
};
void stack_full(){
    cout << "Stack is full." << endl;
    exit(0);
};
void stack_empty(){
    cout << "Stack is empty." << endl;
    exit(0);
};
void push(int item){
    if( top >= MAX_STACK_SIZE-1 )
        stack_full();
    Stack[++top] = item;
};
int pop(){
    if( top == -1 )
        stack_empty();
    return Stack[top--];
};
/****************************************************************************************************/
/** print_token() ��v���̬O�N token ��X�X��                                                     **/
/** �U�гo�̧令�N token ���� postfix_expr �᭱,�ഫ���̫�~�@�ֿ�X postfix_expr                **/
/** �`�N: switch ���C�� case �̫᭱�@�w�n�� break,���D����return�F�蹳get_remaining_token()����  **/
/*****************************************************************************************************/
void print_token(int token_num){
    switch( token_num ){
        case 0: postfix_expr = postfix_expr + '(';   break;
        case 1: postfix_expr = postfix_expr + ')';   break;
        case 2: postfix_expr = postfix_expr + '+';   break;
        case 3: postfix_expr = postfix_expr + '-';   break;
        case 4: postfix_expr = postfix_expr + '*';   break;
        case 5: postfix_expr = postfix_expr + '/';   break;
        case 6: postfix_expr = postfix_expr + '%';   break;
        case 7: postfix_expr = postfix_expr + ' ';   break;
    }
};
/*************************************************************************/
/** postfix() �N���Ǫ�ܦ��ഫ����Ǫ�ܦ�                            **/
/*************************************************************************/
void postfix(){
    char symbol;
    precedence token;
    int n = 0;           // ���Ǫ�ܦ���index
    top = 0;             // stack top
    postfix_expr = "";   // �ΨӦs���Ǫ�ܦ�,����l�Ƭ��Ŧr��
    Stack[0] = Eos;      // ����eos���stack���Y

    /** ��for�j��q��J��expr���Ǫ�ܦ��r��@�Ӥ@�ӧ�token,������Eos����(�o��Eos���|�Q��istack��) **/
    for( token = get_token( &symbol , &n ) ; token != Eos ; token = get_token( &symbol , &n ) ){
        /** token�O�Ʀr,������ipostfix_expr **/
        if( token == Operand ){
            postfix_expr = postfix_expr + symbol;
        }
        /** token�O�k�A��,���_��stack��������pop�X�Өå�ipostfix_expr,����I�쥪�A��,�̫�⥪�A��pop�X�� **/
        else if( token == Rparen ){
            while ( Stack[top] != Lparen )
                print_token( pop() );

            pop();
        }
        /** token�Ooperator,����stack���u���v�j�󵥩�ۤv��operator pop�X�Өå�ipostfix_expr��,�̫�A��token push�istack **/
        else{
            while( isp[Stack[top]] >= icp[token] )
                print_token( pop() );

            push( token );
        }
    }
    /** expr�짹�B�z����,stack���i��|���Ѿl��operator�٨Spop�X��,�o���L�̥���pop�X�Өñ���postfix_expr�᭱,����@�}�l��istack[0]����Eos���� **/
    while( ( token = get_remaining_token( pop() )) != Eos )
        print_token( token );
};
/****************************************************************************************************/
/** eval()�Ψӭp��expr������,�`�N: �o�̪�expr�w�g�bmain()���Y����postfix_expr,�O��Ǫ�ܦ�      **/
/****************************************************************************************************/
int eval(){
    precedence token;
    char symbol;
    int op1, op2;   // operand
    int n = 0;      // expr��index
    top = 0;        // stack top
    token = get_token( &symbol , &n );  //�qexpr����token

    while( token!=Eos ){
        /** token�O�Ʀr,�নint��push�istack�� **/
        if( token == Operand )
            push( symbol-'0' );
        /** token�O�B��Ÿ�,�qstack��pop��ӼƦr�X�Ӱ��B��,�N�B�⵲�Gpush�istack�� **/
        else{
            op2 = pop();
            op1 = pop();
            switch( token ){
                case Plus:   push( op1+op2 );  break;   /* �[ */
                case Minus:  push( op1-op2 );  break;   /* �� */
                case Times:  push( op1*op2 );  break;   /* �� */
                case Divide: push( op1/op2 );  break;   /* �� */
                case Mod:    push( op1%op2 );  break;   /* mod */
            }
        }
        token = get_token( &symbol , &n );  //�qexpr����token
    }
    return pop();  /** �w�g�B�z��expr�F, return �B�⵲�G **/
};
