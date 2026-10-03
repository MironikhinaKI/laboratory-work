//Задание 3
#include <iostream>
#include <omp.h>
#include <windows.h>
using namespace std;

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    setlocale(LC_ALL, "Russian");

    int num_threads;
    cout << "Введите количество потоков: ";
    cin >> num_threads;

    if (num_threads <= 0) {
        cout << "Ошибка: число потоков должно быть положительным!" << endl;
        return 1;
    }

    omp_set_num_threads(num_threads);
    int all = omp_get_max_threads();

////////// 1 способ
    #pragma omp parallel for ordered
    for (int i = 0; i < all; i++) {
        #pragma omp ordered
        {
            int id = all - 1 - i;
            cout << "Поток " << id << " из " << all << endl;
        }
    }

////////// 2 способ
    int* ids = new int[all];
    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        ids[id] = id;
    }

    for (int i = all - 1; i >= 0; i--) {
        cout << "Поток " << ids[i] << " из " << all << endl;
    }
    delete[] ids;

////////// 3 способ
    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        #pragma omp barrier
        for (int memb = all - 1; memb >= 0; memb--) {
            if (id == memb) {
                #pragma omp critical
                {
                    cout << "Поток " << id << " из " << all << endl;
                }
            }
            #pragma omp barrier
        }
    }

////////// 4 способ
    int maxid = all - 1;

    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        #pragma omp barrier
        for (int memb = all - 1; memb >= 0; memb--) {
            #pragma omp critical
            {
                if (id == maxid) {
                    cout << "Поток " << id << " из " << all << endl;
                    maxid--;
                }
            }
            #pragma omp barrier
        }
    }

    return 0;
}
