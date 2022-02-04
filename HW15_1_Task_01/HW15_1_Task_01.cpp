// Написать программу, которая содержит функцию Action, принимающую в качестве аргумента,
// указатели на два массива(А и В) и размеры массивов, а также указатель на функцию.
// Пользователю отображается меню, в котором он может выбрать max, min, avg.
// Если выбран max - передается указатель на функцию, которая ищет максимум,
// если выбран min - передается указатель на функцию, которая ищет минимум,
// если выбран avg - передается указатель на функцию, которая ищет среднее.
// Возвращаемое значение функции Action результат выбора пользователя max, min, avg.

#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
using namespace std;

typedef double (*TypeF)(int*, int*, int, int);

int* CreateMas(int n)
{
	int* mas = new int[n];
	if (!mas) {
		cout << "Error memory" << endl;
		exit(-1);
	}
	return mas;
}

void Input1D(int* arr, int n, int b = 10, int a = -10)
{
	if (a > b)swap(b, a);
	for (int i = 0; i < n; ++i)
		arr[i] = a + rand() % (b - a + 1);
}

void ShowMas(int* arr, int n)
{
	for (int i = 0; i < n; i++)
		cout << *(arr + i) << "\t";
	cout << endl;
}

double Fmax(int* arr1, int* arr2 , int n1, int n2)
{
	int max = arr1[0];
	for (int i = 0; i < n1 + n2; i++){
		if (i < n1) {
			if (max < arr1[i])
				max = arr1[i];
		}
		else
			if (max < arr2[i-n1])
				max = arr2[i-n1];}
	return max;
}

double Fmin(int* arr1, int* arr2, int n1, int n2)
{
	int min = arr1[0];
	for (int i = 0; i < n1 + n2; i++)
		if (i < n1) {
			if (min > arr1[i])
				min = arr1[i];
		}
		else 
			if (min > arr2[i - n1])
				min = arr2[i - n1];
	return min;
}

double Favg(int* arr1, int* arr2, int n1, int n2)
{
	double sum = 0;
	for (int i = 0; i < n1 + n2; i++)
		if (i < n1) sum += arr1[i];
		else sum += arr2[i - n1];
	return sum / (n1 + n2);
}

double Action(int* arr1, int* arr2, int n1, int n2, TypeF func)
{
	return func(arr1, arr2, n1, n2);
}

void Delete(int* arr)
{
	delete[]arr;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(0));

	int nA, nB, a = -100, b = 100;
	nA = 1 + rand() % 10;
	nB = 1 + rand() % 10;

	int* A = CreateMas(nA);
	int* B = CreateMas(nB);
	Input1D(A, nA, b, a);
	Input1D(B, nB, b, a);
	cout << "A:\t";
	ShowMas(A, nA);
	cout << endl;
	cout << "B:\t";
	ShowMas(B, nB);
	cout << endl;
	
	TypeF select[] = { Fmax, Fmin, Favg };

	cout << "Виберіть функцію:\nmax (1), min (2), avg (3) або вихід (0): ";
	
	int num;
	cin >> num;
	
	while (num) {
		while (num < 0 || num > 3) {
			cout << "\nБудь ласка, від 0 до 3: ";
			cin >> num;
		}
		while (num >= 0 && num <= 3) {
			if (!num) break;
			cout << "\n" << Action(A, B, nA, nB, select[num - 1]);
			cout << "\n\nІнша функція (1 - 3), або вихід (0): ";
			cin >> num;
		}
	}
	Delete(A);
	Delete(B);

	return 0;
}