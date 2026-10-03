#include <fstream>
#include <iostream>
#include <omp.h>
#include <vector>
#include <windows.h>
using namespace std;

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    setlocale(LC_ALL, "Russian");

    int numThreads;
    cout << "Введите количество потоков: ";
    cin >> numThreads;

    if (numThreads <= 0) {
        cout << "Ошибка: число потоков должно быть положительным!" << endl;
        return 1;
    }

    // ===== ЧТЕНИЕ ФАЙЛА =====
    vector<double> Vx, Vy, Vz;
    double x, y, z;

    ifstream in("crd_big.txt");
    if (!in.is_open()) {
        cout << "Файл не открылся: crd_big.txt" << endl;
        return 1;
    }

    while (in >> x >> y >> z) {
        Vx.push_back(x);
        Vy.push_back(y);
        Vz.push_back(z);
    }
    in.close();

    int N = Vx.size();
    cout << "Прочитано точек: " << N << endl << endl;

    // ============================================
    // ЗАДАЧА 6: functional decomposition + critical
    // ============================================
    double global_sum = 0;
    omp_set_num_threads(numThreads);

    double start = omp_get_wtime();

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            double local = 0;
            for (int i = 0; i < N; i++) local += Vx[i];
            #pragma omp critical
            global_sum += local;
        }

        #pragma omp section
        {
            double local = 0;
            for (int i = 0; i < N; i++) local += Vy[i];
            #pragma omp critical
            global_sum += local;
        }

        #pragma omp section
        {
            double local = 0;
            for (int i = 0; i < N; i++) local += Vz[i];
            #pragma omp critical
            global_sum += local;
        }
    }

    double end = omp_get_wtime();

    double result = global_sum / (3.0 * N);

    cout << "=== Задача 6 (sections + critical) ===" << endl;
    cout << "Результат: " << result << endl;
    cout << "Время: " << end - start << " сек" << endl;

    return 0;
}
