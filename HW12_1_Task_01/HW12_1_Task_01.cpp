#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iomanip>
using namespace std;

const int ROW = 15, COL = 15;

void Set2DRND(int arr[][COL], int r, int c, int b = 100, int a = 0)
{
	srand(time(0));
	if (a > b)swap(b, a);
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
			arr[i][j] = a + rand() % (b - a + 1);
}

void Set2DRND(double arr[][COL], int r, int c, int b = 100, int a = 0)
{
	srand(time(0));
	if (a > b)swap(b, a);
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
			arr[i][j] = a + (double)(rand() % (b - a + 1))/100.0 + (rand() % (b - a));
}

void Set2DRND(char arr[][COL], int r, int c, char b = 'Z', char a = 'A')
{
	srand(time(0));
	if (a > b)swap(b, a);
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
			arr[i][j] = char(a + rand() % (b - a + 1));
}

void Show2DRND(int arr[][COL], int r, int c)
{
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++)
			cout << arr[i][j] << "\t";
		cout << endl;
	}
}

void Show2DRND(double arr[][COL], int r, int c)
{
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++)
			cout << fixed << setprecision(2) << arr[i][j] << "\t";
		cout << endl;
	}
}

void Show2DRND(char arr[][COL], int r, int c)
{
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++)
			cout << arr[i][j] << "\t";
		cout << endl;
	}
}

void Max2DRND(int arr[][COL], int r, int c)
{
	int maxi = 0, maxj = 0, mini = 0, minj = 0;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (arr[i][j] % 2 == 0) {
				if (arr[maxi][maxj] < arr[i][j]) {
					maxi = i;
					maxj = j;
				}
				if (arr[mini][minj] > arr[i][j]) {
					mini = i;
					minj = j;
				}
			}
		}
	}
	cout << "\nМаксимальний парний елемент:\t[" << maxi << "][" << maxj << "] = " << arr[maxi][maxj] << endl;
	cout << "Мінімальний парний елемент:\t[" << mini << "][" << minj << "] = " << arr[mini][minj] << endl;
	cout << endl;
}

void Max2DRND(double arr[][COL], int r, int c)
{
	int maxi = 0, maxj = 0, mini = 0, minj = 0;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (arr[maxi][maxj] < arr[i][j]) {
				maxi = i;
				maxj = j;
			}
			if (arr[mini][minj] > arr[i][j]) {
				mini = i;
				minj = j;
			}
		}
	}
	cout << "\nОскільки парність або непарність — це властивість цілих чисел, знаходимо просто:";
	cout << "\nмаксимальний елемент:\t[" << maxi << "][" << maxj << "] = " << arr[maxi][maxj] << endl;
	cout << "мінімальний елемент:\t[" << mini << "][" << minj << "] = " << arr[mini][minj] << endl;
	cout << endl;
}

void Max2DRND(char arr[][COL], int r, int c)
{
	int maxi = 0, maxj = 0, mini = 0, minj = 0;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (arr[i][j] % 2 == 0) {
				if (arr[maxi][maxj] < arr[i][j]) {
					maxi = i;
					maxj = j;
				}
				if (arr[mini][minj] > arr[i][j]) {
					mini = i;
					minj = j;
				}
			}
		}
	}
	cout << "\nМаксимальний парний елемент:\t[" << maxi << "][" << maxj << "] = " << arr[maxi][maxj] << endl;
	cout << "Мінімальний парний елемент:\t[" << mini << "][" << minj << "] = " << arr[mini][minj] << endl;
	cout << endl;
}

void Transpose2DRND(int arr[][COL], int r, int c)
{
	for (int i = 0; i < r; i++)
		for (int j = i+1; j < c; j++)
			swap(arr[i][j], arr[j][i]);
}

void Transpose2DRND(double arr[][COL], int r, int c)
{
	for (int i = 0; i < r; i++)
		for (int j = i+1; j < c; j++)
			swap(arr[i][j], arr[j][i]);
}

void Transpose2DRND(char arr[][COL], int r, int c)
{
	for (int i = 0; i < r; i++)
		for (int j = i+1; j < c; j++)
			swap(arr[i][j], arr[j][i]);
}

void SortByRow(int arr[][COL], int r, int c)
{
	for (int i = 0; i < r; i++)
		sort((int*)arr + i * COL, (int*)arr + i * COL + c);
}

void SortByRow(double arr[][COL], int r, int c)
{
	for (int i = 0; i < r; i++)
		sort((double*)arr + i * COL, (double*)arr + i * COL + c);
}

void SortByRow(char arr[][COL], int r, int c)
{
	for (int i = 0; i < r; i++)
		sort((char*)arr + i * COL, (char*)arr + i * COL + c);
}

int main() {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int r, dt;

	cout << "Вкажіть розмір масиву (3 - 15): ";
	cin >> r;
	while (r < 3 || r > 15) {
		cout << "Будь ласка, від 3 до 15: ";
		cin >> r;
	}
	int c = r;


	cout << "Виберіть чим заповнити - int (1), double (2), char (3): ";
	cin >> dt;
	while (dt < 1 || dt > 3) {
		cout << "Будь ласка, від 1 до 3: ";
		cin >> dt;
	}
	cout << endl;

	if (dt == 1) {
		int mas_int[ROW][COL]{ 0 };
		Set2DRND(mas_int, r, c);
		Show2DRND(mas_int, r, c);
		Max2DRND(mas_int, r, c);
		cout << "Відобразити відносно головної діагоналі:" << endl << endl;
		Transpose2DRND(mas_int, r, c);
		Show2DRND(mas_int, r, c);
		cout << "\nПосортувати окремо кожний стовпець:" << endl << endl;
		SortByRow(mas_int, r, c); // Оскільки матриця вже транспонована, сортуємо по рядках і ще раз транспонуємо.
		Transpose2DRND(mas_int, r, c);
		Show2DRND(mas_int, r, c);
	}
	else if (dt == 2) {
		double mas_double[ROW][COL]{ 0 };
		Set2DRND(mas_double, r, c);
		Show2DRND(mas_double, r, c);
		Max2DRND(mas_double, r, c);
		cout << "Відобразити відносно головної діагоналі:" << endl << endl;
		Transpose2DRND(mas_double, r, c);
		Show2DRND(mas_double, r, c);
		cout << "\nПосортувати окремо кожний стовпець:" << endl << endl;
		SortByRow(mas_double, r, c);
		Transpose2DRND(mas_double, r, c);
		Show2DRND(mas_double, r, c);
	}
	else {
		char mas_char[ROW][COL]{ 0 };
		Set2DRND(mas_char, r, c);
		Show2DRND(mas_char, r, c);
		Max2DRND(mas_char, r, c);
		cout << "Відобразити відносно головної діагоналі:" << endl << endl;
		Transpose2DRND(mas_char, r, c);
		Show2DRND(mas_char, r, c);
		cout << "\nПосортувати окремо кожний стовпець:" << endl << endl;
		SortByRow(mas_char, r, c);
		Transpose2DRND(mas_char, r, c);
		Show2DRND(mas_char, r, c);
	}
	
	cout << endl;
	return 0;
}