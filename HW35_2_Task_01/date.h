// �������� ����� � ������ Date ��� �������� ���� (��� ����������� ����� ���������).
// � ������ ������ ���� �������-����, ������� ����������� ���� �� 1.
// �������� ��������������� ������������ � �������-�����.
// � ������ ������ ���� ����������� ��������� ++, --,
// != , == , > , <, >> , << , =, +=, -=, ().
// ����������� ������� � ������������� ����������.

#pragma once

#include <iostream>
#include <Windows.h>
#include <iomanip>
using namespace std;

class Date {
    unsigned int m_d : 5;
    unsigned int m_m : 4;
    int m_y : 12;
    int GetJulianDay() const;
    bool IsLeap();
public:
    Date();
    Date(int, int, int);
    Date(const char*);
    Date(int);
    // ����������
    ~Date() {}
    // ����������� �����������
    Date(const Date&);
    // �������� ������������ ������������
    Date& operator=(const Date&);
    // � ������ ������ ���� �������-����, ������� ����������� ���� �� 1
    Date& PlusOneDay();
    Date operator+(int);
    int operator-(const Date&);
    Date operator-(int);
    Date operator++();
    Date operator++(int);
    Date operator--();
    Date operator--(int);
    bool operator==(const Date&);
    bool operator!=(const Date&);
    bool operator<(const Date&);
    bool operator>(const Date&);
    Date& operator+=(int);
    Date& operator-=(int);
    // () ��������� ��� 1 ����, ��� 2 �����, ��� 3 ��
    int operator()(int);
    operator char* ()const;
    friend Date operator+(int, const Date&);
    friend istream& operator>>(istream&, Date&);
    friend ostream& operator<<(ostream&, const Date&);
};
int Date::GetJulianDay() const {
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
Date::Date(const Date& other) {
    m_d = other.m_d;
    m_m = other.m_m;
    m_y = other.m_y;
}
Date& Date::operator=(const Date& other) {
    m_d = other.m_d;
    m_m = other.m_m;
    m_y = other.m_y;
    return *this;
}
Date& Date::PlusOneDay() {
    *this = GetJulianDay() + 1;
    return *this;
}
Date Date::operator+(int a) {
    return GetJulianDay() + a;
}
int Date::operator-(const Date& a) {
    return GetJulianDay() - a.GetJulianDay();
}
Date Date::operator-(int a) {
    return GetJulianDay() - a;
}
Date Date::operator++() {
    PlusOneDay();
    return *this;
}
Date Date::operator++(int) {
    Date temp(*this);
    ++* this;
    return temp;
}
Date Date::operator--() {
    *this = GetJulianDay() - 1;
    return *this;
}
Date Date::operator--(int) {
    Date temp(*this);
    --* this;
    return temp;
}
bool Date::operator==(const Date& other) {
    return GetJulianDay() == other.GetJulianDay();
}
bool Date::operator!=(const Date& other) {
    return !(operator == (other));
}
bool Date::operator<(const Date& other) {
    return GetJulianDay() < other.GetJulianDay();
}
bool Date::operator>(const Date& other) {
    return GetJulianDay() > other.GetJulianDay();
}
Date& Date::operator+=(int n) {
    *this = GetJulianDay() + n;
    return *this;
}
Date& Date::operator-=(int n) {
    int jd = GetJulianDay();
    if (n > jd)
        cout << "n > jd, subtraction is impossible" << endl;
    else {
        *this = jd -= n;
        return *this;
    }
}
int Date::operator()(int p) {
    if (p == 1) return m_d;
    else if (p == 2) return m_m;
    else if (p == 3) return m_y;
    else return -1;
}
Date::operator char* ()const {
    char* tmpStr = new char[11]{ 0 };
    sprintf(tmpStr, "%02d.%02d.%4d", m_d, m_m, m_y);
    return tmpStr;
}
Date operator+(int l, const Date& r) {
    return r.GetJulianDay() + l;
}
istream& operator>>(istream& fin, Date& a) {
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
ostream& operator<<(ostream& out, const Date& a) {
    out << setw(2) << setfill('0') << right << a.m_d << "." << setw(2) << setfill('0') << a.m_m << setfill(' ') << "." << a.m_y;
    return out;
}