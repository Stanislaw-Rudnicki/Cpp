// Описать базовый класс «Строка».
// Методы:
// 1) конструктор без параметров;
// 2) конструктор, принимающий в качестве параметра C-строку (заканчивается нулевым байтом);
// 3) конструктор копирования;
// 4) оператор присваивания;
// 5) получение длины строки;
// 6) очистка строки (сделать строку пустой);
// 7) деструктор;
// 8) конкатенация строк (перегрузить операторы + и +=);
// 9) проверка на равенство (==) и на неравенство (!=).
//
// Описать класс «Битовая строка» производный от класса «Строка»
// (Строки данного класса могут содержать только символы ‘0’ и ‘1’).
// Если в основе инициализирующей строки встретятся любые символы, отличные от допустимых,
// то «Битовая строка» становится пустой.
// Содержимое строки рассматривается как двоичное представление целого числа
// со знаковым разрядом. Отрицательные числа хранятся в дополнительном коде.
// Методы:
// 1) конструктор без параметров;
// 2) конструктор, принимающий в качестве параметра C-строку;
// 3) конструктор копирования;
// 4) оператор присваивания;
// 4) деструктор;
// 5) изменение знака числа (перевод числа в дополнительный код).
// 8) сложение битовых строк (перегрузить операторы + и +=);
// 9) проверка на равенство (==) и на неравенство(!=).

#include <iostream>
#include <Windows.h>
using namespace std;

