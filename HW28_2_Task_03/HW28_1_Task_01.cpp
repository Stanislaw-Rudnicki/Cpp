// Создайте класс Circle (окружность):
// Реализуйте через перегруженные операторы:
// Проверка на равенство радиусов двух окружностей (операция ==);
// Сравнение длин двух окружностей (операция >);
// Пропорциональное изменение размеров окружности, путем изменения ее радиуса (операция += и -=)

#include <iostream>
#include <Windows.h>
using namespace std;

#define PI 3.14159265

class Circle {
    double r_;
    double C() const { return 2 * PI * r_; };
public:
    Circle() :r_(0) {};
    Circle(const double& r) :r_(r) {};
    Circle(const Circle& other) :r_(other.r_) {};
    Circle& operator=(const Circle&);
    bool operator==(const Circle&);
    bool operator!=(const Circle&);
    bool operator>(const Circle&);
    bool operator<(const Circle&);
    Circle& operator+=(int);
    Circle& operator-=(int);
    friend ostream& operator<<(ostream&, const Circle&);
};
Circle& Circle::operator=(const Circle& other) {
    if (this == &other)
        return *this;
    r_ = other.r_;
    return *this;
}
bool Circle::operator==(const Circle& other) {
    return r_ == other.r_;
}
bool Circle::operator!=(const Circle& other) {
    return !(r_ == other.r_);
}
bool Circle::operator>(const Circle& other) {
    return C() > other.C();
}
bool Circle::operator<(const Circle& other) {
    return C() < other.C();
}
Circle& Circle::operator+=(int n) {
    r_ += n;
    return *this;
}
Circle& Circle::operator-=(int n) {
    // проверка, чтобы n не оказался больше R
    if (n > r_)
        cout << "n > R, subtraction is impossible" << endl;
    else {
        r_ -= n;
        return *this;
    }
}
ostream& operator<<(ostream& out, const Circle& other) {
    out << "R: " << other.r_ << ", C: " << other.C();
    return out;
}


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    
    Circle s1(3);
    Circle s2(s1);
    cout << "s1: " << s1 << endl;
    cout << "s2: " << s2 << endl;
    cout << "s1 == s2: " << boolalpha << (s1 == s2) << endl; // Ответ: 1
    cout << "s1 > s2: " << boolalpha << (s1 > s2) << endl; // Ответ: 0
    s1 += 3;
    cout << s1 << endl; // Ответ: 37.68
    s2 -= 4; // Ответ: n > R, subtraction is impossible
    s2 -= 2; // Ответ: 6.28
    cout << s2 << endl;
        
    return 0;
}