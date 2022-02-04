// 2. В файле function.cpp необходимо написать следующие функции для работы с массивом данных:
// а) функцию для заполнения массива случайными значениями;
// б) функцию для вывода значений массива на консоль;
// в) функцию для поиска минимального элемента;
// г) функцию для поиска максимального элемента;
// д) функцию для сортировки;
// е) функцию для редактирования значения массива.
// Данные функции необходимо написать для работы с массивом целых,
// действительных и символьных значений. (Для каждого типа написать отдельную функцию).

#include "function.h"
#include <iostream>

using namespace std;

int* CreateMasInt(int n) {
	int* mas = new int[n];
	if (!mas) {
		cout << "Error memory" << endl;
		exit(-1);
	}
	return mas;
}

void InputRandInt(int* arr, int n, int b, int a) {
	if (a > b)swap(b, a);
	for (int i = 0; i < n; ++i)
		arr[i] = a + rand() % (b - a + 1);
}

void ShowMasInt(int* arr, int n) {
	for (int i = 0; i < n; i++)
		cout << *(arr + i) << " ";
	cout << endl;
}

int MinMasInt(int* arr, int n) {
	int pmin = 0;
	for (int i = 0; i < n; i++)
		if (arr[pmin] > arr[i])
			pmin = i;
	return pmin;
}

int MaxMasInt(int* arr, int n) {
	int pmax = 0;
	for (int i = 0; i < n; i++)
		if (arr[pmax] < arr[i])
			pmax = i;
	return pmax;
}

void SortMasInt(int* arr, int n) {
	int f;
	do {
		f = 0;
		for (int i = 0; i < n - 1; i++)
			if (arr[i] > arr[i + 1]) {
				swap(arr[i], arr[i + 1]);
				f = 1;
			}
	} while (f);
}

void EditMasInt(int* arr, int n) {
	int id;
	cout << "Индекс элемента для редактирования (0 - " << n - 1 << "): ";
	cin >> id;
	int val;
	cout << "Новое значение элемента " << id << ": ";
	cin >> val;
	if (0 <= id || id <= n) arr[id] = val;
}

void DelMasInt(int* arr) {
	delete[]arr;
}


double* CreateMasDouble(int n) {
	double* mas = new double[n];
	if (!mas) {
		cout << "Error memory" << endl;
		exit(-1);
	}
	return mas;
}

void InputRandDouble(double* arr, int n, int b, int a) {
	if (a > b)swap(b, a);
	for (int i = 0; i < n; ++i)
		arr[i] = a + (double)(rand() % (b - a + 1)) / 100.0 + (rand() % (b - a));
}

void ShowMasDouble(double* arr, int n) {
	for (int i = 0; i < n; i++)
		cout << *(arr + i) << " ";
	cout << endl;
}

int MinMasDouble(double* arr, int n) {
	int pmin = 0;
	for (int i = 0; i < n; i++)
		if (arr[pmin] > arr[i])
			pmin = i;
	return pmin;
}

int MaxMasDouble(double* arr, int n) {
	int pmax = 0;
	for (int i = 0; i < n; i++)
		if (arr[pmax] < arr[i])
			pmax = i;
	return pmax;
}

void SortMasDouble(double* arr, int n) {
	int f;
	do {
		f = 0;
		for (int i = 0; i < n - 1; i++)
			if (arr[i] > arr[i + 1]) {
				swap(arr[i], arr[i + 1]);
				f = 1;
			}
	} while (f);
}

void EditMasDouble(double* arr, int n) {
	int id;
	cout << "Введите индекс элемента для редактирования (0 - " << n - 1 << "): ";
	cin >> id;
	double val;
	cout << "Введите новое значение для єлемента " << id << ": ";
	cin >> val;
	if (0 <= id || id <= n) arr[id] = val;
}

void DelMasDouble(double* arr) {
	delete[]arr;
}


char* CreateMasChar(int n) {
	char* mas = new char[n];
	if (!mas) {
		cout << "Error memory" << endl;
		exit(-1);
	}
	return mas;
}

void InputRandChar(char* arr, int n, int b, int a) {
	if (a > b)swap(b, a);
	for (int i = 0; i < n; ++i)
		arr[i] = char(a + rand() % (b - a + 1));
}

void ShowMasChar(char* arr, int n) {
	for (int i = 0; i < n; i++)
		cout << *(arr + i) << " ";
	cout << endl;
}

int MinMasChar(char* arr, int n) {
	int pmin = 0;
	for (int i = 0; i < n; i++)
		if (arr[pmin] > arr[i])
			pmin = i;
	return pmin;
}

int MaxMasChar(char* arr, int n) {
	int pmax = 0;
	for (int i = 0; i < n; i++)
		if (arr[pmax] < arr[i])
			pmax = i;
	return pmax;
}

void SortMasChar(char* arr, int n) {
	int f;
	do {
		f = 0;
		for (int i = 0; i < n - 1; i++)
			if (arr[i] > arr[i + 1]) {
				swap(arr[i], arr[i + 1]);
				f = 1;
			}
	} while (f);
}

void EditMasChar(char* arr, int n) {
	int id;
	cout << "Введите индекс элемента для редактирования (0 - " << n - 1 << "): ";
	cin >> id;
	char val;
	cout << "Введите новое значение для єлемента " << id << ": ";
	cin >> val;
	if (0 <= id || id <= n) arr[id] = val;
}

void DelMasChar(char* arr) {
	delete[]arr;
}