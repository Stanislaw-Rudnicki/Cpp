// Напишіть інформаційну систему "Співробітники" (ПІБ, Дата народження, Стать, Посада) з наступними вимогами:
// - динамічна зміна розмірів масиву для зберігання інформації;
// - інформація про дати зберігається в бітових полях;
// - організуйте введення даних;
// - організуйте виведення даних у таблиці через псевдо графіку;
// - додавання, зміна та видалення інформації про співробітників;
// - пошук співробітника на прізвище;
// - вивід інформації про всіх співробітників, зазначеного віку;
// - вивід інформації про всіх співробітників, прізвище яких починається на зазначену букву;
// - вивід іменинників вибраного місяця;
// - виведення всіх співробітників по вибраній статті (чоловіча, жіноча);
// - виведення всіх співробітників - пенсіонерів чоловічого (понад 60 років) і жіночого (понад 55 років) статі.


#include <iostream>
#include <conio.h>
#include <windows.h>
#include <stdio.h>
#include <cstdlib>

using namespace std;

char* Lowercase(char* str);
bool Is_leap(int year);
int DateDiff(int day, int day1, int month, int month1, int year, int year1);


//0 BLACK 1 BLUE 2 GREEN 3 CYAN 4 RED 5 MAGENTA
//6 BROWN 7 LIGHTGRAY 8 DARKGRAY 9 LIGHTBLUE 10 LIGHTGREEN 
//11 LIGHTCYAN 12 LIGHTRED 13 LIGHTMAGENTA 14 YELLOW 15 WHITE
#define BACKGROUND 0
#define FOREGROUND 7
#define ITEMSELECT 15
#define MENULEFT 20
#define MENUTOP 4

#define TH cout << "Співробітники " << gr.name << ":" << endl << endl; \
SetConsoleOutputCP(866); \
printf("%c", 213); \
for (int i = 0; i < 4; ++i) printf("%c", 205); 	printf("%c", 209); \
for (int i = 0; i < 55; ++i) printf("%c", 205); printf("%c", 209); \
for (int i = 0; i < 12; ++i) printf("%c", 205); printf("%c", 209); \
for (int i = 0; i < 7; ++i) printf("%c", 205); printf("%c", 209); \
for (int i = 0; i < 22; ++i) printf("%c", 205); printf("%c\n", 184); \
printf("%c", 179); \
SetConsoleOutputCP(1251); cout << " НП "; SetConsoleOutputCP(866); printf("%c", 179); \
SetConsoleOutputCP(1251); printf(" %-53s ", "ПІБ"); SetConsoleOutputCP(866); printf("%c", 179); \
SetConsoleOutputCP(1251); printf(" %-10s ", "Дата нар."); SetConsoleOutputCP(866); printf("%c", 179); \
SetConsoleOutputCP(1251); printf(" %s ", "Стать"); SetConsoleOutputCP(866); printf("%c", 179); \
SetConsoleOutputCP(1251); printf(" %-20s ", "Посада"); SetConsoleOutputCP(866); printf("%c\n", 179); \
printf("%c", 198); \
for (int i = 0; i < 4; ++i) printf("%c", 205); 	printf("%c", 216); \
for (int i = 0; i < 55; ++i) printf("%c", 205); printf("%c", 216); \
for (int i = 0; i < 12; ++i) printf("%c", 205); printf("%c", 216); \
for (int i = 0; i < 7; ++i) printf("%c", 205); printf("%c", 216); \
for (int i = 0; i < 22; ++i) printf("%c", 205); printf("%c\n", 181); \
SetConsoleOutputCP(1251);

#define TF SetConsoleOutputCP(866); \
printf("%c", 192); \
for (int i = 0; i < 4; ++i) printf("%c", 196); 	printf("%c", 193); \
for (int i = 0; i < 55; ++i) printf("%c", 196); printf("%c", 193); \
for (int i = 0; i < 12; ++i) printf("%c", 196); printf("%c", 193); \
for (int i = 0; i < 7; ++i) printf("%c", 196); printf("%c", 193); \
for (int i = 0; i < 22; ++i) printf("%c", 196); printf("%c", 217); \
SetConsoleOutputCP(1251);


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
void Item8() {
	cout << "Item8";
}
void Item9() {
	cout << "Item9";
}

struct Worker {
	char fname[50], lname[50], mname[50], position[50];
	unsigned int d : 5;
	unsigned int m : 4;
	unsigned int y : 12;
	unsigned int gender : 1;
};

struct Staff {
	char name[20];
	Worker* arr;
	int count;
};

