// Студент містить наступні поля – прізвище, дата народження, група.
// Створити динамічну структуру хеш - таблицю. Вона повинна містити такий функціонал:
// добавити студента, видалити, вивести на екран всю таблицю, або одного студента;
// пошук студента по прізвищу, групі;
// реалізувати збереження та завантаження хеш таблиці.
// Зробити меню для роботи з хеш-таблицею.

#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <string>
#include "date.h"

using namespace std;

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
	string name_, group_;
	Date date_;
public:
	Student* next;
	Student(const char* name, const char* date, const char* group)
		:name_(name), date_(date), group_(group), next(0) {};
	string GetName() const { return name_; }
	string GetGroup() const { return group_; }
	size_t Hash();
	void WriteToFile(const char* fn);
	friend ostream& operator<<(ostream& os, const Student& Obj);
};

size_t Student::Hash() {
	if (!name_.empty()) {
		size_t hash = 1, len1 = name_.length();
		for (int i = 0; i < len1; i++)
			hash = 31 * hash + (unsigned char)name_[i];
		size_t len2 = group_.length();
		for (int i = 0; i < len2; i++)
			hash = 31 * hash + (unsigned char)group_[i];
		return hash % (len1 + len2);
	}
	return 0;
}

void Student::WriteToFile(const char* fn) {
	FILE* fs;
	fopen_s(&fs, fn, "ab");
	if (!fs) {
		cout << "Error write file\n"; return;
	}
	int len = name_.length();
	fwrite(&len, sizeof(len), 1, fs);
	fwrite(name_.c_str(), sizeof(char), len, fs);
	fwrite(date_, sizeof(char), 10, fs);
	len = group_.length();
	fwrite(&len, sizeof(len), 1, fs);
	fwrite(group_.c_str(), sizeof(char), len, fs);
	fclose(fs);
}

ostream& operator<<(ostream& os, const Student& Obj) {
	os << Obj.name_ << "\t " << Obj.date_<< "\t" << Obj.group_ << endl;
	return os;
}


class HashTable {
	Student** table_;
	size_t size_;
	size_t maxNameLen_;
public:
	HashTable(size_t n) :table_(new Student* [n] {0}), size_(n), maxNameLen_(0) {}
	~HashTable();
	void Clear();
	void Push(const char* name, const char* date, const char* group);
	void Show();
	void Show(int st);
	void Pop(int n);
	Student* Find(const char* name, const char* group);
	void SaveToFile(const char* fn);
	void LoadFromFile(const char* fn);

};

HashTable::~HashTable() {
	Clear();
	delete[] table_;
}

void HashTable::Clear() {
	for (size_t i = 0; i < size_; i++)
		if (table_[i]) {
			Student* temp = table_[i];
			Student* del = table_[i];
			while (temp) {
				del = temp;
				temp = temp->next;
				delete del;
			}
			table_[i] = 0;
		}
}

void HashTable::Push(const char* name, const char* date, const char* group) {
	Student* node = new Student(name, date, group);
	size_t h = node->Hash() % size_;
	if (!table_[h]) table_[h] = node;
	else {
		Student* temp = table_[h];
		while (temp->next)
			temp = temp->next;
		temp->next = node;
	}
	if (strlen(name) > maxNameLen_)
		maxNameLen_ = strlen(name);
}

void HashTable::Show() {
	int count = 1;
	cout << "ID#" << " Хеш " << setw(maxNameLen_) << left << "ПІБ" << "\t Дата нар." << "\tГрупа" << endl << endl;
	for (size_t i = 0; i < size_; i++)
		if (table_[i]) {
			Student* temp = table_[i];
			while (temp) {
				cout << setw(3) << right << count++ << setw(4) << i << " " << setw(maxNameLen_) << left << *temp << endl;
				temp = temp->next;
			}
		}
}

void HashTable::Show(int n) {
	int count = 1;
	cout << "ID#" << " Хеш " << setw(maxNameLen_) << left << "ПІБ" << "\t Дата нар." << "\tГрупа" << endl << endl;
	for (size_t i = 0; i < size_; i++)
		if (table_[i]) {
			Student* temp = table_[i];
			while (temp) {
				if (count == n) {
					cout << setw(3) << right << count << setw(4) << i << " " << setw(maxNameLen_) << left << *temp << endl;
					return;
				}
				count++;
				temp = temp->next;
			}
		}
}

void HashTable::Pop(int n) {
	int count = 1;
	for (size_t i = 0; i < size_; i++)
		if (table_[i]) {
			Student* temp = table_[i];
			Student* prev = table_[i];
			while (temp) {
				if (count == n) {
					if (prev->next == temp)
						prev->next = temp->next;
					else
						table_[i] = temp->next;
					delete temp;
					return;
				}
				count++;
				prev = temp;
				temp = temp->next;
			}
		}
}

