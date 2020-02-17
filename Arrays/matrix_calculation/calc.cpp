#include <iostream>
#include <iomanip>
#define N 3
using namespace std;

void inputMatrix(int [][N]); //input matrix
void outputMatrix(int [][N]); //output the matrix
void multipleMatrix(int [][N], int [][N], int [][N]); //matrix multiplication
void addMatrix(int [][N], int [][N], int [][N]); //matrix addition
void subMatrix(int [][N], int [][N], int [][N]); //matrix subtraction
void transposeMatrix(int [][N], int [][N]); //transpose matrix
void instruction(); //instruction
//void init(); //initialization

int main() {
    int matrix1[N][N] = { 0 };
    int matrix2[N][N] = { 0 };
    int result[N][N] = { 0 };
    string command;
    instruction();
    while(cin >> command){
        if(command == "add"){
            inputMatrix(matrix1);
            inputMatrix(matrix2);
            addMatrix(matrix1, matrix2, result);
            outputMatrix(result);
            cin >> command;
        }
        else if(command == "sub"){
            inputMatrix(matrix1);
            inputMatrix(matrix2);
            subMatrix(matrix1, matrix2, result);
            outputMatrix(result);
            cin >> command;
        }
        else if(command == "mul"){
            inputMatrix(matrix1);
            inputMatrix(matrix2);
            multipleMatrix(matrix1, matrix2, result);
            outputMatrix(result);
            cin >> command;
        }
        else if(command == "tran"){
            inputMatrix(matrix1);
            transposeMatrix(matrix1, result);
            outputMatrix(result);
            break;
        }
        else if(command == "e"){
            exit(0);
        }
        else{
            instruction();
            cin >> command;
        }
    }
    return 0;
}

void inputMatrix(int matrix[N][N]){
    for(int i = 0;i < N;i++){
        for(int j = 0;j < N;j++){
            cin >> matrix[i][j];
        }
    }
}

void outputMatrix(int matrix[N][N]){
    for(int i = 0;i < N;i++){
        for(int j = 0;j < N; j++){
            cout << setw(3) << matrix[i][j];
        }
        cout << endl;
    }
}

void multipleMatrix(int matrixA[N][N], int matrixB[N][N], int matrixC[N][N]){
    for(int i = 0;i < N;i++){
        for(int j = 0;j < N;j++){
            int sum = 0;
            for(int k = 0;k < N;k++){
                sum = sum + matrixA[i][k] * matrixB[k][j];
            }
            matrixC[i][j] = sum;
        }
    }
}

void addMatrix(int matrixA[N][N], int matrixB[N][N], int matrixC[N][N]){
    for(int i = 0;i < N;i++){
        for(int j = 0;j < N;j++){
            matrixC[i][j] = matrixA[i][j] + matrixB[i][j];
        }
    }
}

void subMatrix(int matrixA[N][N], int matrixB[N][N], int matrixC[N][N]){
    for(int i = 0;i < N;i++){
        for(int j = 0;j < N;j++){
            matrixC[i][j] = matrixA[i][j] - matrixB[i][j];
        }
    }
}

void transposeMatrix(int matrixA[N][N], int matrixC[N][N]){
    for(int i = 0;i < N;i++){
        for(int j = 0;j < N;j++){
            matrixC[i][j] = matrixA[j][i];
        }
    }
}

void instruction(){
    cout << "Commands are listed in the below" << endl;
    cout << "Addition --> add" << endl;
    cout << "Subtraction --> sub" << endl;
    cout << "Multiplication --> mul" << endl;
    cout << "Transpose --> tran" << endl;
    cout << "Exit -- > e" << endl;
}