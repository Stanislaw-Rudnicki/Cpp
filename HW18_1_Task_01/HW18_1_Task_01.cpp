// ������������ ��������� �����������. �������� ��������� ������ (��������, �����, ������������, ����).
// �������� ������ �� 10 ����. ���������� ��� ���� ��������� �����������:
// ������������� �����
// ������ ���� ����
// ����� ���� �� ������
// ����� ����� �� ��������
// ���������� ������� �� �������� ����
// ���������� ������� �� ������
// ���������� ������� �� ������������

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>

using namespace std;

char* Lowercase(char* str);

//0 BLACK 1 BLUE 2 GREEN 3 CYAN 4 RED 5 MAGENTA
//6 BROWN 7 LIGHTGRAY 8 DARKGRAY 9 LIGHTBLUE 10 LIGHTGREEN 
//11 LIGHTCYAN 12 LIGHTRED 13 LIGHTMAGENTA 14 YELLOW 15 WHITE
#define BACKGROUND 0
#define FOREGROUND 7
#define ITEMSELECT 15
#define MENULEFT 20
#define MENUTOP 4

#define TH "Nr\t" << "��������\t\t\t" << "�����\t\t\t" << "������������\t" << "����"

void gotorc(short c, short r) {
	HANDLE StdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD  coord = { c, r };
	SetConsoleCursorPosition(StdOut, coord);
}
void Color(unsigned short BackC, unsigned short ForgC)
{
	HANDLE StdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	unsigned short c = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
	SetConsoleTextAttribute(StdOut, c);
}
void paintmenu(const char** s, int length, int a)
{
	Color(BACKGROUND, FOREGROUND);
	system("cls");
	gotorc(MENULEFT, MENUTOP);
	cout << "......MENU......\n";
	for (size_t i = 0; i < length; i++)
	{
		gotorc(MENULEFT, MENUTOP + i + 1);
		cout << (i == a ? Color(BACKGROUND, ITEMSELECT), "=>" : "  ");
		cout << s[i] << endl;
		Color(BACKGROUND, FOREGROUND);
	}
}
int menu(const char** s, int sizem, int act = 0)
{
	char c = 80;
	while (1)
	{
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
void Item1() {
	cout << "Item1";
}
void Item2() {
	cout << "Item2";
}
void Item3() {
	cout << "Item3";
}
void Item4() {
	cout << "Item4";
}
void Item5() {
	cout << "Item5";
}
void Item6() {
	cout << "Item6";
}
void Item7() {
	cout << "Item7";
}

struct Book {
	char title[100], author[100], publisher[100], genre[100];
};

void ShowBook(Book& d) {
	cout << d.title << "\t\t";
	cout << d.author << "\t\t";
	cout << d.publisher << "\t\t";
	cout << d.genre;
}

void ShowLibrary(Book* Gr, int n) {
	for (int i = 0; i < n; i++) {
		cout << i + 1 << "\t";
		ShowBook(Gr[i]);
		cout << endl;
	}
}

struct Library {
	char name[10];
	Book* arr;
	int count;
};

void AddBook(Library& gr, Book& st) {
	Book* temp = new Book[gr.count + 1];
	memcpy(temp, gr.arr, sizeof(Book) * gr.count);
	temp[gr.count] = st;
	delete[]gr.arr;
	gr.arr = temp;
	gr.count++;
}

void ShowLibrary(Library& gr) {
	cout << "����������: " << gr.name << endl << endl;
	cout << TH << endl;
	ShowLibrary(gr.arr, gr.count);
}

void FindLibrary(Library& gr, const char* key, int w) {
	cout << "����������: " << gr.name << endl << endl;
	cout << TH << endl;
	int j = 0;
	for (int i = 0; i < gr.count; i++) {
		if (strstr(Lowercase((gr.arr + i)->title + w * 100), key)) {
			cout << ++j << "\t";
			ShowBook(gr.arr[i]);
			cout << endl;
		}
	}
	if (!j) cout << "\n������ �� �������" << endl;
}

void SortBooks(Library& gr, int w) {
	bool f;
	int j = 0;
	do {
		f = 0;
		for (int i = 1; i < gr.count - j; i++)
			if (strcmp(gr.arr[i - 1].title + w * 100, gr.arr[i].title + w * 100) > 0) {
				Book temp = gr.arr[i - 1];
				gr.arr[i - 1] = gr.arr[i];
				gr.arr[i] = temp;
				f = 1;
			}
		j++;
	} while (f);
}

void EditBook(Library& gr, Book& st, int p) {
	if (p < 0 || gr.count < p) { return; }
	cout << endl; ShowBook(gr.arr[p]); cout << endl << endl;
	cout << "������� ����� �������� (Enter - ������� ��� ����): "; cin.ignore(); cin.getline(st.title, 100);
	cout << "������� ������ ������ (Enter - ������� ��� ����): "; cin.getline(st.author, 100);
	cout << "������� ����� ������������ (Enter - ������� ��� ����): ";  cin.getline(st.publisher, 100);
	cout << "������� ����� ���� (Enter - ������� ��� ����): ";  cin.getline(st.genre, 100);
	if (strlen(st.title)) strcpy_s(gr.arr[p].title, st.title);
	if (strlen(st.author)) strcpy_s(gr.arr[p].author, st.author);
	if (strlen(st.publisher)) strcpy_s(gr.arr[p].publisher, st.publisher);
	if (strlen(st.genre)) strcpy_s(gr.arr[p].genre, st.genre);
	cout << endl; ShowBook(gr.arr[p]); cout << endl;
}


int main(void) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Color(BACKGROUND, FOREGROUND);

	Book bk;
	Library lib_01{ "Lib 01" };

	bk = { "Git ��� ������������", "����� �����", "�����", "������������ ����������" };
	AddBook(lib_01, bk);
	bk = { "Vue.js � ��������", "������� ���", "�����", "������������ ����������" };
	AddBook(lib_01, bk);
	bk = { "�������� �� Python", "����� �������", "�����", "������������ ����������" };
	AddBook(lib_01, bk);
	bk = { "�������� ����. �1-�2", "������ ������", "������", "�������� ����������� ������" };
	AddBook(lib_01, bk);
	bk = { "50 ������ ����������", "������� �������", "�����", "������-����������" };
	AddBook(lib_01, bk);
	bk = { "������� ��� �������", "����� ���", "�������", "������-����������" };
	AddBook(lib_01, bk);
	bk = { "����� � �������!", "�������� ����", "�����", "���������� ����������" };
	AddBook(lib_01, bk);
	bk = { "����. ������������", "������ ������", "������", "���������� �����" };
	AddBook(lib_01, bk);
	bk = { "���������� �����������", "��������� �.", "�������", "���������� �����" };
	AddBook(lib_01, bk);
	bk = { "��������� ����. 50 ����", "�������� �.", "�����", "�������, �������� � �����" };
	AddBook(lib_01, bk);

	const char* s[]{
	 "�������� ��� �����",
	 "����� ���� �� ������",
	 "����� ����� �� ��������",
	 "���������� �� �������� ����",
	 "���������� �� ������",
	 "���������� �� ������������",
	 "������������� �����" };
	int sizem = sizeof(s) / 4;
	int pm = 0;
	while (1) {
		pm = menu(s, sizem, pm);
		system("cls");
		if (pm < 0) break;
		if (pm == 0) ShowLibrary(lib_01);
		if (pm == 1) {
			char* key = new char[101]{ 0 };
			cout << "������� ��������� ������: "; cin.getline(key, 100);
			FindLibrary(lib_01, Lowercase(key), 1);
			delete[]key;
		};
		if (pm == 2) {
			char* key = new char[101]{ 0 };
			cout << "������� ��������� ������: "; cin.getline(key, 100);
			FindLibrary(lib_01, Lowercase(key), 0);
			delete[]key;
		};
		if (pm == 3) {
			SortBooks(lib_01, 0);
			ShowLibrary(lib_01);
		};
		if (pm == 4) {
			SortBooks(lib_01, 1);
			ShowLibrary(lib_01);
		};
		if (pm == 5) {
			SortBooks(lib_01, 2);
			ShowLibrary(lib_01);
		};
		if (pm == 6){
			int p;
			cout << "������� ����� ����� ��� �������������� (1 - " << lib_01.count << "): "; cin >> p;
			if (0 < p && p <= lib_01.count)
				EditBook(lib_01, bk, p - 1);
			else
				cout << "\n����� � ������� " << p << " �� ����������" << endl;
		}
		Color(BACKGROUND, 2);
		cout << "\ndone\n";
		(void)_getch();
	}

	return 0;
}

char* Lowercase(char* str) {
	if (!str) return str;
	int len = strlen(str);
	char* temp = new char[len + 1]{ 0 };
	while (*str) {
		(*str >= 65 && *str <= 90 || *str >= -64 && *str <= -33) ? *temp++ = *str + 32 : *temp++ = *str;
		str++;
	}
	return temp - len;
}
