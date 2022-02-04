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

// 1. Написать функцию, которая удаляет из строки символ с заданным номером.
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

// 2. Написать функцию, которая удаляет из строки все вхождения в нее заданного символа.
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

// 3. Написать функцию, которая вставляет в строку в указанную позицию заданный символ.
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

// 4. Написать программу, которая заменяет все символы точки "." в строке, введенной пользователем, на символы восклицательного знака "!".
void ReplaceSym(char* str, char ch1, char ch2)
{
	while (*str) {
		if (*str == ch1)
			*str = ch2;
		str++;
	}
}

// 5. Пользователь вводит строку символов и искомый символ, посчитать сколько раз он встречается в строке.
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

// 6. Пользователь вводит строку. Определить количество букв, количество цифр и количество остальных символов, присутствующих в строке.
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
	cout << "Введите строку, содержащую буквы, цифры и другие символы:" << endl;
	cin.getline(str, 100);
	cout << "\nВведите номер символа, который хотите удалить: ";
	int SymToDel;
	cin >> SymToDel;
	DelSymById(str, SymToDel);
	cout << endl << str << endl;
	cout << "\nВведите символ, все вхождения которого хотите удалить: ";
	char ch;
	cin.get();
	cin >> noskipws >> ch;
	DelSym(str, ch);
	cout << endl << str << endl;
	cout << "\nВведите символ, который хотите вставить в строку: ";
	cin.get();
	cin >> ch;
	cout << "\nВведите номер позиции, в которую хотите вставить символ: ";
	int SymToIns;
	cin.get();
	cin >> SymToIns;
	InsSym(str, SymToIns, ch);
	cout << endl << str << endl;
	cout << "\nВведите символ, который хотите заменить: ";
	cin.get();
	cin >> ch;
	cout << "\nВведите символ, которым хотите заменить: ";
	char ch2;
	cin.get();
	cin >> ch2;
	ReplaceSym(str, ch, ch2);
	cout << endl << str << endl;
	cout << "\nВведите символ, вхождения которого хотите посчитать: ";
	cin.get();
	cin >> ch;
	cout << endl << CountSym(str, ch) << endl;
	cout << "\nВ вашей строке присутствует:" << endl;
	cout << "\nБукв: " << CountStr(str, IsAlpha) << endl;
	cout << "Цифр: " << CountStr(str, IsDigit) << endl;
	cout << "Остальных символов: " << CountStr(str, IsSymbol) << endl;
	
	return 0;
}