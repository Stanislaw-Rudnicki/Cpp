// �) � ������� main ������� ��� ������� ����� ������������� (����������) ����� �� ����� function.h (show())
// �) ���������� ���������, ������� ��������� ����� ��� ������ ����� ��������������.
// �������� INTEGER - ����� ������, CHAR - ���������� DOUBLE - ���������. (#define INTEGER)

#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#define INTEGER
//#define DOUBLE
//#define CHAR
#include "function.h"
using namespace std;

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(0));
	int n = 10;
	
	DATATYPE* Mas = CreateMas(n);
	InputMas(Mas, n);
	ShowMas(Mas, n);
	cout << endl;
	EditMas(Mas, n);
	cout << endl;
	ShowMas(Mas, n);
	cout << endl;
	cout << "�in: " << Mas[MinMas(Mas, n)] << endl;
	cout << "�ax: " << Mas[MaxMas(Mas, n)] << endl << endl;
	SortMas(Mas, n);
	ShowMas(Mas, n);
	cout << endl;

	DelMas(Mas);
	return 0;
}