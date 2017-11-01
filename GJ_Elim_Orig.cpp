#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <ratio>
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

class TimeStop
{
    
public:
    void startTimeStop();
    void stopTimeStop();
    double getRealTime();
private:
    // using namespace std::chrono;
    chrono::high_resolution_clock::time_point t1;
    chrono::high_resolution_clock::time_point t2;
    chrono::duration<double> time_span;
    
};

float **loadInput(int *length);

float **loadInput(ifstream *inputMatrixFile, int *length);

bool operateMatrixFirst(float ***matrix, int length);

bool operateMatrixSecond(float ***matrix, int length);

bool operateMatrix2(float ***matrix, int length);

void printMatrix(float ***matrix, int *length);

void swapRows(float ***matrix, int FirstRow, int SecondRow);

void negateRow(float ***matrix, int rowToTransf, int length);

/*
INPUT - number of lines - then matrix of coefficients

3

2 3 4
5 6 3
9 8 6

*/

int main(int argc, char const *argv[]) {
     int length = 0;
    float **matrix;
    ofstream myResultsFile("Results.txt", fstream::out | fstream::app);
    using namespace std::chrono;
    TimeStop stopky;

    if ( argc == 3 ) {

        ifstream myMatrixFiles(argv[argc - 1], fstream::in);
        // int numbMatrixes = 0;
        // myMatrixFiles >> skipws >> length;
//        myResultFileStart.close();
//        ofstream myResultsFile("Results.txt", fstream::out | fstream::app);

        // for (int i = 0; i < numbMatrixes; ++i) {
//            for (int i = 0; i < 2; ++i) {
        // cout << "OK?"

        matrix = loadInput(&myMatrixFiles, &length);

        stopky.startTimeStop();

        if (!operateMatrixFirst(&matrix, length) || !operateMatrixSecond(&matrix, length)) {
            cout << "Failed eliminations" << endl;
            return 1;
        }

        delete[] matrix;
        stopky.stopTimeStop();
        myResultsFile << length << "\t" << stopky.getRealTime() << endl;
        // }

        myMatrixFiles.close();
        myResultsFile.close();
        return 0;
    }


    if (argc > 1) {
        ifstream myMatrixFiles(argv[argc - 1], fstream::in);
        int numbMatrixes = 0;
        myMatrixFiles >> skipws >> numbMatrixes;
//        myResultFileStart.close();
//        ofstream myResultsFile("Results.txt", fstream::out | fstream::app);

        for (int i = 0; i < numbMatrixes; ++i) {
//            for (int i = 0; i < 2; ++i) {

            stopky.startTimeStop();

            matrix = loadInput(&myMatrixFiles, &length);

            if (!operateMatrixFirst(&matrix, length) || !operateMatrixSecond(&matrix, length)) {
                cout << "Failed eliminations" << endl;
                return 1;
            }

            delete[] matrix;
            stopky.stopTimeStop();
            myResultsFile << length << "\t" << stopky.getRealTime() << endl;
        }

        myMatrixFiles.close();
        myResultsFile.close();

    } else {

        matrix = loadInput(&length);

        stopky.startTimeStop();

        if (!operateMatrixFirst(&matrix, length) || !operateMatrixSecond(&matrix, length)) {
            cout << "Failed eliminations" << endl;
            return 1;
        }

        stopky.stopTimeStop();
//        printMatrix(&matrix, &length);
        cout << "Procces duration: " << stopky.getRealTime() << " seconds " << endl;
    }




//  cout << "Starting with:"<< endl;
//  printMatrix(&matrix, &length);


//    printMatrix(&matrix, &length);



    return 0;
}