Student* HashTable::Find(const char* name, const char* group) {
	Student node(name, "01.01.1970", group);
	size_t h = node.Hash() % size_;
	Student* temp = table_[h];
	while (temp) {
		if (temp->GetName() + temp->GetGroup() == node.GetName() + node.GetGroup()) return temp;
		temp = temp->next;
	}
	return 0;
}

void HashTable::SaveToFile(const char* fn) {
	FILE* fs = fopen(fn, "wb");
	if (!fs) {
		printf("Can't open, exiting...\n");
		exit(-1);
	}
	fwrite(&size_, sizeof(size_), 1, fs);
	fclose(fs);
	for (size_t i = 0; i < size_; i++)
		if (table_[i]) {
			Student* temp = table_[i];
			while (temp) {
				temp->WriteToFile(fn);
				temp = temp->next;
			}
		}
}

void HashTable::LoadFromFile(const char* fn) {
	FILE* fs;
	fopen_s(&fs, fn, "rb");
	if (!fs) {
		cout << "Error read file\n"; return;
	}
	Clear();
	delete[] table_;
	fread(&size_, sizeof(size_), 1, fs);
	table_ = new Student * [size_] {0};
	while (true) {
		int len = 0;
		if (!fread(&len, sizeof(len), 1, fs)) break;
		char* name = new char[len + 1] {0};
		fread(name, sizeof(char), len, fs);
		char* date = new char[11] {0};
		fread(date, sizeof(char), 10, fs);
		fread(&len, sizeof(len), 1, fs);
		char* group = new char[len + 1] {0};
		fread(group, sizeof(char), len, fs);
		Push(name, date, group);
		delete[] name, date, group;
	}
	fclose(fs);
}


int main(void) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Color(BACKGROUND, FOREGROUND);

	HashTable Table(10);
	//Table.Push("Ананченко Михайло Олегович", "04.02.1983", "Gr093306");
	//Table.Push("Лозинський Роман Михайлович", "06.08.1991", "Gr093306");
	//Table.Push("Бакумов Олександр Сергійович", "09.04.1994", "Gr093306");
	//Table.Push("Бобровська Соломія", "09.03.1990", "Gr08799");
	//Table.Push("Бабенко Микола", "04.09.1989", "Gr08799");
	//Table.Push("Аллахвердієва Ірина Валеріївна", "26.08.1978", "Gr08799");
	//Table.Push("Ковальов Олександр Іванович", "07.10.1987", "Gr08799");
	//Table.Push("Макаренко Михайло Васильович", "09.04.1990", "Gr08799");
	//Table.Push("Богуцька Єлізавета Петрівна", "14.04.1984", "Gr08799");
	//Table.Push("Третьякова Галина Миколаївна", "21.01.1993", "Gr08799");

	const char* s[]{
	 "Завантажити хеш-таблицю з файлу",
	 "Вивести на екран всю таблицю",
	 "Вивести на екран одного студента",
	 "Добавити студента",
	 "Видалити студента",
	 "Пошук студента по прізвищу, групі",
	 "Зберегти хеш-таблицю у файл" };
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
			Table.LoadFromFile(fn);
			delete[]fn;
		};
		if (pm == 1) {
			Table.Show();
		}
		if (pm == 2) {
			int p;
			cout << "Введіть номер студента, якого треба показати: ";
			cin >> p; cin.clear(); cin.ignore(cin.rdbuf()->in_avail());
			Table.Show(p);
		};
		if (pm == 3) {
			string name, date, group;
			do {
				cout << "Введіть ПІБ: "; getline(cin, name);
			} while (!name[0]);
			cout << "Введіть дату народження у форматі дд.мм.рррр: "; cin >> date;
			cin.clear(); cin.ignore(cin.rdbuf()->in_avail());
			cout << "Введіть групу: "; getline(cin, group);
			Table.Push(name.c_str(), date.c_str(), group.c_str());
		};
		if (pm == 4) {
			int p;
			cout << "Введіть номер студента, якого треба видалити: ";
			cin >> p; cin.clear(); cin.ignore(cin.rdbuf()->in_avail());
			Table.Pop(p);
		};
		if (pm == 5) {
			string name, group;
			cout << "Введіть пошуковий запит, ПІБ: "; getline(cin, name);
			cout << "Введіть пошуковий запит, Група: "; getline(cin, group);
			Student* find = Table.Find(name.c_str(), group.c_str());
			if (find)
			cout << "\n        " << *find << endl;
			else
			cout << "Нічого не знайдено" << endl;
		};
		if (pm == 6) {
			char fn[] = "File.bin";
			Table.SaveToFile(fn);
			cout << "Хеш-таблицю збережено у файл " << fn << endl;
		}
		Color(BACKGROUND, 2);
		cout << "\ndone\n";
		(void)_getch();
	}

	return 0;
}