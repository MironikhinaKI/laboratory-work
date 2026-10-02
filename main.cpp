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

//Задание 2
#include <iostream>
#include <omp.h>
#include <ctime>
#include <string>


int main() {
	setlocale(LC_ALL, "Russian");
	const int N = 16000;
	int a[N];
	double b[N];
	int num_thread;
	std::string schedule_type;
	std::cout << "Введите количество потоков: ";
	std::cin >> num_thread;
	std::cout << "Введите тип schedule: ";
	std::cin >> schedule_type;

	

	for (int i = 0; i < N; i++) {
		a[i] = i;
	}

	for (int i = 0; i < N; i++) {
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
		
	
	double end_time = omp_get_wtime();
	std::cout << "Время выполнения: " << end_time - start_time 
		<< " секунд" << std::endl;
	
	std::cout << "Проверка первых 10 элементов:\n";
	for (int i = 0; i < 10; i++) {
		std::cout << "b[" << i << "] = " << b[i] << "\n";
	}

	
	return 0;
}

//Задание 3
#include <iostream>
#include <omp.h>
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    omp_set_num_threads(8);
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

    int ids[8];
    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        ids[id] = id;
    }
    
    for (int i = all - 1; i >= 0; i--) {
        cout << "Поток " << ids[i] << " из " << all << endl;
    }

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
