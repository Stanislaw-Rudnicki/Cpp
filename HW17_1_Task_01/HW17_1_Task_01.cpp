// 1. �������� ���������, ����������� ����������� �����.
// ���������� �������������� �������� � ������������ �������: �����, ��������, ���������, �������.

#include <iostream>
#include <windows.h>
#include <cstdlib>

using namespace std;

typedef struct Complex {
	double Re;
	double Im;
} z;

void SetComplex(z& z1) {
	cout << "������������ ����� = "; cin >> z1.Re;
	cout << "������ ����� = "; cin >> z1.Im;
}

void ShowComplex(z& z1) {
	cout << z1.Re << " + (" << z1.Im << ")i";
}

z Sum(z& z1, z& z2) {
	z sum;
	sum.Re = z1.Re + z2.Re;
	sum.Im = z1.Im + z2.Im;
	return sum;
}

z Diff(z& z1, z& z2) {
	z diff;
	diff.Re = z1.Re - z2.Re;
	diff.Im = z1.Im - z2.Im;
	return diff;
}

z Prod(z& z1, z& z2) {
	z prod;
	prod.Re = (z1.Re * z2.Re) - (z1.Im * z2.Im);
	prod.Im = (z1.Im * z2.Re) + (z2.Im * z1.Re);
	return prod;
}

z Quot(z& z1, z& z2) {
	z quot;
	quot.Re = (z1.Re * z2.Re + z1.Im * z2.Im) / (pow(z2.Re, 2) + pow(z2.Im, 2));
	quot.Im = (z1.Im * z2.Re - z2.Im * z1.Re) / (pow(z2.Re, 2) + pow(z2.Im, 2));
	return quot;
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	z comp1, comp2;
	cout << "������� ������ ����������� �����: " << endl;
	SetComplex(comp1);
	cout << "������ ����������� �����: ";
	ShowComplex(comp1); cout << endl << endl;
	cout << "������� ������ ����������� �����: " << endl;
	SetComplex(comp2);
	cout << "������ ����������� �����: ";
	ShowComplex(comp2); cout << endl << endl;
	z sum = Sum(comp1, comp2);
	z diff = Diff(comp1, comp2);
	z prod = Prod(comp1, comp2);
	z quot = Quot(comp1, comp2);
	cout << "����� ���� ����� = ";
	ShowComplex(sum); cout << endl;
	cout << "�������� ���� ����� = ";
	ShowComplex(diff); cout << endl;
	cout << "������������ ���� ����� = ";
	ShowComplex(prod); cout << endl;
	cout << "������� ���� ����� (������/������) = ";
	ShowComplex(quot); cout << endl;
	
	return 0;
}


