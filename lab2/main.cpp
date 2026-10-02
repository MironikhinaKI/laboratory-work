#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <omp.h>
#include <string>
using namespace std;

//Заполнение матрицы 
void fillMatrix(vector<vector<int>>& matr, int stroka, int stolb) {
    for (int i = 0; i < stroka; i++) {
        for (int j = 0; j < stolb; j++) {
            matr[i][j] = rand()%10;
        }
    }
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");
    srand(time(0));
    
    // Проверка аргументов
    if (argc < 4) {
        cout << "Использование: " << argv[0] << " <rowsA> <n> <colsB>" << endl;
        cout << "Пример: task4.exe 1000 500 1000" << endl;
        cout << "  rowsA — число строк матрицы A" << endl;
        cout << "  n     — общее измерение (столбцы A = строки B)" << endl;
        cout << "  colsB — число столбцов матрицы B" << endl;
        return 1;
    }

    int rowsA = atoi(argv[1]);
    int n     = atoi(argv[2]);
    int colsB = atoi(argv[3]);

    if (rowsA <= 0 || n <= 0 || colsB <= 0) {
        cout << "Ошибка: все размеры должны быть положительными!" << endl;
        return 1;
    }

    //Создание векторов
    vector<vector<int>> matrixA(rowsA, vector<int>(n));
    vector<vector<int>> matrixB(n, vector<int>(colsB));
    vector<vector<int>> matrixC(rowsA, vector<int>(colsB));

    fillMatrix(matrixA, rowsA, n);
    fillMatrix(matrixB, n, colsB);

    for (int numThreads : {1, 2, 4, 8}) {
        omp_set_num_threads(numThreads);

        // Обнуление результата перед каждым запуском
        for (int i = 0; i < rowsA; i++)
            for (int j = 0; j < colsB; j++)
                matrixC[i][j] = 0;

        double startTime = omp_get_wtime();

        #pragma omp parallel for schedule(static)
        for (int i = 0; i < rowsA; i++) {
            for (int j = 0; j < colsB; j++) {
                int sum = 0;
                for (int k = 0; k < n; k++) {
                    sum += (matrixA[i][k] * matrixB[k][j]);
                }
                matrixC[i][j] = sum;
            }
        }

        double endTime = omp_get_wtime();

        cout << "Потоков: " << numThreads
             << ", время: " << endTime - startTime << " сек" << endl;
    }

    return 0;
}

