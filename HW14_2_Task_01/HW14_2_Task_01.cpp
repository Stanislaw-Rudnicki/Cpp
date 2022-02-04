// �������� ��������� ������� ��� ������ � ������������ ��������:
// ������� ������������� ������������ ������
// ������� ������������� ������������� �������
// ������� ������ ������������� �������
// ������� �������� ������������� �������
// ������� ���������� �������� � ����� �������
// ������� ������� �������� �� ���������� �������
// ������� �������� �������� �� ���������� �������

#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
using namespace std;

// ������� ������������� ������������ ������
int* CreateMas(int n)
{
	int* mas = new int[n];
	if (!mas) {
		cout << "Error memory" << endl;
		exit(-1);
	}
	return mas;
}

// ������� ������������� ������������� �������
void InputRand(int* arr, int n, int b = 10, int a = -10)
{
	if (a > b)swap(b, a);
	for (int i = 0; i < n; ++i)
		arr[i] = a + rand() % (b - a + 1);
}

// ������� ������ ������������� �������
void ShowMas(int* arr, int n)
{
	for (int i = 0; i < n; i++)
		cout << *(arr + i) << "\t";
	cout << endl;
}

// ������� �������� ������������� �������
void DelMas(int* arr)
{
	delete[]arr;
}

// ������� ���������� �������� � ����� �������
int* AddElem(int* arr, int& n, int val)
{
	int* temp = CreateMas(n+1);
	for (int i = 0; i < n; i++)
		temp[i] = arr[i];
	temp[n] = val;
	n++;
	DelMas(arr);
	return temp;
}

// ������� ������� �������� �� ���������� �������
int* InsElem(int* arr, int& n, int id, int val)
{
	int* temp = CreateMas(n + 1);
	for (int i = 0, j = 0; j < n; i++, j++) {
		i == id ? i++ : i;
		temp[i] = arr[j];
	}
	temp[id] = val;
	n++;
	DelMas(arr);
	return temp;
}

// ������� �������� �������� �� ���������� �������
int* DelElem(int* arr, int& n, int id)
{
	int* temp = CreateMas(n - 1);
	for (int i = 0, j = 0; j < n; i++, j++) {
		i == id ? j++ : j;
		temp[i] = arr[j];
	}
	n--;
	DelMas(arr);
	return temp;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(0));

	int n, a = -10, b = 10;
	cout << "������� ���������� ��������� ������� N = ";
	cin >> n;

	int* Mas = CreateMas(n);

	InputRand(Mas, n);
	cout << endl << "Mas[N]:\t\t";
	ShowMas(Mas, n);
	cout << endl;

	cout << "���������� �������� (��������� ��������) � ����� �������";
	int val = a + rand() % (b - a + 1);
	Mas = AddElem(Mas, n, val);
	cout << "\n\nMas[N+1]:\t";
	ShowMas(Mas, n);
	cout << endl;

	int id = rand() % n;
	val = a + rand() % (b - a + 1);
	cout << "������� �������� (���������� = " << val << ") �� ���������� (���������� = " << id << ") �������";
	Mas = InsElem(Mas, n, id, val);
	cout << "\n\nMas[N+2]:\t";
	ShowMas(Mas, n);
	cout << endl;

	id = rand() % n;
	cout << "�������� �������� �� ���������� (���������� = " << id << ") �������";
	Mas = DelElem(Mas, n, id);
	cout << "\n\nMas[N-1]:\t";
	ShowMas(Mas, n);
	cout << endl;

	DelMas(Mas);
	
	return 0;
}
