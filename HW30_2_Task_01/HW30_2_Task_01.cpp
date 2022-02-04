// Студент містить наступні поля – прізвище, дата народження.
// 1. Створити динамічну структуру лінійний однозв’язний список.
// Список містить такий функціонал:
// добавити студента в кінець, в довільну позицію;
// видалити з кінця, з довільної позиції;
// вивести на екран весь список, або одного;
// пошук студента по прізвищу;
// сортування списку студентів;
// реалізувати збереження та завантаження списку.
// Зробити меню для роботи зі списком.

#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <string>
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


class Node {
	string name_;
	Date date_;
public:
	Node* next;
	Node(string name, Date date) :name_(name), date_(date), next(0) {};
	string getName() const { return name_; }
	Date getDate() const { return date_; }
	void setName(string name) { name_ = name; }
	void setDate(const char* date) { date_ = date; }
	friend ostream& operator<<(ostream& os, const Node& Obj);
};

ostream& operator<<(ostream& os, const Node& Obj) {
	os << Obj.name_ << "\t " << Obj.date_ << endl;
	return os;
}

class List {
	Node* begin, * end;
	size_t maxNameLen_;
public:
	List() { begin = end = 0; maxNameLen_ = 0; }
	~List() { Clear(); }
	// Конструктор копирования
	List(const List& other);
	// Конструктор перемещения
	List(List&& other) noexcept;
	// Оператор присваивания копированием
	List& operator=(const List& other);
	// Оператор присваивания перемещением
	List& operator=(List&& other);
	void Push(Node* n);
	void Push(string name, Date date);
	void Clear();
	bool Empty() { return !begin; };
	void PushHead(string name, Date date);
	void Insert(int pos, string name, Date date);
	Node* AddressPos(int pos);
	void DelHead();
	void DelTail();
	void Delete(int pos);
	void Sort();
	void SaveToFile(const char* fn);
	void LoadFromFile(const char* fn);
	Node* Find(string key, Node* start = 0);
	List FindAll(string key);
	friend ostream& operator<<(ostream& os, const List& list);
	friend void swap(List& l, List& r);
};

List::List(const List& other) {
	begin = end = 0;
	maxNameLen_ = 0;
	Node* temp = other.begin;
	while (temp) {
		Push(temp->getName(), temp->getDate());
		temp = temp->next;
	}
}

List::List(List&& other) noexcept {
	begin = other.begin;
	other.begin = nullptr;
	end = other.end;
	other.end = nullptr;
	maxNameLen_ = other.maxNameLen_;
}

List& List::operator=(const List& other) {
	List tmp(other);
	swap(*this, tmp);
	return *this;
}

List& List::operator=(List&& other) {
	swap(*this, other);
	return *this;
}

void List::Push(Node* n) {
	if (!end)
		begin = n;
	else
		end->next = n;
	end = n;
}

void List::Push(string name, Date date) {
	if (name.length() > maxNameLen_)
		maxNameLen_ = name.length();
	Push(new Node(name, date));
}

void List::Clear() {
	Node* temp = 0;
	while (begin) {
		temp = begin;
		begin = begin->next;
		delete temp;
	}
	end = 0;
	maxNameLen_ = 0;
}

void List::PushHead(string name, Date date) {
	if (name.length() > maxNameLen_)
		maxNameLen_ = name.length();
	Node* temp = new Node(name, date);
	temp->next = begin;
	begin = temp;
	if (!end)
		end = begin;
}

void List::Insert(int pos, string name, Date date) {
	if (pos < 0) return;
	if (pos == 0) { PushHead(name, date); return; }
	if (name.length() > maxNameLen_)
		maxNameLen_ = name.length();
	Node* prev = AddressPos(pos - 1);
	if (!prev) return;
	if (prev == end) {
		Push(name, date);
		return;
	}
	Node* node = new Node(name, date);
	node->next = prev->next;
	prev->next = node;
}

