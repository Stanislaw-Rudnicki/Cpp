// Создать класс СПРАВОЧНИК со следующими полями:
// 1. Название фирмы;
// 2. Владелец;
// 3. Телефон;
// 4. Адрес;
// 5. Род деятельности.
// Реализовать следующие возможности:
// 1. Поиск по названию;
// 2. Поиск по владельцу;
// 3. Поиск по номеру телефона;
// 4. Поиск по роду деятельности;
// 5. Показ всех записей и добавление.
// Вся информация, должна сохранятся в файле,
// должна быть реализована возможность добавления новых данных.

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <iomanip>
#include <string>
#include <fstream>

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
	string name, owner, phone, address, activity;
public:
	Node* next;
	Node() {};
	Node(string name, string owner, string phone, string address, string activity)
		:name(name), owner(owner), phone(phone), address(address), activity(activity), next(0) {};
	string getName() const { return name; }
	void setName(string name) { name = name; }
	friend ostream& operator<<(ostream& os, const Node& Obj);
	friend class List;
};

ostream& operator<<(ostream& os, const Node& Obj) {
	os << Obj.name << "\n" << Obj.owner << "\n" << Obj.phone << "\n" << Obj.address << "\n" << Obj.activity << endl;
	return os;
}

class List {
	Node* begin, * end;
public:
	List() { begin = end = 0; }
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
	void Push(string name, string owner, string phone, string address, string activity);
	bool Empty() { return !begin; };
	void Clear();
	void SaveToFile(const char* fn);
	void LoadFromFile(const char* fn);
	Node* Find(string key, int field, Node* start = 0);
	List FindAll(string key, int field);
	friend ostream& operator<<(ostream& os, const List& list);
	friend void swap(List& l, List& r);
};

List::List(const List& other) {
	begin = end = 0;
	Node* temp = other.begin;
	while (temp) {
		Push(temp->name, temp->owner, temp->phone, temp->address, temp->activity);
		temp = temp->next;
	}
}

