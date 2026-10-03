#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
using namespace std;

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    setlocale(LC_ALL, "Russian");
    srand(time(0));

    int count;
    cout << "Введите количество точек: ";
    cin >> count;

    if (count <= 0) {
        cout << "Ошибка: число точек должно быть положительным!" << endl;
        return 1;
    }

    ofstream out("crd_big.txt");
    if (!out.is_open()) {
        cout << "Не удалось создать файл: crd_big.txt" << endl;
        return 1;
    }

    for (int i = 0; i < count; i++) {
        int x = rand() % 2001 - 1000;   // -1000..1000
        int y = rand() % 2001 - 1000;
        int z = rand() % 2001 - 1000;
        out << x << " " << y << " " << z << "\n";
    }

    out.close();
    cout << "Готово: " << count << " точек записано в crd_big.txt" << endl;

    return 0;
}
