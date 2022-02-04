// Даны два массива : А[M] и B[N] (M и N вводятся с клавиатуры).
// Необходимо создать третий массив минимально возможного размера,
// в котором нужно собрать элементы массива A, которые не включаются в массив B, без повторений.
// в котором нужно собрать элементы массивов A и B, которые не являются общими для них, без повторений.

#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
using namespace std;

int* CreateMas(int n)
{
	int* mas = new int[n];
	if (!mas) {
		cout << "Error memory" << endl;
		exit(-1);
	}
	return mas;
}

void InputRand(int* arr, int n, int b = 10, int a = -10)
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

// Рекурсія з коренями
double Nested_sqrt(int i, int n)
{
	return i == n ? sqrt(4 + n) : sqrt((4.0 + i) + Nested_sqrt(i + 1, n));
}


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(0));

	int m, n;
	cout << "Введіть M = ";
	cin >> m;
	cout << "Введіть N = ";
	cin >> n;

	int* A = CreateMas(m);
	int* B = CreateMas(n);
	
	InputRand(A, m);
	cout << endl << "A[M]:\t";
	ShowMas(A, m);
	InputRand(B, n);
	cout << endl << "B[N]:\t";
	ShowMas(B, n);
	cout << endl;

	int* temp = CreateMas(m+n);
	int* ptemp = temp;
	bool f;
	
	for (int i = 0; i < m; i++)	{
		f = false;
		for (int j = 0; j < n; j++)
			if (*(A + i) == *(B + j)) {
				f = true;
				break;
			}
		if (!f) {
			for (int j = 0; j < ptemp - temp; j++)
				if (*(A + i) == *(temp + j)) {
					f = true;
					break;
				}
		}
		if (!f) {
			*ptemp = *(A + i);
			ptemp++;
		}
	}
		
	int k = ptemp - temp;
	int* C = CreateMas(k);
	for (int i = 0; i < k; i++)	{
		*(C+i) = *(temp+i);
	}
	
	cout << "\n1. Зібрати елементи масиву A, які не включаються до масиву B, без повторень" << endl;
	cout << endl << "C[K]:\t";
	ShowMas(C, k);

	for (int i = 0; i < n; i++) {
		f = false;
		for (int j = 0; j < m; j++)
			if (*(B + i) == *(A + j)) {
				f = true;
				break;
			}
		if (!f) {
			for (int j = 0; j < ptemp - temp; j++)
				if (*(B + i) == *(temp + j)) {
					f = true;
					break;
				}
		}
		if (!f) {
			*ptemp = *(B + i);
			ptemp++;
		}
	}

	int l = ptemp - temp;
	int* D = CreateMas(l);
	for (int i = 0; i < l; i++) {
		*(D + i) = *(temp + i);
	}
	delete[]temp;
	cout << "\n\n2. Зібрати елементи масивів A і B, які не є спільними для них, без повторень" << endl;
	cout << endl << "D[L]:\t";
	ShowMas(D, l);

	delete[]A;
	delete[]B;
	delete[]C;
	delete[]D;

	cout << "\n\n3. Переробив рекурсію з коренями. Якщо є така можливість, поправте, будь ласка, оцінку в системі." << endl;
	cout << "\nВведіть n (int): ";
	int x;
	cin >> x;
	cout << "\nsqrt(5+sqrt(6+sqrt(7+...+sqrt(n+4)))) для n = " << x << ":\t" << Nested_sqrt(1, x) << endl << endl;

	return 0;
}