void ShowWorker(Worker& d) {
	printf(" %-23s%-15s%-15s ", d.fname, d.lname, d.mname);
	SetConsoleOutputCP(866); cout << char(179); SetConsoleOutputCP(1251);
	printf(" %02d.%02d.%4d ", d.d, d.m, d.y);
	SetConsoleOutputCP(866); cout << char(179); SetConsoleOutputCP(1251);
	printf("   %s   ", d.gender ? "Ч" : "Ж");
	SetConsoleOutputCP(866); cout << char(179); SetConsoleOutputCP(1251);
	printf(" %-20s ", d.position);
}

void SetWorker(Worker& d) {
	int buf;
	char g;
	SYSTEMTIME st;
	GetSystemTime(&st);
	do {
		cout << "Введіть прізвище: "; cin.getline(d.fname, 50);
	} while (!*d.fname);
	do {
	cout << "Введіть ім'я: "; cin.getline(d.lname, 50);
	} while (!*d.lname);
	do {
	cout << "Введіть по батькові: "; cin.getline(d.mname, 50);
	} while (!*d.mname);
	do {
		cout << "Введіть дату народження. День: ";
		cin >> buf;	cin.clear(); cin.ignore(cin.rdbuf()->in_avail());
	} while (buf < 1 || 31 < buf);
	d.d = buf;
	do {
		cout << "Введіть дату народження. Місяць: ";
		cin >> buf; cin.clear(); cin.ignore(cin.rdbuf()->in_avail());
	} while (buf < 1 || 12 < buf);
	d.m = buf;
	do {
		cout << "Введіть дату народження. Рік: ";
		cin >> buf; cin.clear(); cin.ignore(cin.rdbuf()->in_avail());
	} while (buf < 1 || st.wYear < buf);
	d.y = buf;
	do {
		cout << "Введіть стать (Ч/Ж): "; cin >> g; cin.clear(); cin.ignore(cin.rdbuf()->in_avail());
	} while (g != 'ч' && g != 'Ч' && g != 'ж' && g != 'Ж');
	g == 'ч' || g == 'Ч' ? d.gender = 1 : d.gender = 0;
	do {
	cout << "Введіть посаду: "; cin.getline(d.position, 50);
	} while (!*d.position);
}

void ShowStaff(Worker* Gr, int n, int p = 0) {
	for (int i = p; i < n; i++) {
		SetConsoleOutputCP(866); printf("%c %2d %c", char(179), i + 1, char(179)); SetConsoleOutputCP(1251);
		ShowWorker(Gr[i]);
		SetConsoleOutputCP(866); printf("%c", char(179)); SetConsoleOutputCP(1251);
		cout << endl;
	}
}

void AddWorker(Staff& gr, Worker& st) {
	Worker* temp = new Worker[gr.count + 1];
	memcpy(temp, gr.arr, sizeof(Worker) * gr.count);
	temp[gr.count] = st;
	delete[]gr.arr;
	gr.arr = temp;
	gr.count++;
}

void ShowStaff(Staff& gr) {
	TH
	ShowStaff(gr.arr, gr.count);
	TF
}

typedef bool (*TypeFunc)(Staff&, const char*&, int);

bool ByFname(Staff& gr, const char*& key, int i) {
	return *key ? (strstr(Lowercase(gr.arr[i].fname), key)) : 0;
}

bool ByAge(Staff& gr, const char*& key, int i) {
	SYSTEMTIME st;
	GetSystemTime(&st);
	return (DateDiff(gr.arr[i].d, st.wDay, gr.arr[i].m, st.wMonth, gr.arr[i].y, st.wYear) / 365 == atoi(key));
}

bool ByChar(Staff& gr, const char*& key, int i) {
	return (*Lowercase(gr.arr[i].fname) == *key);
}

bool ByMonth(Staff& gr, const char*& key, int i) {
	return (gr.arr[i].m == atoi(key));
}

bool ByGender(Staff& gr, const char*& key, int i) {
	return (gr.arr[i].gender == atoi(key));
}

bool ByQuery(Staff& gr, const char*& key, int i) {
	SYSTEMTIME st;
	GetSystemTime(&st);
	int Age = DateDiff(gr.arr[i].d, st.wDay, gr.arr[i].m, st.wMonth, gr.arr[i].y, st.wYear) / 365;
	return (gr.arr[i].gender == 1 && Age >= 60 || gr.arr[i].gender == 0 && Age >= 55);
}

void FindStaff(Staff& gr, const char* key, TypeFunc FindFunc) {
	int j = 0;
	for (int i = 0; i < gr.count; i++) {
		if (FindFunc(gr, key, i)) {
			j = 1;
			break;
		}
	}
	if (j) {
		TH
			for (int i = 0; i < gr.count; i++) {
				if (FindFunc(gr, key, i)) {
					ShowStaff(gr.arr, i + 1, i);
				}
			}
		TF
	}
	else cout << "\nНічого не знайдено" << endl;
}

