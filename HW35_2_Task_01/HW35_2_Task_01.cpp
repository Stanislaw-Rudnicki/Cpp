// �������� �������� ������������� ������� ��� ��������.
// ������� ������ ���������� ��� ��������. ����� ������� ������ ����: ϲ�, ��.
// ����������� ������� ����� ����:
// 1. �������� �������� � ������� ������;
// 2. �������� �������� � ����� ������;
// 3. �������� �������� � ������� ������;
// 4. �������� �������� � �������;
// 5. �������� �������� ������ ����������� ���;
// 6. �������� �������� � ���� � ���� �������� ������� � ������� (������� ��� ������� �������� �������� ���������, ��������, �����, ��������, �);
// 7. ³���������� �� ϲ� �� � - �;
// 8. ³���������� �� ϲ� �� � - �;
// 9. ³���������� �� ���� �� ���������;
// 10. ³���������� �� ���� �� ��������;
// 11. �������� �������� ��������.
// 12. ��������� ���������� ��� ��� ��������;
// 13. ��������� ���������� ��� ����������� ��������.

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <string>
#include <list>
#include "date.h"

using namespace std;
const char* lowerCase(const char* str);

//0 BLACK 1 BLUE 2 GREEN 3 CYAN 4 RED 5 MAGENTA
//6 BROWN 7 LIGHTGRAY 8 DARKGRAY 9 LIGHTBLUE 10 LIGHTGREEN 
//11 LIGHTCYAN 12 LIGHTRED 13 LIGHTMAGENTA 14 YELLOW 15 WHITE
#define BACKGROUND 0
#define FOREGROUND 7
#define ITEMSELECT 15
#define MENULEFT 20
#define MENUTOP 4

void gotorc(short c, short r) {
	HANDLE StdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD  coord = { c, r };
	SetConsoleCursorPosition(StdOut, coord);
}

void Color(unsigned short BackC, unsigned short ForgC) {
	HANDLE StdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	unsigned short c = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
	SetConsoleTextAttribute(StdOut, c);
}

void paintmenu(const char** s, int length, int a) {
	Color(BACKGROUND, FOREGROUND);
	system("cls");
	gotorc(MENULEFT, MENUTOP);
	cout << "......MENU......\n";
	for (size_t i = 0; i < length; i++) {
		gotorc(MENULEFT, MENUTOP + i + 1);
		cout << (i == a ? Color(BACKGROUND, ITEMSELECT), "=>" : "  ");
		cout << s[i] << endl;
		Color(BACKGROUND, FOREGROUND);
	}
}

int menu(const char** s, int sizem, int act = 0) {
	char c = 80;
	while (1) {
		if (c == 72 || c == 80) paintmenu(s, sizem, act);
		c = _getch();
		switch (c)
		{
		case 27: //Esc
			return -1;
		case 80: //down
			++act;
			if (act == sizem) act = 0;
			break;
		case 72://up
			if (act == 0) act = sizem;
			--act;
			break;
		case 13: //Enter
			return act;
		}
	}
}


class Student {
	string name_;
	Date date_;
public:
	Student* next;
	Student(string name, Date date) :name_(name), date_(date), next(0) {};
	string getName() const { return name_; }
	Date getDate() const { return date_; }
	void setName(string name) { name_ = name; }
	void setDate(const char* date) { date_ = date; }
	friend ostream& operator<<(ostream& os, const Student& Obj);
};

ostream& operator<<(ostream& os, const Student& Obj) {
	os << Obj.name_ << "\t " << Obj.date_ << endl;
	return os;
}

Student& MakeStudent() {
	string name, date;
	do {
		cout << "������ ϲ�: "; getline(cin, name);
	} while (!name[0]);
	cout << "������ ���� ���������� � ������ ��.��.����: "; cin >> date;
	cin.clear(); cin.ignore(cin.rdbuf()->in_avail());
	return *new Student(name, date.c_str());
}


