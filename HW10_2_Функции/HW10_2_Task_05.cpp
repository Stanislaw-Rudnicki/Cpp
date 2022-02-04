// �������� �������, ������� ����������, �������� �� ����������� ������������ �����.

#include <iostream>
#include <windows.h>
using namespace std;

bool lucky(int a) {
	int sum1, sum2;
	sum1 = a / 100000 + (a / 10000 % 10) + (a / 1000 % 10);
	sum2 = a / 100 % 10 + (a / 10 % 10) + a % 10;
	return (sum1 == sum2);
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int a;
	cout << "������ ����������� �����: ";
	cin >> a;

	if (a > 99999 && a < 1000000) {
		cout << "\n\t����� ";
		if (!lucky(a)) cout << "�� ";
		cout << "�������." << endl;
	}
	else
		cout << "\n\t����� �� �����������!" << endl;
}