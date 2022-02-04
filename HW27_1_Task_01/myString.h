// Разработать класс String, который в дальнейшем будет использоваться для работы со строками.
// Класс должен содержать: 
// - Конструктор по умолчанию, позволяющий создать строку длиной 80 символов;
// - Конструктор, позволяющий создавать строку произвольного размера;
// - Конструктор, который создаёт строку и инициализирует её строкой, полученной от пользователя;
// - Конструктор копирования.
// Класс должен содержать методы для ввода строк с клавиатуры и вывода строк на экран.

#pragma once

#include <iostream>
#include <stdio.h>
using namespace std;

class myString {
	char* str;
	size_t cap;
public:
	// Конструктор по умолчанию, позволяющий создать строку длиной 80 символов
	myString() :myString(0, 0) {}
	// Конструктор, позволяющий создавать строку произвольного размера
	explicit myString(size_t c) :myString(0, c) {}
	// Конструктор, который создаёт строку и инициализирует её строкой, полученной от пользователя
	myString(const char* s) :myString(s, 0) {}
	myString(const char* s, size_t c) {
		size_t len = 0;
		if (s)
			len = strlen(s);
		if (len >= c)
			c = len + 1;
		cap = c;
		if (c) {
			str = new char[c] {0};
			if (len)
				strcpy_s(str, c, s);
		}
		else
			str = 0;
	}
	// Конструктор копирования
	myString(const myString& obj) :myString(obj.str, obj.cap) {}
	// Конструктор переноса
	myString(myString&& obj) {
		cap = obj.cap;
		str = obj.str;
		obj.str = 0;
	}
	myString operator= (const myString& obj) {
		if (this != &obj) {
			if (cap < obj.cap) {
				delete[] str;
				cap = obj.cap;
				str = new char[obj.cap];
			}
			strcpy_s(str, cap, obj.str);
		}
		return *this;
	}
	myString operator= (myString&& obj) {
		delete[] str;
		cap = obj.cap;
		str = obj.str;
		obj.str = 0;
		return *this;
	}
	myString operator+ (const char* r) {
		int lenR = strlen(r);
		int lenN = lenR + strlen(str);
		myString temp(str, lenN + 1);
		strcat(temp.str, r);
		return temp;
	}
	myString operator+ (const myString& obj) {
		int lenR = strlen(obj.str);
		int lenN = lenR + strlen(str);
		myString temp(str, lenN + 1);
		strcat(temp.str, obj.str);
		return temp;
	}
	bool operator== (const myString& obj) {
		int lenR = strlen(obj.str);
		int lenN = strlen(str);
		if (lenN != lenR)
			return false;
		for (size_t i = 0; i < lenN; i++)
			if (str[i] != obj.str[i])
				return false;
		return true;
	}
	bool operator!= (const myString& obj) {
		return !(operator==(obj));
	}
	char& operator [](int index) {
		if (index < cap)
			return str[index];
		else
			return str[cap - 2];
	}
	friend ostream& operator<< (ostream& out, const myString& obj) {
		out << obj.str;
		return out;
	}
	friend istream& operator>> (istream& in, myString& obj) {
		//in.getline(obj.str, obj.cap);
		//in >> obj.str;
		char* buf = new char[255]{ 0 };
		in.getline(buf, 255);
		int cap = strlen(buf);
		buf = (char*)realloc(buf, cap + 1);
		obj.str = buf;
		obj.cap = cap;
		return in;
	}
	~myString() {
		delete[]str;
	}
	// методы для ввода строк с клавиатуры и вывода строк на экран
	void show() {
		cout << (str ? str : "") << endl;
	}
	int showcap() {
		//cout << "Capacity: " << cap << endl;
		return cap;
	}
	void set() {
		char* buf = new char[255]{ 0 };
		cin.getline(buf, 255);
		myString temp(buf);
		*this = temp;
		delete[]buf;
	}
	char* get() {
		return str;
	}
	void unBind() {
		str = 0;
	}
};