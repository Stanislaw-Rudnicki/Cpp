// Реализуйте программу, которая предоставляет функциональность по работе с файлами.
// Приложение получает у пользователя путь к файлу, после чего программа отображает интерфейс по анализу содержимого файла.
// Возможности интерфейса:
// - Поиск заданной строки (по итогам показывать статистику поиска строки по всему файлу);
// - Замена строки на новую строку (по итогам показать статистику по замене строки);
// - Отображение файла на экран;
// - Переворот содержимого файла.
// Используйте для работы с файлами потоки, а для работы со строками класс string.


#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <string>
#include <list>

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


int FindStr(string fn, string str) {
	ifstream file;
	file.open(fn, ios::in);
	if (!file.is_open()) {
		cout << "Error read file\n";
		return -1;
	}
	string line;
	size_t count = 0;
	while (getline(file, line)) {
		size_t pos = line.find(str, 0);
		while (pos != string::npos) {
			pos = line.find(str, pos + 1);
			count++;
		}
	}
	file.close();
	return count;
}

int ReplaceStr(string fn, string find, string replace) {
	ifstream file;
	file.open(fn, ios::in);
	if (!file.is_open()) {
		cout << "Error read file\n";
		return -1;
	}
	list<string> list;
	string line;
	int count = 0;
	while (getline(file, line)) {
		size_t pos = 0;
		while (((pos = line.find(find, pos)) != string::npos) && (pos < line.length())) {
			line.replace(pos, find.length(), replace);
			pos += replace.length();
			count++;
		}
		list.push_back(line);
	}
	file.close();

	ofstream ofs(fn);
	for (auto i : list)
		ofs << i << '\n';
	ofs.close();
	return count;
}

void ShowFile(string fn) {
	ifstream file;
	file.open(fn, ios::in);
	if (!file.is_open()) {
		cout << "Error read file\n";
		return;
	}
	cout << file.rdbuf();
	file.close();
}

void ReverseFile(string fn) {
	ifstream file(fn);
	if (!file.is_open()) {
		cout << "Error read file\n";
		return;
	}
	list<char> list;
	char t;
	while (file.get(t))
		list.push_front(t);
	file.close();

	ofstream ofs(fn);
	for (auto i : list)
		ofs << i;
	ofs.close();
	
	/*int size;
	size = file.tellg();
	char* buf = new char[size];
	file.seekg(0, ios::beg);
	file.read(buf, size);
	file.close();*/
	//// get pointer to associated buffer object
	//filebuf* pbuf = file.rdbuf();

	//// get file size using buffer's members
	//size_t size = pbuf->pubseekoff(0, file.end, file.in);
	//pbuf->pubseekpos(0, file.in);

	//// allocate memory to contain file data
	//char* buffer = new char[size];

	//// get file data
	//pbuf->sgetn(buffer, size);

	/*ofstream ofs(fn, ios::binary);
	for (int i = --size; i >= 0; --i)
		ofs << buf[i];
	delete[] buf;
	ofs.close();*/
}


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Color(BACKGROUND, FOREGROUND);

	const char* s[]{
	 "Указать имя файла",
	 "Поиск заданной строки",
	 "Замена строки на новую строку",
	 "Отображение файла на экран",
	 "Переворот содержимого файла" };
	int sizem = sizeof(s) / 4;
	int pm = 0;
	string fn;

	while (1) {
		pm = menu(s, sizem, pm);
		system("cls");
		if (pm < 0) break;
		if (pm == 0) {
			cout << "Введите имя файла, либо оставьте пустым,\nчтобы загрузить файл по умолчанию (File.txt): "; getline(cin, fn);
			if (!fn[0]) fn = "File.txt";
		};
		if (pm == 1) {
			if (!fn[0]) cout << "Сначала укажите имя файла\n";
			else {
				string find;
				cout << "Введите поисковый запрос: "; getline(cin, find);
				int res = FindStr(fn, find);
				if (res != -1)
					cout << "\nИскомая строка встречается в файле " << res << " раз" << endl;
			}
		}
		if (pm == 2) {
			if(!fn[0]) cout << "Сначала укажите имя файла\n";
			else {
				string find, replace;
				cout << "Что искать: "; getline(cin, find);
				cout << "Чем заменить: "; getline(cin, replace);
				int res = ReplaceStr(fn, find, replace);
				if (res != -1)
					cout << "\nЗамена выполнена " << res << " раз" << endl;
			}
		};
		if (pm == 3) {
			if (!fn[0]) cout << "Сначала укажите имя файла\n";
			else {
				ShowFile(fn);
			}
		};
		if (pm == 4) {
			if (!fn[0]) cout << "Сначала укажите имя файла\n";
			else {
				ReverseFile(fn);
				cout << "Содержимое файла перевернуто!\n";
			}
		}
		Color(BACKGROUND, 2);
		cout << "\ndone\n";
		(void)_getch();
	}

	return 0;
}