Node* List::AddressPos(int pos) {
	if (pos < 0) { return 0; }
	int p = 0;
	Node* temp = begin;
	while (temp) {
		if (!(pos--)) break;
		temp = temp->next;
	}
	return temp;
}

void List::DelHead() {
	if (begin) {
		Node* t = begin;
		begin = begin->next;
		delete t;
	}
	if (!begin) end = 0;
}

void List::DelTail() {
	if (begin == end) { DelHead(); return; }
	Node* temp = begin;
	while (temp->next != end)
		temp = temp->next;
	temp->next = 0;
	delete end;
	end = temp;
}

void List::Delete(int pos) {
	if (pos == 0) { DelHead(); return; }
	Node* del = AddressPos(pos - 1);
	if (!del) { return; }
	if (del == end) { return; }
	Node* temp = del->next;
	del->next = del->next->next;
	if (temp == end) end = del;
	delete temp;
}

Node* List::Find(string key, Node* start) {
	Node* node = start ? start : begin;
	while (node) {
		if (strstr(lowerCase(node->getName().c_str()), lowerCase(key.c_str()))) break;
		node = node->next;
	}
	return node;
}

List List::FindAll(string key) {
	List temp;
	Node* node = begin;
	while (node) {
		node = Find(key, node);
		if (node) {
			temp.Push(node->getName(), node->getDate());
			node = node->next;
		}
	}
	return temp;
}

void List::Sort() {
	Node* a, * b, * p, * h = 0;
	for (Node* i = begin; i != 0; ) {
		a = i;
		i = i->next;
		b = h;
		for (p = 0; (b != 0) && (a->getName() > b->getName()); ) {
			p = b;
			b = b->next;
		}
		if (p == 0) {
			a->next = h;
			h = a;
		}
		else {
			a->next = b;
			p->next = a;
		}
	}
	if (h != 0)
		begin = h;
}

void List::SaveToFile(const char* fn) {
	FILE* fs = fopen(fn, "wb");
	if (!fs) {
		printf("Can't open, exiting...\n");
		exit(-1);
	}
	Node* temp = begin;
	while (temp) {
		int len = temp->getName().length();
		fwrite(&len, sizeof(len), 1, fs);
		fwrite(temp->getName().c_str(), sizeof(char), len, fs);
		fwrite(temp->getDate(), sizeof(char), 10, fs);
		temp = temp->next;
	}
	fclose(fs);
}

void List::LoadFromFile(const char* fn) {
	FILE* fs;
	fopen_s(&fs, fn, "rb");
	if (!fs) {
		cout << "Error read file\n"; return;
	}
	Clear();
	while (true) {
		int len = 0;
		if (!fread(&len, sizeof(len), 1, fs)) break;
		char* name = new char[len + 1]{ 0 };
		fread(name, sizeof(char), len, fs);
		char* date = new char[11]{ 0 };
		fread(date, sizeof(char), 10, fs);
		Push(name, date);
		delete[] name, date;
	}
	fclose(fs);
}

ostream& operator<<(ostream& os, const List& list) {
	if (!list.begin)
		os << "list is empty";
	else {
		int count = 1;
		os << "ID#" << " " << setw(list.maxNameLen_) << left << "ПІБ" << "\t Дата нар." << endl << endl;
		Node* temp = list.begin;
		while (temp) {
			os << setw(3) << right << count++ << " " << setw(list.maxNameLen_) << left << *temp << endl;
			temp = temp->next;
		}
	}
	return os;
}

void swap(List& l, List& r) {
	using std::swap;
	swap(l.begin, r.begin);
	swap(l.end, r.end);
	swap(l.maxNameLen_, r.maxNameLen_);
}