void EditWorker(Staff& gr, Worker& wrkr, int p) {
	if (p < 0 || gr.count < p) { return; }
	TH
		ShowStaff(gr.arr, p + 1, p);
	TF
		int buf;
		char g;
		SYSTEMTIME st;
		GetSystemTime(&st);
		cout << "\nЗмінити прізвище (Enter - залишити без змін): "; cin.getline(wrkr.fname, 50);
		if (*wrkr.fname) strcpy_s(gr.arr[p].fname, wrkr.fname);
		cout << "Змінити ім'я (Enter - залишити без змін): "; cin.getline(wrkr.lname, 50);
		if (*wrkr.lname) strcpy_s(gr.arr[p].lname, wrkr.lname);
		cout << "Змінити по батькові (Enter - залишити без змін): ";  cin.getline(wrkr.mname, 50);
		if (*wrkr.mname) strcpy_s(gr.arr[p].mname, wrkr.mname);
		do {
			cout << "Змінити дату народження. День (Enter - залишити без змін): ";
			cin.getline(wrkr.position, 3); cin.clear(); cin.ignore(cin.rdbuf()->in_avail());
			if (*wrkr.position) buf = atoi(wrkr.position); else break;
		} while (buf < 1 || 31 < buf);
		if (*wrkr.position) gr.arr[p].d = buf;
		do {
			cout << "Змінити дату народження. Місяць (Enter - залишити без змін): ";
			cin.getline(wrkr.position, 3); cin.clear(); cin.ignore(cin.rdbuf()->in_avail());
			if (*wrkr.position) buf = atoi(wrkr.position); else break;
		} while (buf < 1 || 12 < buf);
		if (*wrkr.position) gr.arr[p].m = buf;
		do {
			cout << "Змінити дату народження. Рік (Enter - залишити без змін): ";
			cin.getline(wrkr.position, 5); cin.clear(); cin.ignore(cin.rdbuf()->in_avail());
			if (*wrkr.position) buf = atoi(wrkr.position); else break;
		} while (buf < 1 || st.wYear < buf);
		if (*wrkr.position) gr.arr[p].y = buf;
		do {
			cout << "Змінити стать (Enter - залишити без змін): ";
			cin.getline(wrkr.position, 2); cin.clear(); cin.ignore(cin.rdbuf()->in_avail());
			if (*wrkr.position) g = *wrkr.position; else break;
		} while (g != 'ч' && g != 'Ч' && g != 'ж' && g != 'Ж');
		if (*wrkr.position) g == 'ч' || g == 'Ч' ? gr.arr[p].gender = 1 : gr.arr[p].gender = 0;
		cout << "Змінити посаду (Enter - залишити без змін): "; cin.getline(wrkr.position, 50);
		if (*wrkr.position) strcpy_s(gr.arr[p].position, wrkr.position);
		cout << endl;
	TH
		ShowStaff(gr.arr, p + 1, p);
	TF
}

void DeleteWorker(Staff& gr, Worker& st, int p) {
	if (p < 0 || p >= gr.count) return;
	Worker* temp = new Worker[gr.count + 1];
	if (p) memcpy(temp, gr.arr, sizeof(Worker) * p - 1);
	memcpy(temp + p, gr.arr + p + 1, sizeof(Worker) * (gr.count - p));
	delete[]gr.arr;
	gr.arr = temp;
	gr.count--;
}


