// �������� �������, ������� �������� � �������� ���������� 2 ����� �����
// � ���������� ����� ����� �� ��������� ����� ����.

#include <iostream>
#include <windows.h>
using namespace std;

int MySum(int a, int b)
{	
	if (a > b) swap(a, b);
	return (a + b) * (b - a + 1) / 2;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int a, b;
	cout << "������� ������ ����� (int): ";
	cin >> a;
	cout << "������� ������ ����� (int): ";
	cin >> b;

	cout << endl << "����� ����� �� ��������� ����� ���� = " << MySum(a, b) << endl;

	return 0;
}
