#include <iostream>
#include <omp.h>
#include <cstdlib>
using namespace std;

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");

    if (argc < 2) {
        cout << "Использование: " << argv[0] << " <число_потоков>" << endl;
        cout << "Пример: task3.exe 8" << endl;
        return 1;
    }

    int num_threads = atoi(argv[1]);

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
