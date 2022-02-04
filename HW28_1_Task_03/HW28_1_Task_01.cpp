// Создайте класс Date, который будет содержать информацию о дате (день, месяц, год).
// С помощью механизма перегрузки операторов, определите операцию разности двух дат
// (результат в виде количества дней между датами),
// а также операцию увеличения даты на определенное количество дней.

#include <iostream>
#include <Windows.h>
#include <iomanip>
using namespace std;

class Date {
	unsigned int m_d : 5;
	unsigned int m_m : 4;
	         int m_y : 12;
             int GetJulianDay();
             bool IsLeap();
public:
    Date();
    Date(int, int, int);
    Date(const char*);
    Date(int);
    Date operator + (int);
    int operator - (const Date&);
    Date operator - (int);
    friend Date operator + (int, const Date&);
    friend istream& operator >> (istream&, Date&);
    friend ostream& operator << (ostream&, const Date&);
};
int Date::GetJulianDay() {
    int m = m_m, d = m_d, y = m_y;
    int var1, var2, var3;
    if (m > 2)
        m -= 3;
    else {
        m += 9;
        y--;
    }
    var1 = 146097 * (y / 100) / 4;
    var2 = 1461 * (y % 100) / 4;
    var3 = (153 * m + 2) / 5 + d + 1721119;
    return var1 + var2 + var3;
}
bool Date::IsLeap() {
    return ((m_y) % 4 == 0 && ((m_y) % 100 != 0 || (m_y) % 400 == 0));
}
Date::Date() {
        SYSTEMTIME st;
        GetSystemTime(&st);
        m_d = st.wDay;
        m_m = st.wMonth;
        m_y = st.wYear;
}
Date::Date(int d, int m, int y) {
    m_y = y;
    (1 <= m && m <= 12) ? m_m = m : m_m = 1;
    if (m_m == 2 && IsLeap())
        (1 <= d && d <= 29) ? m_d = d : m_d = 1;
    if (m_m == 2 && !IsLeap())
        (1 <= d && d <= 28) ? m_d = d : m_d = 1;
    for (int i : {1, 3, 5, 7, 8, 10, 12})
        if (m_m == i) {
            (1 <= d && d <= 31) ? m_d = d : m_d = 1;
            break;
        }
        else if (m_m == 2)
            break;
        else
            (1 <= d && d <= 30) ? m_d = d : m_d = 1;
}
Date::Date(const char* s) {
    int d = 1, m = 1, y = 1970;
    if (sscanf(s, "%d.%d.%d", &d, &m, &y) < 3) {
        m_d = 1;
        m_m = 1;
        m_y = 1970;
    }
    else {
        Date temp(d, m, y);
        *this = temp;
    }
}
Date::Date(int jd) {
    int l, j, i, n;
    l = jd + 68569;
    n = (4 * l) / 146097;
    l = l - (146097 * n + 3) / 4;
    i = (4000 * (l + 1)) / 1461001;
    l = l - (1461 * i) / 4 + 31;
    j = (80 * l) / 2447;
    m_d = l - (2447 * j) / 80;
    l = j / 11;
    m_m = j + 2 - (12 * l);
    m_y = 100 * (n - 49) + i + l;
}
Date Date::operator + (int a) {
    return GetJulianDay() + a;
}
int Date::operator - (const Date& a) {
    Date d(a);
    return GetJulianDay() - d.GetJulianDay();
}
Date Date::operator - (int a) {
    return GetJulianDay() - a;
}
Date operator + (int l, const Date& r) {
    Date res(r);
    return res.GetJulianDay() + l;
}
istream& operator >> (istream& fin, Date& a) {
    char buf[11];
    fin.getline(buf, 11);
    int d = 1, m = 1, y = 1970;
    if (sscanf(buf, "%d.%d.%d", &d, &m, &y) < 3) {
        a.m_d = 1;
        a.m_m = 1;
        a.m_y = 1970;
    }
    else {
        a.m_d = d;
        a.m_m = m;
        a.m_y = y;
    }
    return fin;
}
ostream& operator << (ostream& out, const Date& a) {
    out << setw(2) << setfill('0') << a.m_d << "." << setw(2) << setfill('0') << a.m_m << "." << a.m_y;
    return out;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Date d1;
    Date d2("28.02.2019");
    cout << d1 << " - " << d2 << " = " << d1 - d2 << "\n\n";
    cout << "Введите дату в формате дд.мм.гггг: ";
    Date d3;
    cin >> d3;
    cout << "Ваша дата: " << d3 << endl;
    cout << "Сколько дней прибавить? ";
    int n;
    cin >> n;
    cout << "Результат: " << d3 + n << endl;
    cout << "Сколько дней отнять от исходной даты? ";
    cin >> n;
    cout << "Результат: " << d3 - n << endl;

    return 0;
}