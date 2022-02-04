// Создать абстрактный базовый класс с виртуальной функцией — корни уравнения.
// Создать производные классы: класс линейных уравнений и класс квадратных уравнений.
// Определить функцию вычисления корней уравнений.

#include <iostream>
#include <windows.h>
using namespace std;

class Eq {
protected:
	double x1, x2;
public:
	Eq() : x1(0), x2(0) {}
	double GetX1() { return x1; }
	double GetX2() { return x2; }
	virtual int Solve() = 0;
};

class LinEq : public Eq {
protected:
	double b, c;
public:
	LinEq(double b, double c) : b(b), c(c) {}
	int Solve() {
		if (b == 0 && c != 0)
			return -3; // рівняння не має жодного кореня
		else {
			if (c == 0 && b == 0)
				return -2; // рівняння має безліч коренів
			x1 = -c / b;
			return 1;
		}
	}
};

class QuaEq : public LinEq {
	double a;
public:
	QuaEq(double a, double b, double c) : a(a), LinEq(b, c) {}
	int Solve() {
		if (a == 0) return LinEq::Solve();
		double D = b * b - 4 * a * c;
		int cr = 0;
		if (D == 0) {
			cr = 1;
			x1 = x2 = -b / (2 * a);
		}
		if (D > 0) {
			cr = 2;
			x1 = (b * -1 + sqrt(D)) / (2 * a);
			x2 = (b * -1 - sqrt(D)) / (2 * a);
		}
		return cr;
	}
};


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int res = 0;
	double a = 0, b = 0, c = 0;

	cout << "Клас лінійних рівнянь\nВведіть коефцієнти: a = ";
	cin >> a;
	cout << "b = ";
	cin >> b;

	LinEq LE(a, b);
	res = LE.Solve();
	if (res == -3)
		cout << "\nРівняння не має жодного кореня" << endl;
	else if (res == -2)
		cout << "\nРівняння має безліч коренів" << endl;
	else
		cout << "\nx = " << LE.GetX1() << endl;

	
	cout << "\nКлас квадратних рівнянь\nВведіть коефцієнти: a = ";
	cin >> a;
	cout << "b = ";
	cin >> b;
	cout << "с = ";
	cin >> c;

	QuaEq QE(a, b, c);
	res = QE.Solve();
	if (res > 0) {
		cout << "\nx1 = " << QE.GetX1() << endl;
		if (a) cout << "x2 = " << QE.GetX2() << endl;
	}
	else if (res == -2)
		cout << "\nРівняння має безліч коренів" << endl;
	else
		cout << "\nРівняння не має жодного кореня" << endl;

	return 0;
}