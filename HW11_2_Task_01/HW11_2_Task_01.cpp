// Ќаписать функцию, реализующую алгоритм линейного поиска заданного ключа в одномерном массиве.

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

int LinearSearch(int arr[], int size, int key)
{
	for (int i = 0; i < size; i++)
		if (arr[i] == key)
			return i;
	return -1;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int mas[100]{ 0 };
	int a = 0, b = 100, size = 30, key, index;

	InputMasRand(mas, size, b, a);
	ShowMas(mas, size);

	cout << "\n¬ведите ключ поиска: ";
	cin >> key;
	index = LinearSearch(mas, size, key);
	if (index != -1)
		cout << "\n”казанное число находитс€ в €чейке с индексом: " << index << endl;
	else
		cout << "\n”казанное число не найдено." << endl;

	return 0;
}