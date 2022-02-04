// ����������� ����� String, ������� � ���������� ����� �������������� ��� ������ �� ��������.
// ����� ������ ���������: 
// - ����������� �� ���������, ����������� ������� ������ ������ 80 ��������;
// - �����������, ����������� ��������� ������ ������������� �������;
// - �����������, ������� ������ ������ � �������������� � �������, ���������� �� ������������;
// - ����������� �����������.
// ����� ������ ��������� ������ ��� ����� ����� � ���������� � ������ ����� �� �����.


#include <iostream>
#include <stdio.h>
using namespace std;

class myString {
	char* str;
	size_t cap;
public:

	// ����������� �� ���������, ����������� ������� ������ ������ 80 ��������
	myString() :myString(0, 80) {}

	// �����������, ����������� ��������� ������ ������������� �������
	explicit myString(size_t c) :myString(0, c) {}

	// �����������, ������� ������ ������ � �������������� � �������, ���������� �� ������������
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
	// ����������� �����������
	myString(const myString& obj) :myString(obj.str, obj.cap) {}

	// ����������� ��������
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

	// ������ ��� ����� ����� � ���������� � ������ ����� �� �����
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
	myString ob("��������?", 2000);
	return ob;
}




int main() {

	setlocale(LC_ALL, "Russian");
	cout << "����������� �� ���������, ����������� ������� ������ ������ 80 ��������" << endl;
	myString S1;
	cout << "S1 ";
	S1.showcap();
	cout << "\n�����������, ����������� ��������� ������ ������������� �������" << endl;
	myString S2(255);
	cout << "S2 ";
	S2.showcap();
	cout << "\n�����������, ������� ������ ������ � �������������� � �������, ���������� �� ������������" << endl;
	myString S3("�������");
	cout << S3 << endl;
	cout << "S3 ";
	S3.showcap();
	cout << "\n����������� �����������" << endl;
	myString S4(S3);
	cout << S4 << endl;
	myString S5;
	S5 = S3;
	cout << S5 << endl;

	cout << "\n����������� ��������" << endl;
	myString S6;
	S6 = func();
	cout << S6 << endl;

	cout << "\n������ ��� ����� ����� � ���������� � ������ ����� �� �����" << endl;
	cout << "������� ������: ";
	S5.set();
	S5.show();

	cout << "\n���������� ���������� �����-������" << endl;
	cout << "������� ������: ";
	cin >> S5;
	cout << S5 << endl;

	cout << "\n���������� ��������� ��������" << endl;
	S2 = S4 + " �� ";
	S2.show();
	S2 = S2 + S6;
	S2.show();

	cout << "\n���������� ���������� ���������" << endl;
	cout << "(" << S2 << " == " << S4 << "): " << boolalpha << (S2 == S4) << endl;
	cout << "(" << S2 << " != " << S4 << "): " << boolalpha << (S2 != S4) << endl;

	cout << "\n���������� ��������� ����������" << endl;
	cout << "S2[19]: " << S2[19] << endl;
	S2[19] = '!';
	cout << S2 << endl;

	return 0;
}
