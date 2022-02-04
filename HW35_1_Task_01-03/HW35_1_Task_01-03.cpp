#include <iostream>
#include <Windows.h>
#include <time.h>
#include <string>
#include <sstream>
#include <set>
#include <vector>
using namespace std;

// � �������� ����� �������� ����������� ����� ����� �����.
// ��� ������� ����� ������� ����� YES (� �������� �����),
// ���� �� ����� ����� ����������� � ����������� ��� NO, ���� �� �����������.
// ��������� ����� N - ������� �������� ������, � ���� N �����.
//
// Sample Input:
// 6
// 1 2 3 2 3 4
//
// Sample Output:
// NO
// NO
// NO
// YES
// YES
// NO

void Exercise_1() {
    int n;
    string s;
    cout << "N = ";
    cin >> n;

    // � �������� ����� �������� ����������� ����� ����� �����.
    for (size_t i = 0; i < n; i++)
        s += to_string(1 + rand() % 10) + " ";
    cout << s << endl;

    set<int> set;
    stringstream ss(s);
    while (ss >> n)
        if (set.insert(n).second)
            cout << "NO\n";
        else
            cout << "YES\n";
}

// ���� ��� ������ �����, �� ������ ������ �� 100000 ����� �����.
// ���������, ������ ����� �������� ��������� �� � ������� ������, ��� � � �������.
//
// Sample Input:
// 3
// 1 3 2
// 3
// 4 3 2
// Sample Output:
// 2

void Exercise_2() {
    int n, m;
    cout << "N = ";
    cin >> n;
    vector<int> vec1(n);
    for (size_t i = 0; i < n; i++)
        vec1[i] = (1 + rand() % 100);
    for (auto i : vec1)
        cout << i << ' ';
    cout << endl << endl;
    
    cout << "M = ";
    cin >> m;
    vector<int> vec2(m);
    for (size_t i = 0; i < m; i++)
        vec2[i] = (1 + rand() % 100);
    for (auto i : vec2)
        cout << i << ' ';
    cout << endl << endl;

    set<int> set1(vec1.begin(), vec1.end()), set2;
    for (auto i : vec2)
        if (!set1.insert(i).second)
            set2.insert(i);

    cout << "� ������� � � ������� ������ ��������� �������� �����: " << set2.size() << endl;
}

// ���� ��� ������ �����, �� ������ ������ �� 100000 ����� �����.
// ������� �� �����, �� ������� �� � ������, ��� � � ����� ������ � ������� ���������.
// ��������� ����� N - ������� �������� ������� ������, � ���� N ����� ������� ������.
// ���� ��������� ����� M - ������� �������� ������� ������, � ���� M ����� ������� ������.
//
// Sample Input:
// 3
// 1 3 2
// 3
// 4 3 2
// Sample Output:
// 2 3

void Exercise_3() {
    int n, m;
    cout << "N = ";
    cin >> n;
    vector<int> vec1(n);
    for (size_t i = 0; i < n; i++)
        vec1[i] = (1 + rand() % 100);
    for (auto i : vec1)
        cout << i << ' ';
    cout << endl << endl;

    cout << "M = ";
    cin >> m;
    vector<int> vec2(m);
    for (size_t i = 0; i < m; i++)
        vec2[i] = (1 + rand() % 100);
    for (auto i : vec2)
        cout << i << ' ';
    cout << endl << endl;

    set<int> set1(vec1.begin(), vec1.end()), set2;
    for (auto i : vec2)
        if (!set1.insert(i).second)
            set2.insert(i);

    for (auto i : set2)
        cout << i << ' ';
    cout << endl;
}


int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
   
    srand(time(0));

    Exercise_1();
    system("pause");
    system("cls");
    Exercise_2();
    system("pause");
    system("cls");
    Exercise_3();

    return 0;
}