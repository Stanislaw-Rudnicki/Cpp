#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
using namespace std;

template <class T>
void FillMasRec(T arr[], int size, int b = 100, int a = 0)
{
	if (size) {
		FillMasRec(arr, --size, b, a);
		arr[size] = a + rand() % (b - a + 1);
	}
}

// 1. За допомогою рекурсивної функції здійснити виведення на екран елементів одновимірного масиву
template <class T>
void ShowMasRec(T arr[], int size)
{
	if (size) {
		ShowMasRec(arr, --size);
		cout << arr[size] << " ";
	}
}

// 2. За допомогою рекурсивної функції здійснити пошук максимального елемента одновимірного масиву
template <class T>
int FMaxRec(T arr[], int size) {
	int pmax = 0;
	if (size) {
		pmax = FMaxRec(arr, --size);
		return arr[size] < arr[pmax] ? pmax : size;
	}
	else return 1;
}

// 3. За допомогою рекурсивної функції здійснити пошук мінімального елемента одновимірного масиву
template <class T>
int FMinRec(T arr[], int size) {
	int pmin = 0;
	if (size) {
		pmin = FMinRec(arr, --size);
		return arr[size] > arr[pmin] ? pmin : size;
	}
	else return 1;
}

// 4. За допомогою рекурсивної функції обчислити суму елементів одновимірного масиву
template <class T>
T SumRec(T arr[], int size) {
	if (size < 1) return 0;
	return arr[size] + SumRec(arr, --size);
}

// 5. За допомогою рекурсивної функції обчислити середнє арифметичне елементів одновимірного масиву
template <class T>
double AverageRec(T arr[], int size) {
	if (size == 1)
		return arr[size - 1];
	return ((size - 1.0) * AverageRec(arr, size - 1) + arr[size - 1]) / size;
}

// 6. Підрахувати sqrt(5 + sqrt(6 + sqrt(7 + ... + sqrt(n + 4))))
double Nested_sqrt(int i, int n) {
	return i == n ? sqrt(4 + n) : sqrt((4.0 + i) + Nested_sqrt(i + 1, n));
}


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int mas[100]{ 0 };
	int a = -100, b = 100, size = 20;

	/*cout << "1. За допомогою рекурсивної функції здійснити виведення на екран елементів одновимірного масиву" << endl;
	srand(time(0));
	if (a > b)swap(b, a);
	FillMasRec(mas, size, b, a);
	cout << endl;
	ShowMasRec(mas, size);
	cout << endl << endl << endl;
	
	cout << "2. За допомогою рекурсивної функції здійснити пошук максимального елемента одновимірного масиву" << endl;
	int pmax = FMaxRec(mas, size);
	cout << "\nМаксимальний елемент: \t[" << pmax << "] = " << mas[pmax] << endl << endl << endl;
	
	cout << "3. За допомогою рекурсивної функції здійснити пошук мінімального елемента одновимірного масиву" << endl;
	int pmin = FMinRec(mas, size);
	cout << "\nМінімальний елемент: \t[" << pmin << "] = " << mas[pmin] << endl << endl << endl;
	
	cout << "4. За допомогою рекурсивної функції обчислити суму елементів одновимірного масиву" << endl;
	cout << "\nСума елементів одновимірного масиву:\t" << SumRec(mas, size) << endl << endl << endl;
	
	cout << "5. За допомогою рекурсивної функції обчислити середнє арифметичне елементів одновимірного масиву" << endl;
	cout << "\nСереднє арифметичне елементів одновимірного масиву:\t" << AverageRec(mas, size) << endl << endl << endl;*/
	
	cout << "6. Підрахувати sqrt(5+sqrt(6+sqrt(7+...+sqrt(n+4))))" << endl;
	cout << "\n\tВведіть n (int > 5): ";
	int n;
	cin >> n;
	cout << "\nsqrt(5+sqrt(6+sqrt(7+...+sqrt(n+4)))) для n = " << n << ":\t" << Nested_sqrt(1, n) << endl << endl;
	
	return 0;
}