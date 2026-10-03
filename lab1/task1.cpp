//Задание 1
#include <iostream>
#include <omp.h>
#include <windows.h>
using namespace std;

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    setlocale(LC_ALL, "Russian");

    int num_threads;
    cout << "Введите число потоков: ";
    cin >> num_threads;

    if (num_threads <= 0) {
        cout << "Ошибка: число потоков должно быть положительным!" << endl;
        return 1;
    }

    omp_set_num_threads(num_threads);

    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        int all = omp_get_num_threads();
        #pragma omp critical
        {
            cout << "Поток " << id << " из " << all << ". Hello World!" << endl;
        }
    }
    return 0;
}
