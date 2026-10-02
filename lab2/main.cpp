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

void vivod(vector<vector<int>>& matr, int stroka, int stolb) {
    for (int i = 0; i < stroka; i++) {
        for (int j = 0; j < stolb; j++) {
            cout << matr[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(0));
    
    int A_m, A_n, B_n, B_k, n;
    
    //Задание размеров, проверка условия
    cout << "Введите количество строк и столбцов матрицы А через пробел: ";
    cin >> A_m >> A_n;
    cout << "Введите количество строк и столбцов матрицы B через пробел: ";
    cin >> B_n >> B_k;
    if (A_n != B_n) {
        cout << "Ошибка! Кол-во столбцов матрицы А не совпадает с кол-вом строк матрицы В.";
        return 0;
    }
    n = A_n; //для удобства столбцы А и строки В одной переменной

    //Создание векторов
    vector<vector<int>> A(A_m, vector<int>(n));
    vector<vector<int>> B(n, vector<int>(B_k));
    vector<vector<int>> C(A_m, vector<int>(B_k));
    fillMatrix(A, A_m, n);
    //vivod(A, A_m, n);
    fillMatrix(B,n, B_k);
    //vivod(B, n, B_k);

    for (int count : {1, 2, 4, 8}) {
        omp_set_num_threads(count);

        double start = omp_get_wtime();

        #pragma omp parallel for schedule(static)
        for (int m = 0; m < A_m; m++) {
            for (int k = 0; k < B_k; k++) {
                int sumi = 0;
                for (int no = 0; no < n; no++) {
                    sumi += (A[m][no] * B[no][k]);
                }
                C[m][k] = sumi;
            }
        }

        double end = omp_get_wtime();
        cout << "Потоков: " << count << ", время: " << end - start << " сек" << endl;
    }


    return 0;
}
