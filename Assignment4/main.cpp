#include <iostream>
#define Max_define_size 400
//Assignment 4 (basic version)
using namespace std;

typedef struct
{
    int vert;
    int horiz;
} moving;

typedef struct
{
    int row;
    int col;
    int dir;
} element;

element stack[Max_define_size];
int top=0; //index of stack

//add current position to the stack
void add(element position)
{
    stack[++top] = position;
}

//pop out the element in the stack
element pop()
{
    if(top>-1)
    {
        return stack[top--];
    }
}

int main()
{
    int m; //row
    int n; //column
    int pass_row; //specific row need to pass
    int pass_col; //specific column need to pass

    //moving direction
    moving mv[8];
    mv[0].horiz = 0,  mv[0].vert = -1;  //N
    mv[1].horiz = +1, mv[1].vert = -1;  //NE
    mv[2].horiz = +1, mv[2].vert = 0;   //E
    mv[3].horiz = +1, mv[3].vert = +1;  //SE
    mv[4].horiz = 0,  mv[4].vert = +1;  //S
    mv[5].horiz = -1, mv[5].vert = +1;  //SW
    mv[6].horiz = -1, mv[6].vert = 0;   //W
    mv[7].horiz = -1, mv[7].vert = -1;  //NW

    cin >> m >> n >> pass_row >> pass_col;
    int maze[m+2][n+2]; //matrix input by user
    int mark[m+2][n+2]; //matrix used to mark the route

    //set 1 to the outside of the maze and 0 to the mark matrix
    for(int i=0; i<m+2; i++)
    {
        for(int j=0; j<n+2; j++)
        {
            maze[i][j]=1;
            mark[i][j]=0;
        }
    }

    //input value to the matrix
    for(int i=1; i<=m; i++)
    {
        for(int j=1; j<=n; j++)
        {
            cin >> maze[i][j];
        }
    }

    int row; //current row
    int col; //current column
    int next_row; //next row
    int next_col; //next column
    int dir; //direction
    bool found = false; //found the path?
    element position; //current position
    mark[1][1] = 1; //starting of the mark matrix = 1
    top = 0; //index of stack set to 0
    stack[0].row = 1;
    stack[0].col = 1;
    stack[0].dir = 1;

    //path is not found
    while(top>-1 && found==false)
    {
        position = pop();
        row = position.row;
        col = position.col;
        dir = position.dir;
        while(dir<8 && found==false)
        {
            next_row = row + mv[dir].vert;
            next_col = col + mv[dir].horiz;
            //found the path to the destination
            if(next_row==m && next_col==n)
            {
                found=true;
            }
            else if(!maze[next_row][next_col] && !mark[next_row][next_col])
            {
                mark[next_row][next_col] = 1;
                position.row = row;
                position.col = col;
                position.dir = ++dir; //avoid to check the checked direction
                add(position);        //put it into stack
                row = next_row;
                col = next_col;
                dir = 0;
            }
            else
            {
                ++dir;
            }

        }
    }
    //output the result
    if(found == true)
    {
        for(int i=0; i<=top; i++)
        {
            cout << stack[i].row << " " << stack[i].col;
            cout << endl;
        }
        cout << m << " " << n;
    }
    else
    {
        cout << "The maze does not have the path";
    }
    return 0;
}
