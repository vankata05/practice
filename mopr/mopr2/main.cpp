#include <iostream>
#include <fstream>
#include <string>

using namespace std;

double** readFile_(string filename){
    ifstream file(filename);

    double** matrix = new double*[4];
    for(int i = 0; i < 5; i++){
        matrix[i] = new double[5];
    }

    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 4; j++){
            file >> matrix[i][j];
        }
    }

    return matrix;
}

double** priceMatrix(){
    double** matrix = new double*[4];
    for(int i = 0; i < 4; i++){
        matrix[i] = new double[4];
    }

    for(int i = 0; i < 4; i++){
        matrix[0][i] = 0.129;
    }  

    for(int i = 0; i < 4; i++){
        matrix[1][i] = 1.461;
    }

    for(int i = 0; i < 4; i++){
        matrix[2][i] = 85.07;
    }

    for(int i = 0; i < 4; i++){
        matrix[3][i] = 0.132;
    }

    return matrix;
}

double** multiplyMatrix(double** a, double** b){
    double** matrix = new double*[4];
    for(int i = 0; i < 4; i++){
        matrix[i] = new double[4];
    }

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            matrix[i][j] = 0;
            for(int k = 0; k < 4; k++){
                matrix[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    return matrix;
}

void printMatrix(double** matrix){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void printDifference(double** a, double** b){
    for(int i = 0; i < 4; i++){
        cout << a[4][i] - b[i][0] << " ";
    }
    cout << endl;
}

int main(){
    double** matrix = readFile_("./sample.txt");
    cout << "Input:" << endl;
    printMatrix(matrix);
    cout << "\nOutput:" << endl;
    printDifference(matrix, multiplyMatrix(matrix, priceMatrix()));
    return 0;
}