// 1. Написать функцию, добавляющую столбец двухмерному массиву в указанную позицию.
// 2. Написать функцию, удаляющую столбец двухмерного массива по указанному номеру.
// 3. Дана матрица порядка MxN (M строк, N столбцов).
//    Необходимо заполнить ее значениями и написать функцию, осуществляющую циклический сдвиг строк и/или столбцов
//    массива указанное количество раз и в указанную сторону.

#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
using namespace std;

int** CreateArr2D(int R, int C)
{
	int** mas2d = new int* [R];
	for (int i = 0; i < R; i++)
		mas2d[i] = new int[C] {0};
	return mas2d;
}

void Delete(int** arr, int R)
{
	for (int i = 0; i < R; i++)
		delete[]arr[i];
	delete[]arr;
}

void Input1D(int* arr, int n, int b = 10, int a = -10)
{
	if (a > b)swap(b, a);
	for (int i = 0; i < n; ++i)
		arr[i] = a + rand() % (b - a + 1);
}

void Input2D(int** arr, int R, int C, int b = 10, int a = -10)
{
	for (int i = 0; i < R; ++i)
		Input1D(arr[i], C, b, a);
}

void Show1D(int* arr, int n)
{
	for (int i = 0; i < n; i++)
		cout << *(arr + i) << "\t";
	cout << endl;
}

void Show2D(int** arr, int R, int C)
{
	for (int i = 0; i < R; i++)
		Show1D(arr[i], C);
}

int** InsCol2D(int** arr, int m, int& n, int id, int val = 0)
{
	int** temp = CreateArr2D(m, n + 1);
	for (int k = 0; k < m; k++) {
		for (int i = 0, j = 0; j < n; i++, j++) {
			i == id ? i++ : i;
			temp[k][i] = arr[k][j];
		}
		temp[k][id] = val;
	}
	n++;
	Delete(arr, m);
	return temp;
}

int** DelCol2D(int** arr, int m, int& n, int id)
{
	int** temp = CreateArr2D(m, n - 1);
	for (int k = 0; k < m; k++) {
		for (int i = 0, j = 0; j < n; i++, j++) {
			i == id ? j++ : j;
			temp[k][i] = arr[k][j];
		}
	}
	n--;
	Delete(arr, m);
	return temp;
}

void MoveRow(int** arr, int n, int p)
{
	int* b;
	p = (n + p) % n;
	if (p < 0) {
		for (int j = 0; j < abs(p); j++) {
			b = arr[0];
			for (int i = 0; i < n - 1; i++)
				arr[i] = arr[i + 1];
			arr[n-1] = b;
		}
	}
	else {
		for (int j = 0; j < p; j++) {
			b = arr[n - 1];
			for (int i = n - 1; i > 0; i--)
				arr[i] = arr[i - 1];
			arr[0] = b;
		}
	}

}

int** Move2D(int** arr, int m, int n, int mR, int mC)
{
	mR = (m + mR) % m;
	mC = (n + mC) % n;
	if (!mR && !mC) return arr;
	if (!mC) {
		MoveRow(arr, m, mR);
		return arr;
	}
	int** temp = CreateArr2D(m, n);
	for (int k = 0; k < m; k++)
		for (int i = 0; i < n; i++)
			temp[(m + k + mR) % m][(n + i + mC) % n] = arr[k][i];
	Delete(arr, m);
	return temp;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(0));

	int M, N, a = 0, b = 100;
	M = 3 + rand() % 8;
	N = 3 + rand() % 8;
	
	int** mas = CreateArr2D(M, N);
	Input2D(mas, M, N, b, a);
	Show2D(mas, M, N);
	int id = rand() % N;
	int val = 0; 
	cout << "\nФункция, добавляющая столбец двухмерному массиву в указанную (rand() = " << id << ") позицию" << endl;
	mas = InsCol2D(mas, M, N, id, 0);
	cout << endl;
	Show2D(mas, M, N);

	id = rand() % N;
	cout << "\nФункция, удаляющая столбец двухмерного массива по указанному (rand() = " << id << ") номеру" << endl;
	mas = DelCol2D(mas, M, N, id);
	cout << endl;
	Show2D(mas, M, N);

	cout << "\nФункция, осуществляющая циклический сдвиг строк и/или столбцов массива\nуказанное количество раз и в указанную сторону." << endl;
	cout << "\nКуда и на сколько будем сдвигать строки?\nВверх - отрицательное число, никуда - 0, вниз - положительное число: ";
	int mR, mC;
	cin >> mR;
	cout << "\nКуда и на сколько будем сдвигать столбцы?\nВлево - отрицательное число, никуда - 0, вправо - положительное число: ";
	cin >> mC;
	mas = Move2D(mas, M, N, mR, mC);
	cout << endl;
	Show2D(mas, M, N);
	
	Delete(mas, M);

	return 0;
}