class MyString {
protected:
	char* str;
	size_t cap;
public:
	// 1) конструктор без параметров;
	MyString() :MyString(0, 0) {}
	// Конструктор, позволяющий создавать строку произвольного размера
	explicit MyString(size_t c) :MyString(0, c) {}
	// 2) конструктор, принимающий в качестве параметра C-строку (заканчивается нулевым байтом);
	MyString(const char* s) :MyString(s, 0) {}
	MyString(const char* s, size_t c);
	// 3) Конструктор копирования
	MyString(const MyString& obj) :MyString(obj.str, obj.cap) {}
	// Конструктор переноса
	MyString(MyString&& obj);
	// 7) Деструктор
	~MyString();
	// 4) Оператор присваивания;
	MyString operator=(const MyString& obj);
	// Оператор присваивания перемещением
	MyString operator=(MyString&& obj);
	MyString operator+(const char* r);
	// 8) конкатенация строк (перегрузить операторы + и +=);
	MyString operator+(const MyString& obj);
	MyString& operator+=(const MyString& obj);
	MyString operator*(const MyString& obj);
	// 9) проверка на равенство (==) и на неравенство (!=).
	bool operator==(const MyString& obj);
	bool operator!=(const MyString& obj);
	char& operator[](int index);
	int operator()(char c);
	// 5) получение длины строки;
	size_t length() const;
	// 6) очистка строки (сделать строку пустой);
	void clear();
	friend MyString operator*(const char* l, const MyString& obj);
	friend ostream& operator<<(ostream& out, const MyString& obj);
	friend istream& operator>>(istream& in, MyString& obj);
	void show() {
		cout << (str ? str : "") << endl;
	}
	size_t capacity() const {
		return cap;
	}
	void set() {
		char* buf = new char[255]{ 0 };
		cin.getline(buf, 255);
		MyString temp(buf);
		*this = temp;
		delete[]buf;
	}
	char* getStr() { return str; }
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
	delete[] str;
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

MyString& MyString::operator+=(const MyString& obj) {
	*this = *this + obj;
	return *this;
}

MyString MyString::operator*(const MyString& obj) {
	int lenR = strlen(obj.str);
	int len = strlen(str);
	char* temp = new char[lenR < len ? lenR + 1 : len + 1]{ 0 };
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

int MyString::operator()(char c) {
	char* p = strchr(str, c);
	if (!p) return -1;
	else return p - str;
}

size_t MyString::length() const {
	return strlen(str);
}

void MyString::clear() {
	delete[]str;
	str = 0;
	cap = 0;
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

class MyBitstring : public MyString {
protected:
	int CheckString(const char* s);
public:
	// 1) конструктор без параметров;
	MyBitstring();
	// 2) конструктор, принимающий в качестве параметра C-строку;
	MyBitstring(const char* s);
	// 3) конструктор копирования;
	MyBitstring(const MyBitstring& b);
	// 4) деструктор;
	~MyBitstring() {};
	// 4) оператор присваивания;
	const MyBitstring& operator=(const MyBitstring& b);
	// 5) изменение знака числа (перевод числа в дополнительный код).
	MyBitstring operator-();
	// 8) сложение битовых строк (перегрузить операторы + и +=);
	const MyBitstring  operator+(const MyBitstring& b);
	MyBitstring& operator+=(const MyBitstring& b);
	// 9) проверка на равенство (==) и на неравенство(!=).
	bool operator==(const MyBitstring& b);
	bool operator!=(const MyBitstring& b);
};

int MyBitstring::CheckString(const char* s) {
	if (!s) return 0;
	int len = strlen(s);
	for (int n = 0; n < len; n++)
		if ((s[n] != '0') && (s[n] != '1'))
			return 0;
	return 1;
}

MyBitstring::MyBitstring() {
	str = 0;
	cap = 0;
}

MyBitstring::MyBitstring(const char* s) : MyString(s) {
	if (!CheckString(s)) {
		delete[] str;
		str = 0;
		cap = 0;
	}
}

MyBitstring::MyBitstring(const MyBitstring& b) : MyString(b.str) {
	if (!CheckString(b.str)) {
		delete[] str;
		str = 0;
		cap = 0;
	}
}

const MyBitstring& MyBitstring::operator=(const MyBitstring& b) {
	if (str)
		delete[] str;
	if (b.str) {
		str = _strdup(b.str);
		cap = b.cap;
	}
	else {
		str = 0;
		cap = 0;
	}
	return *this;
}

MyBitstring MyBitstring::operator-() {
	MyBitstring Res(*this);
	int len = strlen(Res.str);
	for (size_t i = 0; i < len; i++) {
		if (Res.str[i] == '0') Res.str[i] = '1';
		else if (Res.str[i] == '1') Res.str[i] = '0';
	}
	return Res + "0001";
}

const MyBitstring MyBitstring::operator+(const MyBitstring& b) {
	int m, p = 0, a1, a2;
	int len = length(), lenB = b.length();
	len > lenB ? m = len : m = lenB;
	char* r = new char[m + 1];
	memset(r, '0', m);
	r[m] = 0;
	int n1 = len - 1, n2 = lenB - 1;
	for (int n = m - 1; n >= 0; n--) {
		if (n1 >= 0) a1 = str[n1] - '0';
		else a1 = 0;
		if (n2 >= 0) a2 = b.str[n2] - '0';
		else a2 = 0;
		switch (a1 + a2 + p) {
		case 3:
			r[n] = 1;
			p = 2;
			break;
		case 2:
			r[n] = '0';
			p = 1;
			break;
		case 1:
			r[n] = '1';
			p = 0;
			break;
		case 0:
			r[n] = '0';
			p = 0;
			break;
		}
		n1--;
		n2--;
	}
	return MyBitstring(r);
}

MyBitstring& MyBitstring::operator+=(const MyBitstring& b) {
	*this = *this + b;
	return *this;
}

bool MyBitstring::operator==(const MyBitstring& b) {
	int l;
	int len = length(), lenB = b.length();
	len > lenB ? l = len : l = lenB;
	int r = 1;;
	int n1 = len - 1, n2 = lenB - 1, k;
	k = l - 1;
	while (k >= 0) {
		if ((n1 >= 0) && (n2 >= 0) && (str[n1] != b.str[n2])) return 0;
		if ((n1 < 0) && (b.str[n2] != '0')) return 0;
		if ((n2 < 0) && (str[n1] != '0')) return 0;
		k--; n1--; n2--;
	}
	return 1;
}

bool MyBitstring::operator!=(const MyBitstring& b) {
	return !(operator==(b));
}



int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	MyBitstring a("0101");
	MyBitstring b, c;
	
	cout << "a = " << a << endl;
	b = a;
	cout << "b = a;\nb = " << b << endl;
	cout << "a == b ? " << boolalpha << (a == b) << endl;

	b = -b;
	cout << "b = -b;\nb = " << b << endl;
	cout << "a == b ? " << boolalpha << (a == b) << endl;
	
	c = a + b;
	cout << "c = a + b;\nc = " << c << endl;
	return 0;
}