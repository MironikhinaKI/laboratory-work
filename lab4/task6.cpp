#include <fstream>
#include <iostream>
#include <omp.h>
#include <vector>
#include <cstdlib>
using namespace std;

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");

    // Проверка аргументов
    if (argc < 3) {
        cout << "Использование: " << argv[0] << " <файл> <число_потоков>" << endl;
        cout << "Пример: task6.exe crd_big.txt 4" << endl;
        return 1;
    }

    string filename = argv[1];
    int numThreads  = atoi(argv[2]);

    if (numThreads <= 0) {
        cout << "Ошибка: число потоков должно быть положительным!" << endl;
        return 1;
    }

    vector<double> Vx, Vy, Vz;
    double x, y, z;

    ifstream in(filename);
    if (!in.is_open()) {
        cout << "Файл не открылся: " << filename << endl;
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
    cout << "Результат: " << result << endl;
    cout << "Время: " << end - start << " сек" << endl;

    return 0;
}
