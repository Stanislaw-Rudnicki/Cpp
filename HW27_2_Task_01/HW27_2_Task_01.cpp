// �������� ����� ��� �������� ������� �������������� �����.
// ����� ������ ������������� ���������������� ��� ��������
// ������� ������������ �� ������ ��������, ������� ��������������, ������� ��������, ������� �����.
// �������-����� ��� �������� ������� ������ ���� ����������� � ������� ����������� �������-������.
// ����� ����� ������ ������� ���������� ��������� ������� � ���������� ��� �������� � ������� ����������� �������-�����.

#include <iostream>
#include <Windows.h>
using namespace std;

class area {
public:
    static int count;

    static double triangle1() /*������� ������������ �� ������� � ������*/
    {
        double a = 0;
        double h = 0;
        cout << "������� ������������ �� ������� � ������" << endl;
        cout << "������� �������" << endl;
        cin >> a;
        cout << "������� ������" << endl;
        cin >> h;
        count++;
        return 0.5 * h * a;
    }

    static double triangle2() // ������� ������������ �� ���� �������� 
    {
        double p = 0;
        double a = 0;
        double b = 0;
        double c = 0;
        cout << "������� ������������ �� ���� ��������" << endl;
        cout << "������� ������� 1" << endl;
        cin >> a;
        cout << "������� ������� 2" << endl;
        cin >> b;
        cout << "������� ������� 3" << endl;
        cin >> c;
        p = (a + b + c) / 2;
        count++;
        return sqrt(p * (p - a) * (p - b) * (p - c));
    }

    static double rectangle() //������� ��������������
    {
        double a = 0;
        double b = 0;
        cout << "������� ��������������" << endl;
        cout << "������� ������� 1" << endl;
        cin >> a;
        cout << "������� ������� 2" << endl;
        cin >> b;
        count++;
        return a * b;
    }
    
    static double square() // ������� �������� �� ����� �������
    {
        double a = 0;
        cout << "������� �������� �� ����� �������" << endl;
        cout << "������� �������" << endl;
        cin >> a;
        count++;
        return a * a;
    }

    static double rhombus() //������� ����� �� ����� ������� � ������
    {
        double a = 0;
        double h = 0;
        cout << "������� ����� �� ����� ������� � ������" << endl;
        cout << "������� �������" << endl;
        cin >> a;
        cout << "������� ������" << endl;
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
        cout << "1. ������� ������������ �� ������� � ������\n2. ������� ������������ �� ���� ��������\n";
        cout << "3. ������� ��������������\n4. ������� �������� �� ����� �������\n5. ������� ����� �� ����� ������� � ������\n0. �����\n";
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
            cout << "���������� ��������� �������: " << area::count << endl;
            n = 0;
        }
    } while (n != 0);

    return 0;
}