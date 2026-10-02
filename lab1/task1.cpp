//Задание 1
#include <iostream>
#include <omp.h>
#include <cstdlib>
using namespace std;

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");

    if (argc < 2) {
        cout << "Использование: " << argv[0] << " <число_потоков>" << endl;
        cout << "Пример: task1.exe 8" << endl;
        return 1;
    }
    
    int num_threads = atoi(argv[1]);
    
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
