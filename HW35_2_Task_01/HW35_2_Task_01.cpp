// Написати програму «Інформаційну систему про студентів».
// Система містить інформацію про студентів. Кожен студент містить поля: ПІБ, вік.
// Забезпечити систему таким меню:
// 1. Добавити студента в початок списку;
// 2. Добавити студента в кінець списку;
// 3. Добавити студента в позицію списку;
// 4. Видалити студента зі системи;
// 5. Видалити студентів старше зазначеного віку;
// 6. Видалити студентів у яких є набір введених символів у прізвищі (Введено «ко» Потрібно видалити студентів Устименко, Петренко, Мокон, Колотило, …);
// 7. Відсортувати за ПІБ від А - Я;
// 8. Відсортувати за ПІБ від Я - А;
// 9. Відсортувати за віком по зростанню;
// 10. Відсортувати за віком по спаданню;
// 11. Видалити дублікати студентів.
// 12. Виведення інформації про всіх студентів;
// 13. Виведення інформації про конкретного студента.

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
		cout << "Введіть ПІБ: "; getline(cin, name);
	} while (!name[0]);
	cout << "Введіть дату народження у форматі дд.мм.рррр: "; cin >> date;
	cin.clear(); cin.ignore(cin.rdbuf()->in_avail());
	return *new Student(name, date.c_str());
}


int main(void) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Color(BACKGROUND, FOREGROUND);

	list<Student> St;
	St.emplace_back("Ананченко Михайло Олегович", "04.02.1983");
	St.emplace_back("Лозинський Роман Михайлович", "06.08.1991");
	St.emplace_back("Бакумов Олександр Сергійович", "09.04.1994");
	St.emplace_back("Бобровська Соломія", "09.03.1990");
	St.emplace_back("Бабенко Микола", "04.09.1989");
	St.emplace_back("Аллахвердієва Ірина Валеріївна", "26.08.1978");
	St.emplace_back("Ковальов Олександр Іванович", "07.10.1987");
	St.emplace_back("Макаренко Михайло Васильович", "09.04.1990");
	St.emplace_back("Богуцька Єлізавета Петрівна", "14.04.1984");
	St.emplace_back("Третьякова Галина Миколаївна", "21.01.1993");
	St.emplace_back("Бакумов Олександр Сергійович", "09.04.1994");
	
	const char* s[]{
	 "Добавити студента в початок списку",
	 "Добавити студента в кінець списку",
	 "Добавити студента в позицію списку",
	 "Видалити студента зі системи",
	 "Видалити студентів старше зазначеного віку",
	 "Видалити студентів у яких є набір введених символів у прізвищі",
	 "Відсортувати за ПІБ від А - Я",
	 "Відсортувати за ПІБ від Я - А",
	 "Відсортувати за віком по зростанню",
	 "Відсортувати за віком по спаданню",
	 "Видалити дублікати студентів",
	 "Виведення інформації про всіх студентів",
	 "Виведення інформації про конкретного студента" };
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
			cout << "Введіть позицію, в яку треба добавити студента: ";
			cin >> p; cin.clear(); cin.ignore(cin.rdbuf()->in_avail());
			if (0 < p && p <= St.size() + 1) {
				auto it = St.begin();
				advance(it, p - 1);
				St.insert(it, tmp);
			}
		};
		if (pm == 3) {
			int p;
			cout << "Введіть позицію студента, якого треба видалити: ";
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
				cout << "Введіть вік, студентів старше якого треба видалити: ";
			cin >> p; cin.clear(); cin.ignore(cin.rdbuf()->in_avail());
			} while (p < 1 || 150 <= p);
			Date d;
			St.remove_if([&p, &d](Student a) { return (d - a.getDate())/365 > p; });
		};
		if (pm == 5) {
			string name;
			cout << "Введіть пошуковий запит: "; getline(cin, name);
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
			cout << "ID#" << " " << setw(35) << left << "ПІБ" << "\t Дата нар." << endl << endl;
			for (auto i : St)
				cout << setw(3) << right << count++ << " " << setw(35) << left << i << endl;
		};
		if (pm == 12) {
			int p;
			cout << "Введіть номер студента, якого треба показати: ";
			cin >> p; cin.clear(); cin.ignore(cin.rdbuf()->in_avail());
			cout << endl;
			if (0 < p && p <= St.size()) {
				auto it = St.begin();
				advance(it, p - 1);
				cout << setw(3) << p << " " << *it << endl;
			}
			else
				cout << "Нічого не знайдено" << endl;
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