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

// 1. �������� ������ �������, ��� �������� ����� ������� �������
template <class T>
int LinEq(T a, T b, T& res)
{
	if (a == 0 && b != 0)
		return -3; // ������� �� �� ������� ������
	else {
		if (b == 0 && a == 0)
			return -2; // ������� �� ����� ������
		res = -b / a;
		return 1;
	}
}

// 2. �������� ������ �������, ��� �������� ����� ����������� �������
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

// 3. �������� ������ �������, ��� ������� ����� ������������� �������� � �����.
// ������� ������� ������� �������� � �������� ��������
template <class T>
int FMax(T arr[], int size)
{
	int pmax = 0;
	for (int i = 0; i < size; i++)
		if (arr[pmax] < arr[i])
			pmax = i;
	return pmax;
}

// 4. �������� ������ �������, ��� ������ �����,
// � �������� �� ����� ������� �������� �������� ������
template <class T>
void FZero(T arr[], int size)
{
	int flag = 0;
	for (int i = 0; i < size; i++)
		if (arr[i] == 0) {
			cout << "[" << i << "] ";
			flag++;
		}
	if (flag == 0) cout << "������.";
}

// 5. �������� ������ �������, ��� ������ x � �������� x^y. Y - ���� �����
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

	cout << "1. �������� ������ �������, ��� �������� ����� ������� �������" << endl;
	cout << "\n������ ����������: a = ";
	cin >> a;
	cout << "b = ";
	cin >> b;

	if (LinEq(a, b, res) == -3)
	cout << "\nг������ �� �� ������� ������" << endl;
	else if (LinEq(a, b, res) == -2)
	cout << "\nг������ �� ����� ������" << endl;
	else
	cout << "\nx = " << res << endl;

	cout << "\n2. �������� ������ �������, ��� �������� ����� ����������� �������" << endl;
	cout << "\n������ ����������: a = ";
	cin >> a;
	cout << "b = ";
	cin >> b;
	cout << "� = ";
	cin >> c;

	if (QuaEq(a, b, c, x1, x2) > 0) {
		cout << "\nx1 = " << x1 << endl;
		if (a) cout << "x2 = " << x2 << endl;
	}
	else if (QuaEq(a, b, c, x1, x2) == -2)
		cout << "\nг������ �� ����� ������" << endl;
	else
		cout << "\nг������ �� �� ������� ������" << endl;

	cout << "\n3. �������� ������ �������, ��� ������� ����� ������������� �������� � �����.\n������� ������� ������� �������� � �������� ��������" << endl << endl;

	int mas[100]{ 0 };
	int size = 10;
	InputRand(mas, size, 10, 0);
	ShowMas(mas, size);
	cout << "\n������������ ������� � �����: [" << FMax(mas, size) << "] = " << mas[FMax(mas, size)] << endl;

	cout << "\n4. �������� ������ �������, ��� ������ �����, � �������� �� ����� ������� �������� �������� ������" << endl;
	cout << "\n������� �������� �������� ������: ";
	FZero(mas, size);
	cout << endl;

	cout << "\n5. �������� ������ �������, ��� ������ x � y � �������� x^y. Y - ���� �����" << endl;
	int p;
	double n;
	cout << "\n������ x (double): ";
	cin >> n;
	cout << "������ y (int): ";
	cin >> p;

	cout << endl << n << " ^ " << p << " = " << power(n, p) << endl;

	return 0;
}