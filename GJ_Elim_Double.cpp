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

double **loadInput(int *length);

double **loadInput(ifstream *inputMatrixFile, int *length);

bool operateMatrixFirst(double ***matrix, int length);

bool operateMatrixSecond(double ***matrix, int length);

bool operateMatrix2(double ***matrix, int length);

void printMatrix(double ***matrix, int *length);

void swapRows(double ***matrix, int FirstRow, int SecondRow);

void negateRow(double ***matrix, int rowToTransf, int length);


int main(int argc, char const *argv[]) {
    int length = 0;
    double **matrix;
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

double **loadInput(int *length) {
    double **matrix = NULL;

    cout << "Number of equations ? " << endl;

    cin >> (*length);

    cout << "Coefficients of matrix, which has to be";
    cout << " inverted with Gauss-Jorden method." << endl;

    matrix = new double *[(*length)];

    for (int i = 0; i < (*length); ++i) {
        matrix[i] = new double[2 * (*length)]();
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

double **loadInput(ifstream *inputMatrixFile, int *length) {
//    int (*length) = 0;
    double **matrix = NULL;

    (*inputMatrixFile) >> skipws >> (*length);
//    cout << "Mam : " << (*length) << endl;

    matrix = new double *[(*length)];

    for (int i = 0; i < (*length); ++i) {
        matrix[i] = new double[2 * (*length)]();
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

bool operateMatrixFirst(double ***matrix, int length) {

    // int pivot = -1;
    // int ** real_matrix = (*matrix);

    // Prechadzam diagonalu
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




        //Simplyfing current row
        for (int j = length * 2 - 1; j >= 0; --j) {
            (*matrix)[i][j] /= (*matrix)[i][i];
        }

        // Prechadzam Y-sylon os, but only to foreLast item
        for (int y = i + 1; y < length; ++y) {


            double multi = (*matrix)[y][i] / (*matrix)[i][i];
            // cout << " Multi is: " << multi << endl;

            // Prechadzam X-sovu os
            for (int x = i; x < length * 2; ++x) {

                // cout << " Pred : " << (*matrix)[y][x] << " Po: " << (*matrix)[y][x] - ((*matrix)[i][x] * multi) << endl;
                (*matrix)[y][x] -= ((*matrix)[i][x] * multi);

            }
        }

    }

    return true;
}

bool operateMatrixSecond(double ***matrix, int length) {

    // Prechadzam diagonalu z hora doel
    for (int i = 1; i < length; ++i) {




        // Prechadzam Y-sylon os, but only to foreLast item
        for (int y = i - 1; y >= 0; --y) {


            double multi = (*matrix)[y][i] / (*matrix)[i][i];
            // cout << " Multi is: " << multi << endl;

            // Prechadzam X-sovu os
            for (int x = i; x < length * 2; ++x) {

                // cout << " Pred : " << (*matrix)[y][x] << " Po: " << (*matrix)[y][x] - ((*matrix)[i][x] * multi) << endl;
                (*matrix)[y][x] -= ((*matrix)[i][x] * multi);

            }
        }

    }

    return true;

}



void printMatrix(double ***matrix, int *length) {

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

void swapRows(double ***matrix, int FirstRow, int SecondRow) {

    double *tmpRow = (*matrix)[FirstRow];
    (*matrix)[FirstRow] = (*matrix)[SecondRow];
    (*matrix)[SecondRow] = tmpRow;

}

void negateRow(double ***matrix, int rowToTransf, int length) {
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

