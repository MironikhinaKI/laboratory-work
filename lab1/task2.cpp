#include <iostream>
#include <omp.h>
#include <ctime>
#include <string>
#include <cstdlib>
using namespace std;

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "Russian");
	
	if (argc < 3) {
        cout << "Использование: " << argv[0] << " <число_потоков> <schedule>" << endl;
        cout << "Пример: task2.exe 8 static" << endl;
        cout << "schedule: static | dynamic | guided | runtime" << endl;
        return 1;
    }

	int num_thread = atoi(argv[1]);
    string schedule_type = argv[2];

    if (num_thread <= 0) {
        cout << "Ошибка: число потоков должно быть положительным!" << endl;
        return 1;
    }
	
	const int N = 16000;
	int a[N];
	double b[N];

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
        cout << "Доступные: static | dynamic | guided | runtime" << endl;
        return 1;
    }
	
	double end_time = omp_get_wtime();
	cout << "Время выполнения: " << end_time - start_time << " секунд" << endl;
	
	std::cout << "Проверка первых 10 элементов:\n";
	for (int i = 0; i < 10; i++) {
		cout << "b[" << i << "] = " << b[i] << "\n";
	}

	
	return 0;
}
