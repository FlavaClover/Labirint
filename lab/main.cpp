#include <iostream>
#include <string>
#include "Labirint.h"
using namespace std;


int main() {
    srand(time(NULL));
    int x_start, y_start;
    cout << "Начальная точка: "; cin >> x_start >> y_start;
    int x_end, y_end;
    cout << "Конечная точка: "; cin >> x_end >> y_end;
    Labirint l(10, 10, x_start, y_start, x_end, y_end);
    l.print_labirint();

    cout<<"Для продолжения работы программы нажмите любую клавишу...\n";
    fflush(stdin);
    getchar();
    l.solve();

    l.print_labirint();

    return 0;
}
