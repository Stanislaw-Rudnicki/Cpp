// Создайте класс с именем Time для хранения времени.
// В классе должна быть функция-член, которая даёт приращение времени, хранящееся в объекте Time, равное 1 секунде.
// Напишите соответствующие конструкторы и функции-члены.
// В классе должны быть перегружены операции ++, --, != , == , > , <, >> , << , =, +=, -=, ().
// Используйте обычную и дружественную перегрузку.


#include <iostream>
#include <Windows.h>
#include <iomanip>
using namespace std;

class Time {
    int s_, m_, h_, d_;
    int GetSeconds() const;
public:
    Time();
    Time(int, int, int);
    Time(const char*);
    Time(int);
    // Деструктор
    ~Time() {}
    // Конструктор копирования
    Time(const Time&);
    // Оператор присваивания копированием
    Time& operator=(const Time&);
    // В классе должна быть функция-член, которая даёт приращение времени, хранящееся в объекте Time, равное 1 секунде
    Time& PlusOneSecond();
    Time operator+(int);
    int operator-(const Time&);
    Time operator-(int);
    Time operator++();
    Time operator++(int);
    Time operator--();
    Time operator--(int);
    bool operator==(const Time&);
    bool operator!=(const Time&);
    bool operator<(const Time&);
    bool operator>(const Time&);
    Time& operator+=(int);
    Time& operator-=(int);
    // () повертати при 1 день, при 2 місяць, при 3 рік
    int operator()(int);
    friend Time operator+(int, const Time&);
    friend istream& operator>>(istream&, Time&);
    friend ostream& operator<<(ostream&, const Time&);
};
int Time::GetSeconds() const {
    return h_ * 60 * 60 + m_ * 60 + s_;
}
Time::Time() {
    SYSTEMTIME st;
    GetSystemTime(&st);
    s_ = st.wSecond;
    m_ = st.wMinute;
    h_ = st.wHour;
    d_ = 0;
}
Time::Time(int h, int m, int s) {
    (0 <= h && h <= 23) ? h_ = h : h_ = 0;
    (0 <= m && m <= 59) ? m_ = m : m_ = 0;
    (0 <= s && s <= 59) ? s_ = s : s_ = 0;
    d_ = 0;
}
Time::Time(const char* str) {
    int h = 0, m = 0, s = 0;
    if ((sscanf(str, "%d.%d.%d", &h, &m, &s) < 3) && (sscanf(str, "%d:%d:%d", &h, &m, &s) < 3)) {
            h_ = 0;
            m_ = 0;
            s_ = 0;
        }
    else {
        Time temp(h, m, s);
        *this = temp;
    }
}
Time::Time(int ss) {
    if (ss < 0) {
        d_ = ss / 86400;
        ss = 86400 - abs(ss % 86400);
    }
    else
        d_ = ss / 86400;
    h_ = ss / 3600 % 24;
    m_ = ss / 60 % 60;
    s_ = ss % 60;
}
Time::Time(const Time& other) {
    d_ = other.d_;
    h_ = other.h_;
    m_ = other.m_;
    s_ = other.s_;
}
Time& Time::operator=(const Time& other) {
    d_ = other.d_;
    h_ = other.h_;
    m_ = other.m_;
    s_ = other.s_;
    return *this;
}
Time& Time::PlusOneSecond() {
    *this = GetSeconds() + 1;
    return *this;
}
Time Time::operator+(int a) {
    return GetSeconds() + a;
}
int Time::operator-(const Time& a) {
    return GetSeconds() - a.GetSeconds();
}
Time Time::operator-(int a) {
    return GetSeconds() - a;
}
Time Time::operator++() {
    PlusOneSecond();
    return *this;
}
Time Time::operator++(int) {
    Time temp(*this);
    ++* this;
    return temp;
}
Time Time::operator--() {
    *this = GetSeconds() - 1;
    return *this;
}
Time Time::operator--(int) {
    Time temp(*this);
    --* this;
    return temp;
}
bool Time::operator==(const Time& other) {
    return GetSeconds() == other.GetSeconds();
}
bool Time::operator!=(const Time& other) {
    return !(operator == (other));
}
bool Time::operator<(const Time& other) {
    return GetSeconds() < other.GetSeconds();
}
bool Time::operator>(const Time& other) {
    return GetSeconds() > other.GetSeconds();
}
Time& Time::operator+=(int n) {
    *this = GetSeconds() + n;
    return *this;
}
Time& Time::operator-=(int n) {
    int sec = GetSeconds();
    if (n > sec)
        cout << "n > seconds, subtraction is impossible" << endl;
    else {
        *this = sec -= n;
        return *this;
    }
}
int Time::operator()(int p) {
    if (p == 1) return h_;
    else if (p == 2) return m_;
    else if (p == 3) return s_;
    else return -1;
}
Time operator+(int l, const Time& r) {
    return r.GetSeconds() + l;
}
istream& operator>>(istream& fin, Time& a) {
    char buf[9];
    fin.getline(buf, 9);
    int h = 0, m = 0, s = 0;
    if ((sscanf(buf, "%d.%d.%d", &h, &m, &s) < 3) && (sscanf(buf, "%d:%d:%d", &h, &m, &s) < 3)) {
            a.h_ = 0;
            a.m_ = 0;
            a.s_ = 0;
        }
    else {
        a.h_ = h;
        a.m_ = m;
        a.s_ = s;
    }
    return fin;
}
ostream& operator<<(ostream& out, const Time& a) {
    out << a.h_ << ":" << setw(2) << setfill('0') << a.m_ << ":" << setw(2) << setfill('0') << a.s_;
    return out;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Time d1;
    Time d2("8:02:20");
    cout << d1 << " - " << d2 << " = " << d1 - d2 << "\n\n";
    cout << "Введите время в формате чч:мм:сс: ";
    Time d3;
    cin >> d3;
    cout << "Ваше время: " << d3 << endl;
    cout << "Сколько секунд прибавить? ";
    int n;
    cin >> n;
    cout << "Результат: " << d3 + n << endl;
    cout << "Сколько секунд отнять от исходного времени? ";
    cin >> n;
    cout << "Результат: " << d3 - n << endl;
    cout << d1.PlusOneSecond() << endl;
    cout << d1 << endl;
    cout << d1++ << endl;
    cout << d1 << endl;
    cout << d1-- << endl;
    cout << d1 << endl;
    cout << d2 << endl;
    cout << boolalpha << (d1 > d2) << endl;
    Time d4;
    d4 = d2;
    cout << d4 << endl;
    cout << (d4 += 2) << endl;
    cout << d4 << endl;
    cout << (d4 -= 2) << endl;
    cout << d4 << endl;
    cout << d4(1) << endl;
    cout << d4(2) << endl;
    cout << d4(3) << endl;
    cout << d4(100500) << endl;
    return 0;
}