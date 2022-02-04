#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
using namespace std;

template <class T>
void InputRand(T arr[], int size, int b = 100, int a = 0)
{
	srand(time(0));
	if (a > b)swap(b, a);
	for (int i = 0; i < size; ++i)
		arr[i] = a + rand() % (b - a + 1);
}

template <class T>
void ShowMas(T arr[], int size)
{
	for (int i = 0; i < size; i++)
		cout << arr[i] << " ";
	cout << endl;
}

// 1. Напишіть шаблон функції, яка обчислює корінь лінійного рівняння
template <class T>
int LinEq(T a, T b, T& res)
{
	if (a == 0 && b != 0)
		return -3; // рівняння не має жодного кореня
	else {
		if (b == 0 && a == 0)
			return -2; // рівняння має безліч коренів
		res = -b / a;
		return 1;
	}
}

// 2. Напишіть шаблон функції, яка обчислює корінь квадратного рівняння
template <class T>
int QuaEq(T a, T b, T c, T& x1, T& x2)
{
	if (a == 0) return LinEq(b, c, x1);
	double D = b * b - 4 * a * c;
	int cr = 0;
	if (D == 0) {
		cr = 1;
		x1 = x2 = (b * -1 + sqrt(D)) / (2 * a);
	}
	if (D > 0) {
		cr = 2;
		x1 = (b * -1 + sqrt(D)) / (2 * a);
		x2 = (b * -1 - sqrt(D)) / (2 * a);
	}
	return cr;
}

// 3. Напишіть шаблон функції, яка здійснює пошук максимального елемента в масиві.
// Функція повертає позицію елемента і виводить значення
template <class T>
int FMax(T arr[], int size)
{
	int pmax = 0;
	for (int i = 0; i < size; i++)
		if (arr[pmax] < arr[i])
			pmax = i;
	return pmax;
}

// 4. Напишіть шаблон функції, яка приймає масив,
// і виводить на екран позиції нульових елементів масиву
template <class T>
void FZero(T arr[], int size)
{
	int flag = 0;
	for (int i = 0; i < size; i++)
		if (arr[i] == 0) {
			cout << "[" << i << "] ";
			flag++;
		}
	if (flag == 0) cout << "відсутні.";
}

// 5. Напишіть шаблон функції, яка приймає x і обчислює x^y. Y - ціле число
template <class T, class U>
T power(T chislo, U step)
{
	int i = 1;
	double res = chislo;
	if (step < 0) {
		step = -step;
		do {
			res *= chislo;
			i++;
		} while (i != step);
		double z = res;
		res = 1;
		res /= z;
		return res;
	}
	else if (step > 1) {
		do {
			res *= chislo;
			i++;
		} while (i != step);
		return res;
	}
	if (step == 1) return res;
	if (step == 0) return 1;
	return res;
}


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	double res = 0, a = 0, b = 0, c = 0, x1 = 0, x2 = 0;

	cout << "1. Напишіть шаблон функції, яка обчислює корінь лінійного рівняння" << endl;
	cout << "\nВведіть коефцієнти: a = ";
	cin >> a;
	cout << "b = ";
	cin >> b;

	if (LinEq(a, b, res) == -3)
	cout << "\nРівняння не має жодного кореня" << endl;
	else if (LinEq(a, b, res) == -2)
	cout << "\nРівняння має безліч коренів" << endl;
	else
	cout << "\nx = " << res << endl;

	cout << "\n2. Напишіть шаблон функції, яка обчислює корінь квадратного рівняння" << endl;
	cout << "\nВведіть коефцієнти: a = ";
	cin >> a;
	cout << "b = ";
	cin >> b;
	cout << "с = ";
	cin >> c;

	if (QuaEq(a, b, c, x1, x2) > 0) {
		cout << "\nx1 = " << x1 << endl;
		if (a) cout << "x2 = " << x2 << endl;
	}
	else if (QuaEq(a, b, c, x1, x2) == -2)
		cout << "\nРівняння має безліч коренів" << endl;
	else
		cout << "\nРівняння не має жодного кореня" << endl;

	cout << "\n3. Напишіть шаблон функції, яка здійснює пошук максимального елемента в масиві.\nФункція повертає позицію елемента і виводить значення" << endl << endl;

	int mas[100]{ 0 };
	int size = 10;
	InputRand(mas, size, 10, 0);
	ShowMas(mas, size);
	cout << "\nМаксимальний елемент в масиві: [" << FMax(mas, size) << "] = " << mas[FMax(mas, size)] << endl;

	cout << "\n4. Напишіть шаблон функції, яка приймає масив, і виводить на екран позиції нульових елементів масиву" << endl;
	cout << "\nПозиції нульових елементів масиву: ";
	FZero(mas, size);
	cout << endl;

	cout << "\n5. Напишіть шаблон функції, яка приймає x і y і обчислює x^y. Y - ціле число" << endl;
	int p;
	double n;
	cout << "\nВведіть x (double): ";
	cin >> n;
	cout << "Введіть y (int): ";
	cin >> p;

	cout << endl << n << " ^ " << p << " = " << power(n, p) << endl;

	return 0;
}