List::List(List&& other) noexcept {
	begin = other.begin;
	other.begin = nullptr;
	end = other.end;
	other.end = nullptr;
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

void List::Push(string name, string owner, string phone, string address, string activity) {
	Push(new Node(name, owner, phone, address, activity));
}

void List::Clear() {
	Node* temp = 0;
	while (begin) {
		temp = begin;
		begin = begin->next;
		delete temp;
	}
	end = 0;
}

Node* List::Find(string key, int field, Node* start) {
	Node* node = start ? start : begin;
	while (node) {
		string (Node::* str);
		switch (field) {
		case 1:
			str = &Node::name;
			break;
		case 2:
			str = &Node::owner;
			break;
		case 3:
			str = &Node::phone;
			break;
		case 4:
			str = &Node::activity;
			break;
		}
		if (strstr(lowerCase((node->*str).c_str()), lowerCase(key.c_str()))) break;
		node = node->next;
	}
	return node;
}

List List::FindAll(string key, int field) {
	List temp;
	Node* node = begin;
	while (node) {
		node = Find(key, field, node);
		if (node) {
			temp.Push(node->name, node->owner, node->phone, node->address, node->activity);
			node = node->next;
		}
	}
	return temp;
}

void List::SaveToFile(const char* fname) {
	ofstream fs;
	fs.open(fname, ios::out | ios::binary);
	if (!fs.is_open()) { cout << "Error write file\n"; return; }
	Node* temp = begin;
	while (temp) {
		for (string(Node::* str) : { &Node::name, &Node::owner, &Node::phone, &Node::address, &Node::activity }) {
			int len = (temp->*str).length();
			fs.write(reinterpret_cast<char*>(&len), sizeof(len));
			fs.write((temp->*str).c_str(), len);
		}
		temp = temp->next;
	}
	fs.close();
}

void List::LoadFromFile(const char* fname) {
	ifstream fcin;
	fcin.open(fname, ios::in);
	if (!fcin.is_open()) { cout << "Error read file\n"; return; }
	while (true) {
		Node* temp = new Node;
		for (string(Node::* str) : { &Node::name, &Node::owner, &Node::phone, &Node::address, &Node::activity }) {
			int len = 0;
			if (!fcin.read((char*)&len, sizeof(len))) {
				delete temp;
				fcin.close();
				return;
			}
			(temp->*str).resize(len);
			fcin.read(&(temp->*str)[0], len);
		}
		Push(temp);
	}
	fcin.close();
}

ostream& operator<<(ostream& os, const List& list) {
	if (!list.begin)
		os << "list is empty";
	else {
		int count = 1;
		Node* temp = list.begin;
		while (temp) {
			os << setw(3) << right << count++ << " " << *temp << endl;
			temp = temp->next;
		}
	}
	return os;
}

void swap(List& l, List& r) {
	using std::swap;
	swap(l.begin, r.begin);
	swap(l.end, r.end);
}


int main(void) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Color(BACKGROUND, FOREGROUND);

	List Directory;
	/*Directory.Push("Name 01", "Owner 01", "(067) 123-45-67", "Street A, 01", "Activity 01");
	Directory.Push("Name 02", "Owner 02", "(050) 654-46-79", "Street A, 157B", "Activity 02");
	Directory.Push("Name 03", "Owner 03", "(063) 798-54-77", "Street B, 54", "Activity 03");
	Directory.Push("Name 04", "Owner 04", "(068) 545-88-68", "Street A, 77/1", "Activity 04");
	Directory.Push("Name 05", "Owner 05", "(097) 755-66-88", "Street C, 254", "Activity 05");*/
	
	//Directory.LoadFromFile("File.bin");
	//cout << Directory << endl;

	//Directory.SaveToFile("File.bin");

	const char* s[]{
	 "Загрузить справочник из файла",
	 "Показать все записи",
	 "Добавить новую запись",
	 "Поиск по названию",
	 "Поиск по владельцу",
	 "Поиск по номеру телефона",
	 "Поиск по роду деятельности",
	 "Сохранить справочник в файл" };
	int sizem = sizeof(s) / 4;
	int pm = 0;
	char fn[] = "File.bin";

	while (1) {
		pm = menu(s, sizem, pm);
		system("cls");
		if (pm < 0) break;
		if (pm == 0) {
			char* fn = new char[255]{ 0 };
			cout << "Введите имя файла, либо оставьте пустым,\nчтобы загрузить файл по умолчанию (File.bin): "; cin.getline(fn, 255);
			if (!*fn) strcpy(fn, "File.bin");
			Directory.LoadFromFile(fn);
			delete[]fn;
		};
		if (pm == 1) {
			cout << Directory;
		}
		if (pm == 2) {
			string name, owner, phone, address, activity;
			do {
				cout << "Введите название: "; getline(cin, name);
			} while (!name[0]);
			cout << "Введите владельца: "; getline(cin, owner);
			cout << "Введите телефон: "; getline(cin, phone);
			cout << "Введите адрес: "; getline(cin, address);
			cout << "Введите род деятельности: "; getline(cin, activity);
			Directory.Push(name, owner, phone, address, activity);
		};
		if (pm == 3) {
			string name;
			cout << "Введите поисковый запрос: "; getline(cin, name);
			cout << endl;
			List F = Directory.FindAll(name, 1);
			if (!F.Empty())
				cout << F;
			else
				cout << "Ничего не найдено" << endl;
		};
		if (pm == 4) {
			string owner;
			cout << "Введите поисковый запрос: "; getline(cin, owner);
			cout << endl;
			List F = Directory.FindAll(owner, 2);
			if (!F.Empty())
				cout << F;
			else
				cout << "Ничего не найдено" << endl;
		};
		if (pm == 5) {
			string phone;
			cout << "Введите поисковый запрос: "; getline(cin, phone);
			cout << endl;
			List F = Directory.FindAll(phone, 3);
			if (!F.Empty())
				cout << F;
			else
				cout << "Ничего не найдено" << endl;
		};
		if (pm == 6) {
			string activity;
			cout << "Введите поисковый запрос: "; getline(cin, activity);
			cout << endl;
			List F = Directory.FindAll(activity, 4);
			if (!F.Empty())
				cout << F;
			else
				cout << "Ничего не найдено" << endl;
		};
		if (pm == 7) {
			char fn[] = "File.bin";
			Directory.SaveToFile(fn);
			cout << "Справочник сохранен в файл файл " << fn << endl;
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