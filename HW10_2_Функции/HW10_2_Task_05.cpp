// Написать функцию, которая определяет, является ли «счастливым» шестизначное число.

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
	cout << "Введіть шестизначне число: ";
	cin >> a;

	if (a > 99999 && a < 1000000) {
		cout << "\n\tЧисло ";
		if (!lucky(a)) cout << "не ";
		cout << "щасливе." << endl;
	}
	else
		cout << "\n\tЧисло не шестизначне!" << endl;
}