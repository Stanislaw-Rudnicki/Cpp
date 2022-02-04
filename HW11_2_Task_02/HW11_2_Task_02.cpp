// Ќаписать функцию, реализующую алгоритм бинарного поиска заданного ключа в одномерном массиве.

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

void SortMas(int arr[], int size)
{
	int flag;
	do {
		flag = 0;
		for (int i = 0; i < size - 1; i++)
			if (arr[i] > arr[i + 1]) {
				swap(arr[i], arr[i + 1]);
				flag = 1;
			}
	} while (flag);
}

int Search_Binary(int arr[], int left, int right, int key)
{
	int midd = 0;
	while (1) {
		midd = (left + right) / 2;
		if (key < arr[midd])       
			right = midd - 1;      
		else if (key > arr[midd])  
			left = midd + 1;	   
		else                       
			return midd;           
		if (left > right)          
			return -1;
	}
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int mas[100]{ 0 };
	int a = 0, b = 100, size = 30, key, index;

	InputMasRand(mas, size, b, a);
	SortMas(mas, size);
	ShowMas(mas, size);

	cout << "\n¬ведите ключ поиска: ";
	cin >> key;
	index = Search_Binary(mas, 0, size, key);
	if (index >= 0)
		cout << "\n”казанное число находитс€ в €чейке с индексом: " << index << "\n";
	else
		cout << "\n”казанное число не найдено.\n";

	return 0;
}