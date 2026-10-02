//Задание 1
#include <iostream>
#include <omp.h>
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    int num_threads;
    cin >> num_threads;
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
