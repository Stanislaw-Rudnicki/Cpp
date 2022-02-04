// —оздайте класс ƒробь (или используйте уже ранее созданный вами).
// »спользу€ перегрузку операторов реализуйте дл€ него арифметические операции дл€ работы с дроб€ми
// (операции + , -, *, / ).

#include <iostream>
#include <Windows.h>
using namespace std;

class Fraction {
    int sign;               // знак дроби (+ или -)
    int intPart;            // цела€ часть дроби
    int numerator;          // числитель дроби
    int denominator;        // знаменатель дроби
    void GetMixedView();    // преобразование в смешанный вид
    void Cancellation();    // сокращение дроби
    void GetIntPart();      // выделение целой части дроби
public:
    Fraction() :Fraction(0, 1) {};
    Fraction(int, int, int = 0, int = 1);
    Fraction operator + (const Fraction&);
    Fraction operator + (int);
    Fraction operator - (const Fraction&);
    Fraction operator - (int);
    Fraction operator * (const Fraction&);
    Fraction operator * (int);
    Fraction operator / (const Fraction&);
    Fraction operator / (int);
    Fraction  operator - ();
    friend Fraction operator + (int, const Fraction&);
    friend Fraction operator - (int, const Fraction&);
    friend Fraction operator * (int, const Fraction&);
    friend Fraction operator / (int, const Fraction&);
    operator double();
    // bool operator > (const Fraction&);
    // bool operator < (const Fraction&);
    // bool operator >= (const Fraction&);
    // bool operator <= (const Fraction&);
    // bool operator != (const Fraction&);
    // bool operator == (const Fraction&);
    friend istream& operator >> (istream&, Fraction&);
    friend ostream& operator << (ostream&, const Fraction&);
};
void Fraction::GetMixedView() {
    GetIntPart();
    Cancellation();
}
void Fraction::Cancellation() {
    if (numerator) {
        int m = denominator,
            n = numerator,
            ost = m % n;
        while (ost) {
            m = n; n = ost;
            ost = m % n;
        }
        int nod = n;
        if (nod != 1) {
            numerator /= nod; denominator /= nod;
        }
    }
}
void Fraction::GetIntPart() {
    if (numerator >= denominator) {
        intPart += (numerator / denominator);
        numerator %= denominator;
    }
}
Fraction::Fraction(int n, int d, int i, int s) {
    intPart = i;
    numerator = n;
    denominator = d;
    sign = s;
    GetMixedView();
}
Fraction Fraction::operator + (const Fraction& a) {
    Fraction res;
    res.numerator = sign * (intPart * denominator + numerator) * a.denominator +
        a.sign * (a.intPart * a.denominator + a.numerator) * denominator;
    res.denominator = denominator * a.denominator;
    if (res.numerator < 0) {
        res.numerator *= -1;
        res.sign = -1;
    }
    res.GetMixedView();
    return res;
}
Fraction Fraction::operator + (int a) {
    Fraction res;
    Fraction b(0, 1, abs(a), a / abs(a));
    res = (*this) + b;
    return res;
}
Fraction Fraction::operator - (const Fraction& a) {
    Fraction res;
    res.numerator = sign * (intPart * denominator + numerator) * a.denominator -
        a.sign * (a.intPart * a.denominator + a.numerator) * denominator;
    res.denominator = denominator * a.denominator;
    if (res.numerator < 0) {
        res.numerator *= -1;
        res.sign = -1;
    }
    res.GetMixedView();
    return res;
}
Fraction Fraction::operator - (int a) {
    Fraction res;
    Fraction b(0, 1, abs(a), a / abs(a));
    res = (*this) - b;
    return res;
}
Fraction Fraction::operator*(const Fraction& a) {
    Fraction res;
    res.numerator = sign * (intPart * denominator + numerator) * a.numerator;
    res.denominator = denominator * a.denominator;
    if (res.numerator < 0) {
        res.numerator *= -1;
        res.sign = -1;
    }
    res.GetMixedView();
    return res;
}
Fraction Fraction::operator*(int a) {
    Fraction res;
    Fraction b(0, 1, abs(a), a / abs(a));
    res = (*this) * b;
    return res;
}
Fraction Fraction::operator/(const Fraction& a) {
    Fraction res;
    res.numerator = sign * (intPart * denominator + numerator) * a.denominator;
    res.denominator = denominator * a.numerator;
    if (res.numerator < 0) {
        res.numerator *= -1;
        res.sign = -1;
    }
    res.GetMixedView();
    return res;
}
Fraction Fraction::operator/(int a) {
    Fraction res;
    Fraction b(0, 1, abs(a), a / abs(a));
    res = (*this) / b;
    return res;
}
Fraction operator + (int a, const Fraction& c) {
    Fraction res;
    Fraction b(0, 1, abs(a), a / abs(a));
    res = b + c;
    return res;
}
Fraction operator - (int a, const Fraction& c) {
    Fraction res;
    Fraction b(0, 1, abs(a), a / abs(a));
    res = b - c;
    return res;
}
Fraction operator*(int a, const Fraction& c) {
    Fraction res;
    Fraction b(0, 1, abs(a), a / abs(a));
    res = b * c;
    return res;
}
Fraction operator/(int a, const Fraction& c) {
    Fraction res;
    Fraction b(0, 1, abs(a), a / abs(a));
    res = b / c;
    return res;
}
Fraction Fraction::operator-() {
    Fraction res(*this);
    res.sign = -res.sign;
    return res;
}
Fraction::operator double() {
    return (double)sign * (intPart * denominator + numerator) / denominator;
}
istream& operator >> (istream& fin, Fraction& a) {
    char buf[30];
    fin.getline(buf, 29);
    // находим первое вхождение символа '/' в строку
    char* ps = strchr(buf, '/');
    // если символ не найден, т.е. число - без дробной части
    if (ps == NULL) {
        // из строки выдел€ем целую часть
        sscanf(buf, "%d", &a.intPart);
        a.numerator = 0;
        a.denominator = 1;
        //знак числа определ€етс€ по знаку целой части
        if (a.intPart >= 0)
            a.sign = 1;
        else {
            a.sign = -1;
            a.intPart = -a.intPart;
        }
        return fin;
    }
    // если число без целой части
    if (strchr(buf, ' ') == NULL) {
        a.intPart = 0;
        // считываем из строки числитель и знаменатель
        sscanf(buf, "%d/%d", &a.numerator, &a.denominator);
        //знак числа определ€етс€ по знаку числител€
        if (a.numerator > 0)
            a.sign = 1;
        else {
            a.sign = -1;
            a.numerator = -a.numerator;
        }
        a.GetMixedView();
        return fin;
    }
    // считывание всех составл€ющих дроби и определение знака
    sscanf(buf, "%d %d/%d", &a.intPart, &a.numerator, &a.denominator);
    if (a.intPart > 0)
        a.sign = 1;
    else {
        a.sign = -1;
        a.intPart = -a.intPart;
    }
    a.GetMixedView();
    return fin;
}
ostream& operator << (ostream& out, const Fraction& a) {
    if (a.sign < 0)
        out << "-";
    if (a.intPart)
        out << a.intPart << " ";
    if (a.numerator)
        out << a.numerator << "/" << a.denominator;
    if (a.intPart == 0 && a.numerator == 0)
        out << "0";
    //out << " ";
    return out;
}


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
  
    Fraction d1(2, 3, 0, 1);    // 2/3
    Fraction d2(4, 5, 2, -1);   // -2 4/5
    Fraction d3(4, 3, 1, 1);    // 2 1/3
    Fraction d4(10, 6);         // 1 2/3
    Fraction d5(3, 7);          // 3/7
    Fraction d6(3, 8, 2);       // 2 3/8
    Fraction d7;                // 0

    Fraction r1(2, 3, 0, 1);
    cout << "r1 = " << r1 << endl;
    Fraction r2(5, 7, 0, 1);
    cout << "r2 = " << r2 << endl;
    cout << "-r2= " << -r2 << endl;
    cout << "r2 = " << (double)r2 << endl;
    cout << endl;
    Fraction d;
    
    // вызов оператора "+" дл€ двух дробей
    d = r1 + r2;
    cout << "r1 + r2 = " << d << endl;
    // вызов оператора "+" дл€ дроби и числа
    d = r1 + (-11);
    cout << "r1 + (-11) = " << d << endl;
    // вызов оператора "+" дл€ числа и дроби
    d = 5 + r1;
    cout << "5 + r1 = " << d << endl;
    // вызов оператора преобразовани€ дроби к типу double
    Fraction q(1, 3);
    double f = q;
    cout << q << " = " << f << endl;

    r1 = { 7, 9 };
    r2 = { 4, 7 };
    cout << r1 << " / " << r2 << " = " << r1 / r2 << endl;

    return 0;
}