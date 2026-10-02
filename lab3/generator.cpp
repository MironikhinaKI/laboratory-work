#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");

    if (argc < 3) {
        cout << "Использование: " << argv[0] << " <файл> <число_точек>" << endl;
        cout << "Пример: generator.exe crd_big.txt 1000000" << endl;
        return 1;
    }

    string filename = argv[1];
    int count = atoi(argv[2]);

    if (count <= 0) {
        cout << "Ошибка: число точек должно быть положительным!" << endl;
        return 1;
    }

    srand(time(0));

    ofstream out(filename);
    if (!out.is_open()) {
        cout << "Не удалось создать файл: " << filename << endl;
        return 1;
    }

    for (int i = 0; i < count; i++) {
        int x = rand() % 2001 - 1000;   // -1000..1000
        int y = rand() % 2001 - 1000;
        int z = rand() % 2001 - 1000;
        out << x << " " << y << " " << z << "\n";
    }

    out.close();
    cout << "Готово: " << count << " точек записано в " << filename << endl;

    return 0;
}