int main(void) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Color(BACKGROUND, FOREGROUND);

	List St;
	/*St.Push("Ананченко Михайло Олегович", "04.02.1983");
	St.Push("Лозинський Роман Михайлович", "06.08.1991");
	St.Push("Бакумов Олександр Сергійович", "09.04.1994");
	St.Push("Бобровська Соломія", "09.03.1990");
	St.Push("Бабенко Микола", "04.09.1989");
	St.Push("Аллахвердієва Ірина Валеріївна", "26.08.1978");
	St.Push("Ковальов Олександр Іванович", "07.10.1987");
	St.Push("Макаренко Михайло Васильович", "09.04.1990");
	St.Push("Богуцька Єлізавета Петрівна", "14.04.1984");
	St.Push("Третьякова Галина Миколаївна", "21.01.1993");*/

	const char* s[]{
	 "Завантажити список з файлу",
	 "Вивести на екран весь список",
	 "Вивести на екран одного студента",
	 "Добавити студента в кінець",
	 "Добавити студента в довільну позицію",
	 "Видалити студента з кінця",
	 "Видалити студента з довільної позиції",
	 "Пошук студента по прізвищу",
	 "Сортування списку студентів",
	 "Зберегти список у файл" };
	int sizem = sizeof(s) / 4;
	int pm = 0;
	char fn[] = "File.bin";

	while (1) {
		pm = menu(s, sizem, pm);
		system("cls");
		if (pm < 0) break;
		if (pm == 0) {
			char* fn = new char[255]{ 0 };
			cout << "Введіть ім'я файлу, або залиште порожнім,\nщоб завантажити файл за замовчуванням (File.bin): "; cin.getline(fn, 255);
			if (!*fn) strcpy(fn, "File.bin");
			St.LoadFromFile(fn);
			delete[]fn;
		};
		if (pm == 1) {
			cout << St;
		}
		if (pm == 2) {
			int p;
			cout << "Введіть номер студента, якого треба показати: ";
			cin >> p; cin.clear(); cin.ignore(cin.rdbuf()->in_avail());
			cout << endl;
			Node* node = St.AddressPos(p - 1);
			if (node)
				cout << setw(3) << p << " " << *node << endl;
			else
				cout << "Нічого не знайдено" << endl;
		};
		if (pm == 3) {
			string name, date;
			do {
				cout << "Введіть ПІБ: "; getline(cin, name);
			} while (!name[0]);
			cout << "Введіть дату народження у форматі дд.мм.рррр: "; cin >> date;
			cin.clear(); cin.ignore(cin.rdbuf()->in_avail());
			St.Push(name, date.c_str());
		};
		if (pm == 4) {
			string name, date;
			do {
				cout << "Введіть ПІБ: "; getline(cin, name);
			} while (!name[0]);
			cout << "Введіть дату народження у форматі дд.мм.рррр: "; cin >> date;
			cin.clear(); cin.ignore(cin.rdbuf()->in_avail());
			int p;
			cout << "Введіть позицію, в яку треба добавити студента: ";
			cin >> p; cin.clear(); cin.ignore(cin.rdbuf()->in_avail());
			St.Insert(p - 1, name, date.c_str());
		};
		if (pm == 5) {
			St.DelTail();
			cout << "Студента з кінця видалено." << endl;
		};
		if (pm == 6) {
			int p;
			cout << "Введіть позицію студента, якого треба видалити: ";
			cin >> p; cin.clear(); cin.ignore(cin.rdbuf()->in_avail());
			St.Delete(p - 1);
		};
		if (pm == 7) {
			string name;
			cout << "Введіть пошуковий запит, ПІБ: "; getline(cin, name);
			cout << endl;
			List F = St.FindAll(name);
			if (!F.Empty())
				cout << F;
			else
				cout << "Нічого не знайдено" << endl;
		};
		if (pm == 8) {
			St.Sort();
			cout << St;
		};
		if (pm == 9) {
			char fn[] = "File.bin";
			St.SaveToFile(fn);
			cout << "Список збережено у файл " << fn << endl;
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