int main(void) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Color(BACKGROUND, FOREGROUND);

	Worker wrkr;
	Staff company{ "Espresso-service" };
	
	wrkr = { "Ананченко", "Михайло", "Олегович", "Кур'єр", 17, 11, 1994, 1 };
	AddWorker(company, wrkr);
	wrkr = { "Лозинський", "Роман", "Михайлович", "Водій", 20, 1, 1994, 1 };
	AddWorker(company, wrkr);
	wrkr = { "Бакумов", "Олександр", "Сергійович", "Водій", 25, 4, 1989, 1 };
	AddWorker(company, wrkr);
	wrkr = { "Бобровська", "Соломія", "Анатоліївна", "Бухгалтер", 20, 12, 1989, 0 };
	AddWorker(company, wrkr);
	wrkr = { "Аллахвердієва", "Ірина", "Валеріївна", "Бухгалтер", 26, 8, 1978, 0 };
	AddWorker(company, wrkr);
	wrkr = { "Бабенко", "Микола", "Вікторович", "Комірник", 17, 9, 1980, 1 };
	AddWorker(company, wrkr);
	wrkr = { "Ковальов", "Олександр", "Іванович", "Директор", 7, 10, 1967, 1 };
	AddWorker(company, wrkr);
	wrkr = { "Макаренко", "Михайло", "Васильович", "Юрист", 9, 4, 1950, 1 };
	AddWorker(company, wrkr);
	wrkr = { "Богуцька", "Єлізавета", "Петрівна", "Менеджер з продажів", 14, 4, 1964, 0 };
	AddWorker(company, wrkr);
	wrkr = { "Третьякова", "Галина", "Миколаївна", "Менеджер з продажів", 21, 1, 1963, 0 };
	AddWorker(company, wrkr);

	const char* s[]{
	 "Показати всіх",
	 "Додати співробітника",
	 "Редагувати співробітника",
	 "Видалити співробітника",
	 "Пошук співробітника на прізвище",
	 "Пошук співробітників зазначеного віку",
	 "Пошук співробітників, прізвище яких починається на зазначену букву",
	 "Пошук іменинників вибраного місяця",
	 "Пошук всіх співробітників по вибраній статті (Ч/Ж)",
	 "Пошук всіх пенсіонерів (Ч >= 60 && Ж >= 55)" };
	int sizem = sizeof(s) / 4;
	int pm = 0;
	while (1) {
		pm = menu(s, sizem, pm);
		system("cls");
		if (pm < 0) break;
		if (pm == 0) ShowStaff(company);
		if (pm == 1) {
			SetWorker(wrkr);
			AddWorker(company, wrkr);
		};
		if (pm == 2) {
			int p;
			cout << "Введіть номер співробітника для редагування (1 - " << company.count << "): ";
			cin >> p; cin.clear(); cin.ignore(cin.rdbuf()->in_avail());
			if (0 < p && p <= company.count)
				EditWorker(company, wrkr, p - 1);
			else
				cout << "\nСівробітника з номером " << p << " не існує" << endl;
		};
		if (pm == 3) {
			int p;
			cout << "Введіть номер співробітника для видалення (1 - " << company.count << "): ";
			cin >> p; cin.clear(); cin.ignore(cin.rdbuf()->in_avail());
			if (0 < p && p <= company.count)
				DeleteWorker(company, wrkr, p - 1);
			else
				cout << "\nСівробітника з номером " << p << " не існує" << endl;
		};
		if (pm == 4) {
			char* key = new char[50]{ 0 };
			cout << "Введіть пошуковий запит: "; cin.getline(key, 50);
			FindStaff(company, Lowercase(key), ByFname);
			delete[]key;
		};
		if (pm == 5) {
			char* key = new char[4]{ 0 };
			cout << "Введіть пошуковий запит: "; cin.getline(key, 4); cin.clear(); cin.ignore(cin.rdbuf()->in_avail());
			FindStaff(company, key, ByAge);
			delete[]key;
		};
		if (pm == 6) {
			char* key = new char[2]{ 0 };
			cout << "Введіть пошуковий запит: "; cin.getline(key, 2); cin.clear(); cin.ignore(cin.rdbuf()->in_avail());
			FindStaff(company, Lowercase(key), ByChar);
			delete[]key;
		};
		if (pm == 7) {
			char* key = new char[3]{ 0 };
			cout << "Введіть пошуковий запит: "; cin.getline(key, 3); cin.clear(); cin.ignore(cin.rdbuf()->in_avail());
			FindStaff(company, key, ByMonth);
			delete[]key;
		};
		if (pm == 8) {
			char g;
			char* key = new char[2]{ 0 };
			do {
				cout << "Введіть пошуковий запит (Ч/Ж): "; cin >> g; cin.clear(); cin.ignore(cin.rdbuf()->in_avail());
			} while (g != 'ч' && g != 'Ч' && g != 'ж' && g != 'Ж');
			g == 'ч' || g == 'Ч' ? *key = '1' : *key = '0';
			FindStaff(company, key, ByGender);
			delete[]key;
		};
		if (pm == 9) {
			char* key = new char[2]{ 0 };
			FindStaff(company, key, ByQuery);
			delete[]key;
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

bool Is_leap(int year) {
	return ((year) % 4 == 0 && ((year) % 100 != 0 || (year) % 400 == 0));
}

int DateDiff(int day, int day1, int month, int month1, int year, int year1) {
	int days_before_month = 30 * month + (month + 5) * 4 / 7 - 35 + 2 * (month < 3);
	int y = year - 1;
	int date = day + days_before_month + (Is_leap(year) && month > 2) + y * 365 + y / 4 - y / 100 + y / 400;

	int days_before_month1 = 30 * month1 + (month1 + 5) * 4 / 7 - 35 + 2 * (month1 < 3);
	int y1 = year1 - 1;
	int date1 = day1 + days_before_month1 + (Is_leap(year1) && month1 > 2) + y1 * 365 + y1 / 4 - y1 / 100 + y1 / 400;
	return (date1 - date);
}
