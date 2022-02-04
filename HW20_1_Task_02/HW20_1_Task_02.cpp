#include <iostream>
#include <windows.h>

// Нахождение меньшего из двух чисел;
#define MinD(a, b) (((a)<(b))?(a):(b))

// Нахождение большего из двух чисел;
#define MaxD(a, b) (((a)>(b))?(a):(b))

// Возведение числа в квадрат;
#define Sq(a) ((a)*(a))

// Возведение числа в степень;
#define EXP(a, b, c) c=a; for (int i=0; i<(b)-1; c*=(a), i++);

// Проверка числа на четность;
#define Is_even(a) ((a % 2) == 0)

// Проверка числа на нечетность;
#define Is_odd(a) ((a % 2) == 1)

using namespace std;


int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int a = 2, b = 8, c;

	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	cout << "Min: " << MinD(a, b) << endl;
	cout << "Max: " << MaxD(a, b) << endl;
	cout << a << " ^ 2 = " << Sq(a) << endl;
	EXP(a, b, c);
	cout << a << " ^ " << b << " = " << c << endl;
	cout << "Is_even(a): " << Is_even(a) << endl;
	cout << "Is_odd(a): " << Is_odd(a) << endl;

	return 0;
}