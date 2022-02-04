// Создайте класс для подсчета площади геометрических фигур.
// Класс должен предоставлять функциональность для подсчета
// площади треугольника по разным формулам, площади прямоугольника, площади квадрата, площади ромба.
// Функции-члены для подсчета площади должны быть реализованы с помощью статических функций-членов.
// Также класс должен считать количество подсчетов площади и возвращать это значение с помощью статической функции-члена.

#include <iostream>
#include <Windows.h>
using namespace std;

class area {
public:
    static int count;

    static double triangle1() /*площадь треугольника по стороне и высоте*/
    {
        double a = 0;
        double h = 0;
        cout << "Площадь треугольника по стороне и высоте" << endl;
        cout << "введите сторону" << endl;
        cin >> a;
        cout << "введите высоту" << endl;
        cin >> h;
        count++;
        return 0.5 * h * a;
    }

    static double triangle2() // площадь треугольника по трем сторонам 
    {
        double p = 0;
        double a = 0;
        double b = 0;
        double c = 0;
        cout << "Площадь треугольника по трем сторонам" << endl;
        cout << "введите сторону 1" << endl;
        cin >> a;
        cout << "введите сторону 2" << endl;
        cin >> b;
        cout << "введите сторону 3" << endl;
        cin >> c;
        p = (a + b + c) / 2;
        count++;
        return sqrt(p * (p - a) * (p - b) * (p - c));
    }

    static double rectangle() //площадь прямоугольника
    {
        double a = 0;
        double b = 0;
        cout << "Площадь прямоугольника" << endl;
        cout << "введите сторону 1" << endl;
        cin >> a;
        cout << "введите сторону 2" << endl;
        cin >> b;
        count++;
        return a * b;
    }
    
    static double square() // площадь квадрата по длине стороны
    {
        double a = 0;
        cout << "Площадь квадрата по длине стороны" << endl;
        cout << "введите сторону" << endl;
        cin >> a;
        count++;
        return a * a;
    }

    static double rhombus() //площадь ромба по длине стороны и высоте
    {
        double a = 0;
        double h = 0;
        cout << "Площадь ромба по длине стороны и высоте" << endl;
        cout << "введите сторону" << endl;
        cin >> a;
        cout << "введите высоту" << endl;
        cin >> h;
        count++;
        return a * h;
    }
};

int area::count = 0;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int n;
    double s;
    do
    {
        cout << "1. Площадь треугольника по стороне и высоте\n2. Площадь треугольника по трем сторонам\n";
        cout << "3. Площадь прямоугольника\n4. Площадь квадрата по длине стороны\n5. Площадь ромба по длине стороны и высоте\n0. Выход\n";
        cin >> n;
        switch (n) {
        case 1:
            s = area::triangle1();
            cout << "S = " << s << endl;
            break;
        case 2:
            s = area::triangle2();
            cout << "S = " << s << endl;
            break;
        case 3:
            s = area::rectangle();
            cout << "S = " << s << endl;
            break;
        case 4:
            s = area::square();
            cout << "S = " << s << endl;
            break;
        case 5:
            s = area::rhombus();
            cout << "S = " << s << endl;
            break;

        default:
            cout << "Количество подсчетов площади: " << area::count << endl;
            n = 0;
        }
    } while (n != 0);

    return 0;
}