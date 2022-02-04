// Разработать класс String, который в дальнейшем будет использоваться для работы со строками.
// Класс должен содержать: 
// - Конструктор по умолчанию, позволяющий создать строку длиной 80 символов;
// - Конструктор, позволяющий создавать строку произвольного размера;
// - Конструктор, который создаёт строку и инициализирует её строкой, полученной от пользователя;
// - Конструктор копирования.
// Класс должен содержать методы для ввода строк с клавиатуры и вывода строк на экран.


#include <iostream>
#include <stdio.h>
using namespace std;

class myString {
	char* str;
	size_t cap;
public:

	// Конструктор по умолчанию, позволяющий создать строку длиной 80 символов
	myString() :myString(0, 80) {}

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
		in.getline(obj.str, obj.cap);
		//in >> obj.str;
		return in;
	}

	~myString() {
		delete[]str;
	}

	// методы для ввода строк с клавиатуры и вывода строк на экран
	void show() {
		cout << (str ? str : "") << endl;
	}

	void showcap() {
		cout << "Capacity: " << cap << endl;
	}

	void set() {
		cin.getline(str, cap);
	}
};

myString func() {
	myString ob("внимание?", 2000);
	return ob;
}




int main() {

	setlocale(LC_ALL, "Russian");
	cout << "Конструктор по умолчанию, позволяющий создать строку длиной 80 символов" << endl;
	myString S1;
	cout << "S1 ";
	S1.showcap();
	cout << "\nКонструктор, позволяющий создавать строку произвольного размера" << endl;
	myString S2(255);
	cout << "S2 ";
	S2.showcap();
	cout << "\nКонструктор, который создаёт строку и инициализирует её строкой, полученной от пользователя" << endl;
	myString S3("Спасибо");
	cout << S3 << endl;
	cout << "S3 ";
	S3.showcap();
	cout << "\nКонструктор копирования" << endl;
	myString S4(S3);
	cout << S4 << endl;
	myString S5;
	S5 = S3;
	cout << S5 << endl;

	cout << "\nКонструктор переноса" << endl;
	myString S6;
	S6 = func();
	cout << S6 << endl;

	cout << "\nМетоды для ввода строк с клавиатуры и вывода строк на экран" << endl;
	cout << "Введите строку: ";
	S5.set();
	S5.show();

	cout << "\nПерегрузка операторов ввода-вывода" << endl;
	cout << "Введите строку: ";
	cin >> S5;
	cout << S5 << endl;

	cout << "\nПерегрузка оператора сложения" << endl;
	S2 = S4 + " за ";
	S2.show();
	S2 = S2 + S6;
	S2.show();

	cout << "\nПерегрузка операторов сравнения" << endl;
	cout << "(" << S2 << " == " << S4 << "): " << boolalpha << (S2 == S4) << endl;
	cout << "(" << S2 << " != " << S4 << "): " << boolalpha << (S2 != S4) << endl;

	cout << "\nПерегрузка оператора индексации" << endl;
	cout << "S2[19]: " << S2[19] << endl;
	S2[19] = '!';
	cout << S2 << endl;

	return 0;
}
