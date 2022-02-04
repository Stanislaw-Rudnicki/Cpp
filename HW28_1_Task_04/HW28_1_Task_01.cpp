// Добавить в строковый класс функцию, которая создает строку,
// содержащую пересечение двух строк, то есть общие символы для двух строк.
// Например, результатом пересечения строк «sdqcg» «rgfas34»
// будет строка «sg». Для реализации функции перегрузить оператор * (бинарное умножение).

#include <iostream>
#include <Windows.h>
using namespace std;

class MyString {
	char* str;
	size_t cap;
public:
	MyString() :MyString(0, 0) {}
	// Конструктор, позволяющий создавать строку произвольного размера
	explicit MyString(size_t c) :MyString(0, c) {}
	// Конструктор, который создаёт строку и инициализирует её строкой, полученной от пользователя
	MyString(const char* s) :MyString(s, 0) {}
	MyString(const char* s, size_t c);
	// Конструктор копирования
	MyString(const MyString& obj) :MyString(obj.str, obj.cap) {}
	// Конструктор переноса
	MyString(MyString&& obj);
	// Деструктор
	~MyString();
	MyString operator=(const MyString& obj);
	MyString operator=(MyString&& obj);
	MyString operator+(const char* r);
	MyString operator+(const MyString& obj);
	MyString operator*(const MyString& obj);
	bool operator==(const MyString& obj);
	bool operator!=(const MyString& obj);
	char& operator[](int index);
	friend MyString operator*(const char* l, const MyString& obj);
	friend ostream& operator<<(ostream& out, const MyString& obj);
	friend istream& operator>>(istream& in, MyString& obj);
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
		MyString temp(buf);
		*this = temp;
		delete[]buf;
	}
	char* get() { return str; }
	void unBind() { str = 0; }
};
MyString::MyString(const char* s, size_t c) {
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
MyString::MyString(MyString&& obj) {
		cap = obj.cap;
		str = obj.str;
		obj.str = 0;
}
MyString::~MyString() {
	delete[]str;
}
MyString MyString::operator=(const MyString& obj) {
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
MyString MyString::operator=(MyString&& obj) {
	delete[] str;
	cap = obj.cap;
	str = obj.str;
	obj.str = 0;
	return *this;
}
MyString MyString::operator+(const char* r) {
	int lenR = strlen(r);
	int lenN = lenR + strlen(str);
	MyString temp(str, lenN + 1);
	strcat(temp.str, r);
	return temp;
}
MyString MyString::operator+(const MyString& obj) {
	int lenR = strlen(obj.str);
	int lenN = lenR + strlen(str);
	MyString temp(str, lenN + 1);
	strcat(temp.str, obj.str);
	return temp;
}
MyString MyString::operator*(const MyString& obj) {
	int lenR = strlen(obj.str);
	int len = strlen(str);
	char* temp = new char[lenR < len ? lenR + 1 : len + 1] {0};
	char* temp0 = temp;
	for (size_t i = 0; i < len; i++)
		if (!strchr(temp0, str[i]))
			if (strchr(obj.str, str[i])) {
				*temp = str[i];
				temp++;
			}
	return temp0;
}
bool MyString::operator==(const MyString& obj) {
	int lenR = strlen(obj.str);
	int lenN = strlen(str);
	if (lenN != lenR)
		return false;
	for (size_t i = 0; i < lenN; i++)
		if (str[i] != obj.str[i])
			return false;
	return true;
}
bool MyString::operator!=(const MyString& obj) {
	return !(operator==(obj));
}
char& MyString::operator[](int index) {
	if (index < cap)
		return str[index];
	else
		return str[cap - 2];
}
MyString operator*(const char* l, const MyString& obj) {
	MyString temp(l);
	return temp * obj;
}
ostream& operator<<(ostream& out, const MyString& obj) {
	out << obj.str;
	return out;
}
istream& operator>>(istream& in, MyString& obj) {
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


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

	MyString s1 = "sdqcg";
	MyString s2 = "rgfas34";

	cout << s1 * s2 << endl;
	cout << s2 * s1 << endl;
	cout << s1 * "sfcsdfsdfd" << endl;
	cout << "sfcsdfsdfd" * s1 << endl;
    
    return 0;
}