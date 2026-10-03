//Задание 2
#include <iostream>
#include <omp.h>
#include <string>
#include <windows.h>
using namespace std;

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    setlocale(LC_ALL, "Russian");

    const int N = 16000;
    int a[N];
    double b[N];

    int num_thread;
    string schedule_type;

    cout << "Введите количество потоков: ";
    cin >> num_thread;

    cout << "Введите тип schedule (static/dynamic/guided/runtime): ";
    cin >> schedule_type;

    for (int i = 0; i < N; i++) {
        a[i] = i;
        b[i] = 0.0;
    }

    omp_set_num_threads(num_thread);

    double start_time = omp_get_wtime();

    if (schedule_type == "static") {
        #pragma omp parallel for schedule(static)
        for (int i = 1; i < N - 1; i++) {
            b[i] = (a[i - 1] + a[i] + a[i + 1]) / 3.0;
        }
    }
    else if (schedule_type == "dynamic") {
        #pragma omp parallel for schedule(dynamic)
        for (int i = 1; i < N - 1; i++) {
            b[i] = (a[i - 1] + a[i] + a[i + 1]) / 3.0;
        }
    }
    else if (schedule_type == "guided") {
        #pragma omp parallel for schedule(guided)
        for (int i = 1; i < N - 1; i++) {
            b[i] = (a[i - 1] + a[i] + a[i + 1]) / 3.0;
        }
    }
    else if (schedule_type == "runtime") {
        #pragma omp parallel for schedule(runtime)
        for (int i = 1; i < N - 1; i++) {
            b[i] = (a[i - 1] + a[i] + a[i + 1]) / 3.0;
        }
    }
    else {
        cout << "Ошибка: неизвестный тип schedule!" << endl;
        return 1;
    }

    double end_time = omp_get_wtime();

    cout << "Время выполнения: " << end_time - start_time << " секунд" << endl;

    cout << "Проверка первых 10 элементов:" << endl;
    for (int i = 0; i < 10; i++) {
        cout << "b[" << i << "] = " << b[i] << endl;
    }

    return 0;
}
