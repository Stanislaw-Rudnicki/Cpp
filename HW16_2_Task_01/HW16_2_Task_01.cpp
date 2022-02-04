#include <iostream>
#include <windows.h>
#include <cstdlib>

using namespace std;

// 1. int mystrlen(const char* str); -функція визначає довжину рядка.
int mystrlen(const char* str)
{
	int len = 0;
	while (str && str[len])
		len++;
	return len;
}

// 2. char* mystrcpy(char* str1, const char* str2); -функція копіює рядок str2 в буфер, що адресується через str1. Функція повертає покажчик на перший рядок str1.
char* mystrcpy(char* str1, const char* str2)
{
	char* str = str1;
	while (*str1++ = *str2++);
	return str;
}

// 3. char* mystrcat(char* str1, const char* str2); -функція приєднує рядок str2 до рядка str1. Функція повертає покажчик на перший рядок str1.
char* mystrcat(char* str1, const char* str2)
{
	if (!str1 || !str2) return str1;
	int len2 = mystrlen(str2);
	if (!len2) return str1;
	int len1 = mystrlen(str1);
	char* temp = new char[len1 + len2 + 1]{ 0 };
	while (*str1)
		*temp++ = *str1++;
	while (*str2)
		*temp++ = *str2++;
	return temp - len1 - len2;
}

// 4. char* mystrchr(char* str, char s); -функція здійснює пошук символу s в рядку str. Функція повертає покажчик на перше входження символу в рядок, в іншому випадку 0.
char* mystrchr(char* str, char s)
{
	if (!str) return str;
	while (*str) {
		if (*str == s)
			return str;
		str++;
	}
	return 0;
}

// 5. char* mystrstr(char* str1, char* str2); -функція здійснює пошук підрядка str2 в рядку str1. Функція повертає покажчик на перше входження підрядка str2 в рядок str1, в іншому випадку 0.
char* mystrstr(char* str1, char* str2)
{
	int len1 = mystrlen(str1);
	int len2 = mystrlen(str2);
	if (len2 > len1) return 0;
	while (*str1) {
		if (*str1 == *str2) {
			int i = 0;
			for (i; *str1 == *str2 && *str1; i++) {
				++str1;
				++str2;
			}
			if (*str2 == 0)
				return str1 - len2;
			str2 -= i;
			str1 -= i;
		}
		++str1;
	}
	return 0;
}

// 6. int mystrcmp(const char* str1, const char* str2); -функція порівнює два рядки, і, якщо рядки рівні повертає 0, якщо перший рядок більше другий, то повертає 1, інакше - 1.
int mystrcmp(const char* str1, const char* str2)
{
	for (; *str1 != 0 || *str2 != 0; str1++, str2++) {
		if (*str1 > * str2)
			return 1;
		if (*str1 < *str2)
			return -1;
	}
	return 0;
}

// 7. int StringToNumber(char* str); -функція конвертує рядок в число і повертає це число.
int StringToNumber(char* str)
{
	if (!str) return 0;
	bool IsPos = true;
	if (*str == 45) {
		str++;
		IsPos = !IsPos;
	}
	else if (*str < 48 || *str > 57)
		exit(-1);
	int res = 0;
	while (*str && *str >= 48 && *str <= 57) {
		res = res * 10 + *str - '0';
		str++;
	}
	return IsPos ? res : -res;
}

// 8. char* NumberToString(int number); -функція конвертує число в рядок і повертає покажчик на цей рядок.
char* NumberToString(int number)
{
	int i = 0;
	int num2 = number;
	do {
		num2 /= 10;
		i++;
	} while (num2 != 0);
	char* temp = new char[i + 2]{ 0 };
	int offset = i;
	if (number < 0) {
		*temp = 45;
		temp++;
		offset++;
	}
	for (i -= 1; i >= 0; i--, temp++)
		* temp = abs(number) / int(pow(10, i)) % 10 + '0';
	return temp - offset;
}

// 9. char* Uppercase(char* str1); -функція перетворює рядок у верхній регістр.
char* Uppercase(char* str1)
{
	if (!str1) return str1;
	int len = mystrlen(str1);
	char* temp = new char[len + 1]{ 0 };
	while (*str1) {
		(*str1 >= 97 && *str1 <= 122) ? *temp = *str1 - 32 : *temp = *str1;
		temp++;
		str1++;
	}
	return temp - len;
}

// 10. char* Lowercase(char* str1); -функція перетворює рядок у нижній регістр.
char* Lowercase(char* str1)
{
	if (!str1) return str1;
	int len = mystrlen(str1);
	char* temp = new char[len + 1]{ 0 };
	while (*str1) {
		(*str1 >= 65 && *str1 <= 90) ? *temp = *str1 + 32 : *temp = *str1;
		temp++;
		str1++;
	}
	return temp - len;
}

// 11. char* mystrrev(char* str); -функція реверсує рядок і повертає покажчик на новий рядок.
char* mystrrev(char* str)
{
	if (!str) return str;
	int len = mystrlen(str);
	char* temp = new char[len + 1]{ 0 };
	for (int i = 0, j = len - 1; i < len; i++, j--)
		* (temp + i) = *(str + j);
	return temp;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	cout << "1. Введіть рядок str1: ";
	char* str1 = new char[101]{ 0 };
	cin.getline(str1, 100);
	
	cout << "\nДовжина рядка: " << mystrlen(str1) << endl;
	
	cout << "\nВведіть рядок str2, який містить великі та малі літери: ";
	char* str2 = new char[101]{ 0 };
	cin.getline(str2, 100);
	
	cout << "\n2. Рядок str2 скопійовано в буфер, що адресується через str1: " << endl << endl;
	cout << mystrcpy(str1, str2) << endl;
	
	cout << "\n3. Рядок str2 приєднано до рядка str1: " << endl << endl;
	cout << mystrcat(str1, str2) << endl;
	
	cout << "\n4. Введіть символ для пошуку в рядку str1: ";
	char ch;
	cin >> noskipws >> ch;
	char* res = mystrchr(str1, ch);
	cout << endl;
	if (res)
		cout << res << endl;
	else
		cout << "Входжень не знайдено" << endl;
	
	cout << "\n5. Введіть підрядок str2 для пошуку в рядку str1: ";
	cin.ignore();
	cin.getline(str2, 100);
	res = mystrstr(str1, str2);
	cout << endl;
	if (res)
		cout << res << endl;
	else
		cout << "Входжень не знайдено" << endl;
	
	cout << "\n6. Функція порівнює рядки str1 та str2." << endl << endl;;
	cout << mystrcmp(str1, str2) << endl;
	
	cout << "\n7. Введіть рядок str3, щоб конвертувати його в число: ";
	char* str3 = new char[101]{ 0 };
	cin.getline(str3, 100);
	cout << endl << StringToNumber(str3) << endl;
	
	cout << "\n8. Введіть число, щоб конвертувати його в рядок: ";
	int x;
	cin >> x;
	cout << endl << NumberToString(x) << endl;
	
	cout << "\n9. Функція перетворює рядок у верхній регістр: " << endl << endl;;
	cout << Uppercase(str1) << endl;
	
	cout << "\n10. Функція перетворює рядок у нижній регістр: " << endl << endl;;
	cout << Lowercase(str1) << endl;
	
	cout << "\n11. Функція реверсує рядок: " << endl << endl;;
	cout << mystrrev(str1) << endl;

	delete[]str1;
	delete[]str2;
	delete[]str3;

	return 0;
}