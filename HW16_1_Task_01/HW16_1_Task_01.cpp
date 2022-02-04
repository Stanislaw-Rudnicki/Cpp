#include <iostream>
#include <windows.h>
#include <cstdlib>
using namespace std;


int LenStr(const char* str)
{
	int len = 0;
	while (str && str[len])
		len++;
	return len;
}

// 1. �������� �������, ������� ������� �� ������ ������ � �������� �������.
void DelSymById(char* str, int id)
{
	int len = LenStr(str);
	if (!str || id < 1 || len < id) return;
	str = str + id - 1;
	while (*str) {
		*str = *(str + 1);
		str++;
	}
}

// 2. �������� �������, ������� ������� �� ������ ��� ��������� � ��� ��������� �������.
void DelSym(char* str, char ch)
{
	const char* old = str;
	while (*old) {
		if (*old != ch) {
			*str = *old;
			++str;
		}
		++old;
	}
	*str = '\0';
}

// 3. �������� �������, ������� ��������� � ������ � ��������� ������� �������� ������.
void InsSym(char* str, int id, char ch)
{
	int len = LenStr(str);
	if (!str || id < 1 || len + 2 <= id) return;
	char temp = ch;
	str = str + id - 1;
	while (*str) {
		swap(*str, temp);
		str++;
	}
	*str = temp;
	*++str = '\0';
}

// 4. �������� ���������, ������� �������� ��� ������� ����� "." � ������, ��������� �������������, �� ������� ���������������� ����� "!".
void ReplaceSym(char* str, char ch1, char ch2)
{
	while (*str) {
		if (*str == ch1)
			*str = ch2;
		str++;
	}
}

// 5. ������������ ������ ������ �������� � ������� ������, ��������� ������� ��� �� ����������� � ������.
int CountSym(const char* str, char ch)
{
	int count = 0;
	if (!str) return 0;
	while (*str) {
		if (*str == ch)
			count++;
		str++;
	}
	return count;
}

// 6. ������������ ������ ������. ���������� ���������� ����, ���������� ���� � ���������� ��������� ��������, �������������� � ������.
int IsDigit(int K) { return K >= 48 && K <= 57; }
int IsAlpha(int K) { return (K >= 65 && K <= 90) || (K >= 97 && K <= 122); }
int IsSymbol(int K) { return !IsDigit(K) && !IsAlpha(K); }

int CountStr(const char* source, int (*Test)(int))
{
	int count = 0;
	if (!source) return 0;
	while (*source) {
		if (Test(*source))
			count++;
		source++;
	}
	return count;
}


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	char* str = new char[101]{ 0 };
	cout << "������� ������, ���������� �����, ����� � ������ �������:" << endl;
	cin.getline(str, 100);
	cout << "\n������� ����� �������, ������� ������ �������: ";
	int SymToDel;
	cin >> SymToDel;
	DelSymById(str, SymToDel);
	cout << endl << str << endl;
	cout << "\n������� ������, ��� ��������� �������� ������ �������: ";
	char ch;
	cin.get();
	cin >> noskipws >> ch;
	DelSym(str, ch);
	cout << endl << str << endl;
	cout << "\n������� ������, ������� ������ �������� � ������: ";
	cin.get();
	cin >> ch;
	cout << "\n������� ����� �������, � ������� ������ �������� ������: ";
	int SymToIns;
	cin.get();
	cin >> SymToIns;
	InsSym(str, SymToIns, ch);
	cout << endl << str << endl;
	cout << "\n������� ������, ������� ������ ��������: ";
	cin.get();
	cin >> ch;
	cout << "\n������� ������, ������� ������ ��������: ";
	char ch2;
	cin.get();
	cin >> ch2;
	ReplaceSym(str, ch, ch2);
	cout << endl << str << endl;
	cout << "\n������� ������, ��������� �������� ������ ���������: ";
	cin.get();
	cin >> ch;
	cout << endl << CountSym(str, ch) << endl;
	cout << "\n� ����� ������ ������������:" << endl;
	cout << "\n����: " << CountStr(str, IsAlpha) << endl;
	cout << "����: " << CountStr(str, IsDigit) << endl;
	cout << "��������� ��������: " << CountStr(str, IsSymbol) << endl;
	
	return 0;
}