// Создайте класс «Комплексное число» - Complex. Класс должен содержать несколько конструкторов.
// Класс должен иметь возможность вводить и выводить комплексные числа посредством перегруженных операций >> и <<.
// Перегрузите операции + , -, != , == , ().
// Используйте обычную и дружественную перегрузку.

#include <iostream>
#include <Windows.h>
using namespace std;

class Complex {
    double Re;
    double Im;
public:
    Complex() :Complex(0, 0) {};
    Complex(double, double = 0);
    Complex operator + (const Complex&);
    Complex operator + (double);
    Complex operator - (const Complex&);
    Complex operator - (double);
    Complex operator * (const Complex&);
    Complex operator * (double);
    Complex operator / (const Complex&);
    Complex operator / (double);
    Complex operator - ();
    bool operator==(const Complex&);
    bool operator!=(const Complex&);
    double operator()(int);
    friend Complex operator + (double, const Complex&);
    friend Complex operator - (double, const Complex&);
    friend Complex operator * (double, const Complex&);
    friend Complex operator / (double, const Complex&);
    friend istream& operator >> (istream&, Complex&);
    friend ostream& operator << (ostream&, const Complex&);
};
Complex::Complex(double r, double i) {
    Re = r;
    Im = i;
}
Complex Complex::operator + (const Complex& a) {
    Complex res;
    res.Re = Re + a.Re;
    res.Im = Im + a.Im;
    return res;
}
Complex Complex::operator + (double a) {
    Complex res;
    Complex b(a);
    res = (*this) + b;
    return res;
}
Complex Complex::operator - (const Complex& a) {
    Complex res;
    res.Re = Re - a.Re;
    res.Im = Im - a.Im;
    return res;
}
Complex Complex::operator - (double a) {
    Complex res;
    Complex b(a);
    res = (*this) - b;
    return res;
}
Complex Complex::operator * (const Complex& a) {
    Complex res;
    res.Re = (Re * a.Re) - (Im * a.Im);
    res.Im = (Im * a.Re) + (a.Im * Re);
    return res;
}
Complex Complex::operator * (double a) {
    Complex res;
    Complex b(a);
    res = (*this) * b;
    return res;
}
Complex Complex::operator / (const Complex& a) {
    Complex res;
    res.Re = (Re * a.Re + Im * a.Im) / (pow(a.Re, 2) + pow(a.Im, 2));
    res.Im = (Im * a.Re - a.Im * Re) / (pow(a.Re, 2) + pow(a.Im, 2));
    return res;
}
Complex Complex::operator / (double a) {
    Complex res;
    Complex b(a);
    res = (*this) / b;
    return res;
}
Complex operator + (double a, const Complex& c) {
    Complex res;
    Complex b(a);
    res = b + c;
    return res;
}
Complex operator - (double a, const Complex& c) {
    Complex res;
    Complex b(a);
    res = b - c;
    return res;
}
Complex operator * (double a, const Complex& c) {
    Complex res;
    Complex b(a);
    res = b * c;
    return res;
}
Complex operator / (double a, const Complex& c) {
    Complex res;
    Complex b(a);
    res = b / c;
    return res;
}
Complex Complex::operator - () {
    Complex res(*this);
    res.Re = -res.Re;
    res.Im = -res.Im;
    return res;
}
bool Complex::operator==(const Complex& other) {
    return Re == other.Re && Im == other.Im;
}
bool Complex::operator!=(const Complex& other) {
    return !(operator == (other));
}
double Complex::operator()(int p) {
    if (p == 1) return Re;
    else if (p == 2) return Im;
    else return -1;
}
istream& operator >> (istream& fin, Complex& a) {
    char buf[30];
    fin.getline(buf, 29);
    sscanf(buf, "%lf %lf", &a.Re, &a.Im);
    return fin;
}
ostream& operator << (ostream& out, const Complex& a) {
    if (!a.Re && a.Im)
        out << a.Im << "i";
    if (a.Re && !a.Im)
        out << a.Re;
    if (a.Re && a.Im)
        out << a.Re << showpos << a.Im << noshowpos << "i";
    if (!a.Re && !a.Im)
        out << "0";
    return out;
}


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Complex d1(0, 1.6);
    Complex d2(0, -1);
    Complex d3(4, 0);
    Complex d4(1.5, 6.5);
    Complex d5(3);
    Complex d6(0);
    Complex d7;

    cout << d1 << endl;
    cout << d2 << endl;
    cout << d3 << endl;
    cout << d4 << endl;
    cout << d5 << endl;
    cout << d6 << endl;
    cout << d7 << endl;

    Complex comp1, comp2;
    cout << "Введите первое комплексное число: " << endl;
    cin >> comp1;
    cout << "Первое комплексное число: " << comp1 << endl << endl;
    cout << "Введите второе комплексное число: " << endl;
    cin >> comp2;
    cout << "Второе комплексное число: " << comp2 << endl << endl;
    cout << "Сумма этих чисел = " << comp1 + comp2 << endl;
    cout << "Разность этих чисел = " << comp1 - comp2 << endl;
    cout << "Произведение этих чисел = " << comp1 * comp2 << endl;
    cout << "Частное этих чисел (первое/второе) = " << comp1 / comp2 << endl;
    cout << boolalpha << (comp1 == comp2) << endl;
    cout << boolalpha << (comp1 != comp2) << endl;
    cout << boolalpha << comp1(1) << " " << comp1(2) << endl;

    return 0;
}