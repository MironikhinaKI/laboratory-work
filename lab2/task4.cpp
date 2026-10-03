#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <omp.h>
#include <windows.h>
using namespace std;

// Заполнение матрицы случайными числами
void fillMatrix(vector<vector<int>>& matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % 10;
        }
    }
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    setlocale(LC_ALL, "Russian");
    srand(time(0));

    int rowsA, n, colsB;

    cout << "Введите число строк матрицы A: ";
    cin >> rowsA;
    cout << "Введите общее измерение (столбцы A = строки B): ";
    cin >> n;
    cout << "Введите число столбцов матрицы B: ";
    cin >> colsB;

    if (rowsA <= 0 || n <= 0 || colsB <= 0) {
        cout << "Ошибка: все размеры должны быть положительными!" << endl;
        return 1;
    }

    // Создание матриц
    vector<vector<int>> matrixA(rowsA, vector<int>(n));
    vector<vector<int>> matrixB(n, vector<int>(colsB));
    vector<vector<int>> matrixC(rowsA, vector<int>(colsB));

    fillMatrix(matrixA, rowsA, n);
    fillMatrix(matrixB, n, colsB);

    cout << "\n=== Результаты ===" << endl;

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