int main(void) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Color(BACKGROUND, FOREGROUND);

	list<Student> St;
	St.emplace_back("��������� ������� ��������", "04.02.1983");
	St.emplace_back("���������� ����� ����������", "06.08.1991");
	St.emplace_back("������� ��������� ���������", "09.04.1994");
	St.emplace_back("���������� ������", "09.03.1990");
	St.emplace_back("������� ������", "04.09.1989");
	St.emplace_back("��������䳺�� ����� ��������", "26.08.1978");
	St.emplace_back("�������� ��������� ��������", "07.10.1987");
	St.emplace_back("��������� ������� ����������", "09.04.1990");
	St.emplace_back("�������� �������� �������", "14.04.1984");
	St.emplace_back("���������� ������ ���������", "21.01.1993");
	St.emplace_back("������� ��������� ���������", "09.04.1994");
	
	const char* s[]{
	 "�������� �������� � ������� ������",
	 "�������� �������� � ����� ������",
	 "�������� �������� � ������� ������",
	 "�������� �������� � �������",
	 "�������� �������� ������ ����������� ���",
	 "�������� �������� � ���� � ���� �������� ������� � �������",
	 "³���������� �� ϲ� �� � - �",
	 "³���������� �� ϲ� �� � - �",
	 "³���������� �� ���� �� ���������",
	 "³���������� �� ���� �� ��������",
	 "�������� �������� ��������",
	 "��������� ���������� ��� ��� ��������",
	 "��������� ���������� ��� ����������� ��������" };
	int sizem = sizeof(s) / 4;
	int pm = 0;

	while (1) {
		pm = menu(s, sizem, pm);
		system("cls");
		if (pm < 0) break;
		if (pm == 0) {
			cout << sizeof(s);
			//St.push_front(MakeStudent());
		};
		if (pm == 1) {
			St.push_back(MakeStudent());			
		}
		if (pm == 2) {
			Student& tmp = MakeStudent();
			int p;
			cout << "������ �������, � ��� ����� �������� ��������: ";
			cin >> p; cin.clear(); cin.ignore(cin.rdbuf()->in_avail());
			if (0 < p && p <= St.size() + 1) {
				auto it = St.begin();
				advance(it, p - 1);
				St.insert(it, tmp);
			}
		};
		if (pm == 3) {
			int p;
			cout << "������ ������� ��������, ����� ����� ��������: ";
			cin >> p; cin.clear(); cin.ignore(cin.rdbuf()->in_avail());
			if (0 < p && p <= St.size()) {
				auto it = St.begin();
				advance(it, p - 1);
				St.erase(it);
			}
		};
		if (pm == 4) {
			int p;
			do {
				cout << "������ ��, �������� ������ ����� ����� ��������: ";
			cin >> p; cin.clear(); cin.ignore(cin.rdbuf()->in_avail());
			} while (p < 1 || 150 <= p);
			Date d;
			St.remove_if([&p, &d](Student a) { return (d - a.getDate())/365 > p; });
		};
		if (pm == 5) {
			string name;
			cout << "������ ��������� �����: "; getline(cin, name);
			name = lowerCase(name.c_str());
			St.remove_if([&name](Student a) { return strstr(lowerCase(a.getName().c_str()), name.c_str()); });
		};
		if (pm == 6) {
			St.sort([](Student a, Student b) { return a.getName() < b.getName(); });
		};
		if (pm == 7) {
			St.sort([](Student a, Student b) { return a.getName() > b.getName(); });
		};
		if (pm == 8) {
			St.sort([](Student a, Student b) { return a.getDate() < b.getDate(); });
		};
		if (pm == 9) {
			St.sort([](Student a, Student b) { return a.getDate() > b.getDate(); });
		};
		if (pm == 10) {
			St.sort([](Student a, Student b) { return a.getName() < b.getName(); });
			St.unique([](Student a, Student b) {return a.getName() == b.getName() && a.getDate() == b.getDate(); });
		};
		if (pm == 11) {
			int count = 1;
			cout << "ID#" << " " << setw(35) << left << "ϲ�" << "\t ���� ���." << endl << endl;
			for (auto i : St)
				cout << setw(3) << right << count++ << " " << setw(35) << left << i << endl;
		};
		if (pm == 12) {
			int p;
			cout << "������ ����� ��������, ����� ����� ��������: ";
			cin >> p; cin.clear(); cin.ignore(cin.rdbuf()->in_avail());
			cout << endl;
			if (0 < p && p <= St.size()) {
				auto it = St.begin();
				advance(it, p - 1);
				cout << setw(3) << p << " " << *it << endl;
			}
			else
				cout << "ͳ���� �� ��������" << endl;
		}
		Color(BACKGROUND, 2);
		cout << "\ndone\n";
		(void)_getch();
	}

	return 0;
}

const char* lowerCase(const char* str) {
	if (!str) return str;
	int len = strlen(str);
	char* temp = new char[len + 1]{ 0 };
	while (*str) {
		(*str >= 65 && *str <= 90 || *str >= -64 && *str <= -33) ? *temp++ = *str + 32 : *temp++ = *str;
		str++;
	}
	return temp - len;
}