float **loadInput(int *length) {
    float **matrix = NULL;

    cout << "Number of equations ? " << endl;

    cin >> (*length);

    cout << "Coefficients of matrix, which has to be";
    cout << " inverted with Gauss-Jorden method." << endl;

    matrix = new float *[(*length)];

    for (int i = 0; i < (*length); ++i) {
        matrix[i] = new float[2 * (*length)]();
    }

    for (int i = 0; i < (*length); ++i) {
        for (int j = 0; j < (*length); ++j) {
            cin >> matrix[i][j];
        }
    }

    for (int i = 0; i < (*length); ++i) {
        matrix[i][i + (*length)] = 1;
    }

    return matrix;
}

float **loadInput(ifstream *inputMatrixFile, int *length) {
//    int (*length) = 0;
    float **matrix = NULL;

    (*inputMatrixFile) >> skipws >> (*length);
    // cout << "Mam : " << (*length) << endl;

    matrix = new float *[(*length)];

    for (int i = 0; i < (*length); ++i) {
        matrix[i] = new float[2 * (*length)]();
    }

    for (int i = 0; i < (*length); ++i) {
        for (int j = 0; j < (*length); ++j) {
            (*inputMatrixFile) >> matrix[i][j];
//            cout << matrix[i][j];
        }
//        cout << endl;
    }

    for (int i = 0; i < (*length); ++i) {
        matrix[i][i + (*length)] = 1;
    }

    return matrix;

}

bool operateMatrix2(float ***matrix, int length) {

    //Goes through diagonale
    for (int i = 0; i < length; ++i) {

        /*
           Deciding if
        */
        if ((*matrix)[i][i] <= 0) {

            int toSwap = -1;
            int toSwapNegative = -1;

            if ((*matrix)[i][i] < 0)
                toSwapNegative = i;
            /*
                findind main pivot on vertical line
            */
            for (int k = i + 1; k < length; ++k) {
                if ((*matrix)[k][i] > 0.0000001) {
                    toSwap = k;
                    break;
                } else if (toSwapNegative == -1 && (*matrix)[k][i] < -0.0000001) {
                    toSwapNegative = k;
                }
            }

            if (toSwap != -1) {
                swapRows(matrix, i, toSwap);
            } else if (toSwapNegative != -1) {
                negateRow(matrix, toSwapNegative, length);
                if (i != toSwapNegative)
                    swapRows(matrix, i, toSwapNegative);
            } else
                return false;

        }


        //Goes through y-axis
        for (int y = 0; y < length; ++y) {

            float multi = (*matrix)[y][i] / (*matrix)[i][i];
            float division = (*matrix)[i][i];
            //Goes through x-axis
            for (int x = i; x < length * 2; ++x) {

                if (y == i) {
                    (*matrix)[y][x] /= division;
                } else {
                    (*matrix)[y][x] -= (*matrix)[i][x] * multi;
                }

            }

        }

    }
    return true;
}


void printMatrix(float ***matrix, int *length) {

    for (int i = 0; i < (*length); ++i) {
        for (int j = 0; j < (*length) * 2; ++j) {
            if (j == (*length) * 2 - 1)
                cout << setprecision(8) << setw(12) << (*matrix)[i][j] << endl;
            else
                cout << setprecision(8) << setw(12) << (*matrix)[i][j] << " ";
        }

    }
    cout << endl;
}

void swapRows(float ***matrix, int FirstRow, int SecondRow) {

    float *tmpRow = (*matrix)[FirstRow];
    (*matrix)[FirstRow] = (*matrix)[SecondRow];
    (*matrix)[SecondRow] = tmpRow;

}

void negateRow(float ***matrix, int rowToTransf, int length) {
    for (int i = 0; i < length * 2; ++i) {
        if ((*matrix)[rowToTransf][i] != 0)
            (*matrix)[rowToTransf][i] *= -1;
    }
}




void TimeStop::startTimeStop(){
    this->t1 = chrono::high_resolution_clock::now();
}


void TimeStop::stopTimeStop(){
    this->t2 = chrono::high_resolution_clock::now();
    this->time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
}


double TimeStop::getRealTime(){
    return this->time_span.count();
}
