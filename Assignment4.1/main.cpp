#include <iostream>
#define Max_matrix_size 400
//Assignment 4 (Final Version)
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

element stack[Max_matrix_size];
int top = 0; //index of the stack
bool target = false;

void add(element position)
{
    stack[++top] = position;
}

element pop()
{
    if(top>-1)
    {
        return stack[top--];
    }
}

int main()
{
    int m;
    int n;
    int pass_row;
    int pass_col;

    moving mv[8];
    mv[0].horiz = 0, mv[0].vert=-1; //N
    mv[1].horiz = +1,mv[1].vert=-1; //NE
    mv[2].horiz = +1,mv[2].vert=0;  //E
    mv[3].horiz = +1,mv[3].vert=+1; //SE
    mv[4].horiz = 0, mv[4].vert=+1; //S
    mv[5].horiz = -1,mv[5].vert=+1; //SW
    mv[6].horiz = -1,mv[6].vert=0;  //W
    mv[7].horiz = -1,mv[7].vert=-1; //NW

    if(pass_row == 0 && pass_col ==0)
    {
        target = true;
    }

    cin >> m >> n >> pass_row >> pass_col;
    int maze[m+2][n+2];
    int mark[m+2][n+2];

    for(int i=0; i<m+2; i++)
    {
        for(int j=0; j<n+2; j++)
        {
            maze[i][j]=1;
            mark[i][j]=0;
        }
    }

    for(int i=1; i<=m; i++)
    {
        for(int j=1; j<=n; j++)
        {
            cin >> maze[i][j];
        }
    }

    int row;
    int col;
    int next_row;
    int next_col;
    int dir;
    top = 0;
    element position;
    bool found = false;

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
            if(next_row==m && next_col==n)
            {
                //direction ==3, find again
                if(dir==3)
                {
                    dir++;
                    continue;
                }
                //found the path and it pass through the specific point
                else if(target==true)
                {
                    found = true;
                    position.row = row;
                    position.col = col;
                    position.dir = ++dir;
                    add(position);
                }
                //find again
                else
                {
                    position = pop();
                    row = position.row;
                    col = position.col;
                    dir = position.dir;
                }
            }
            else if(!maze[next_row][next_col] && !mark[next_row][next_col])
            {
                if(row==m && col+1==n && dir!=3)
                {
                    dir++;
                    continue;
                }
                mark[next_row][next_col] = 1;
                position.row = row;
                position.col = col;
                position.dir = dir++;
                add(position);
                row = next_row;
                col = next_col;
                if((row==pass_row &&col==pass_col) || (pass_row==0 && pass_col==0))
                {
                    target = true;
                }
                dir =0;
            }
            else
                dir++;
        }
    }

    if(found == true && target ==true)
    {
        for(int i=0; i<=top; i++)
        {
            cout << stack[i].row << " " << stack[i].col;
            cout << endl;
        }
        cout << m << " " <<n;
    }
    else
    {
        cout <<"The maze does not have a path.";
    }
    return 0;
}
