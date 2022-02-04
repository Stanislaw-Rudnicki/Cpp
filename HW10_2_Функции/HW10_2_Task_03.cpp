// Число называется совершенным, если сумма всех его делителей равна ему самому.
// Напишите функцию поиска таких чисел во введенном интервале.

#include <iostream>
#include <windows.h>
using namespace std;

void Perfect(int a, int b)
{
	if (a > b) swap(a, b);
	int flag = 0;
	for (int i = a; i <= b; (i % 2 == 0) ? i += 2 : i++) {
		int sum = 1;
		for (int j = 2; j < sqrt(i); j++) {
			if (i % j == 0)
				sum += j + i / j;
		}
		if (sum == i && sum != 1) {
			cout << i << ", ";
			flag++;
		}
	}
	if (!flag)
		cout << "\b\b отсутствуют. ";
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int a, b;
	cout << "Введите первое число (int): ";
	cin >> a;
	cout << "Введите второе число (int): ";
	cin >> b;

	cout << endl << "Совершенные числа во введенном интервале: ";
	Perfect(a, b);
	cout << "\b\b." << endl;

	return 0;
}