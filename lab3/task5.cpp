#include <fstream>
#include <iostream>
#include <omp.h>
#include <vector>
#include <cstdlib>
using namespace std;

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");

    // проверка аргументов
    if (argc < 3) {
        cout << "Использование: " << argv[0] << " <файл> <число_потоков>" << endl;
        cout << "Пример: task5.exe crd_big.txt 4" << endl;
        return 1;
    }

    string filename = argv[1];
    int numThreads  = atoi(argv[2]);

    if (numThreads <= 0) {
        cout << "Ошибка: число потоков должно быть положительным!" << endl;
        return 1;
    }

    // ===== ЧТЕНИЕ ФАЙЛА =====
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

    double sumi_x = 0, sumi_y = 0, sumi_z = 0;

    // parallel for + reduction
    omp_set_num_threads(numThreads);

    double start1 = omp_get_wtime();

    #pragma omp parallel for reduction(+:sumi_x, sumi_y, sumi_z)
    for (int i = 0; i < N; i++) {
        sumi_x += Vx[i];
        sumi_y += Vy[i];
        sumi_z += Vz[i];
    }

    double end1 = omp_get_wtime();

    cout << "=== Версия 1 (reduction) ===" << endl;
    cout << "Центр: " << sumi_x / N << " " << sumi_y / N << " " << sumi_z / N << endl;
    cout << "Время: " << end1 - start1 << " сек" << endl << endl;

    // parallel sections
    sumi_x = 0; sumi_y = 0; sumi_z = 0;
    omp_set_num_threads(numThreads);

    double start2 = omp_get_wtime();

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            for (int i = 0; i < N; i++) sumi_x += Vx[i];
        }

        #pragma omp section
        {
            for (int i = 0; i < N; i++) sumi_y += Vy[i];
        }

        #pragma omp section
        {
            for (int i = 0; i < N; i++) sumi_z += Vz[i];
        }
    }

    double end2 = omp_get_wtime();

    cout << "=== Версия 2 (sections) ===" << endl;
    cout << "Центр: " << sumi_x / N << " " << sumi_y / N << " " << sumi_z / N << endl;
    cout << "Время: " << end2 - start2 << " сек" << endl;

    return 0;
}
