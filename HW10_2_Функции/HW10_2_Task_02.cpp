// Написать функцию, которая получает в качестве параметров 2 целых числа
// и возвращает сумму чисел из диапазона между ними.

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
	cout << "Введите первое число (int): ";
	cin >> a;
	cout << "Введите второе число (int): ";
	cin >> b;

	cout << endl << "Сумма чисел из диапазона между ними = " << MySum(a, b) << endl;

	return 0;
}
