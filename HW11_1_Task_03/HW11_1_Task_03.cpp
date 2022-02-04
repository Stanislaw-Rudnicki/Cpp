// Написать функцию, определяющую количество положительных,
// отрицательных и нулевых элементов передаваемого ей массива.

#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
using namespace std;

void ShowMas(int arr[], int size)
{
	for (int i = 0; i < size; i++)
		cout << arr[i] << " ";
	cout << endl;
}

void InputMasRand(int arr[], int size, int b = 100, int a = 0)
{
	srand(time(0));
	if (a > b)swap(b, a);
	for (int i = 0; i < size; ++i)
		arr[i] = a + rand() % (b - a + 1);
}

void ShowPosNeg(int arr[], int size)
{
	int pos = 0, neg = 0, zero = 0;
	for (int i = 0; i < size; ++i) 
		if (arr[i] > 0) pos++;
		else if (arr[i] < 0) neg++;
		else zero++;
	
	cout << "\nПоложительных:\t" << pos << "\nОтрицательных:\t" << neg << "\nНулевых:\t" << zero << endl;
}

int main() {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int mas[100]{ 0 };
	int a = -100, b = 100, size = 20;

	InputMasRand(mas, size, b, a);
	ShowMas(mas, size);
	ShowPosNeg(mas, size);

	return 0;
}