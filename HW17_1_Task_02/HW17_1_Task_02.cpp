// 2. Реализовать структуру «Автомобиль» (длина, клиренс (высота посадки), объем двигателя,
// мощность двигателя, диаметр колес, цвет, тип коробки передач).
// Создайте функции для задания значений, отображения значений, поиска значений.

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>

using namespace std;

char* NumberToString(double number);
char* Lowercase(char* str);

//0 BLACK 1 BLUE 2 GREEN 3 CYAN 4 RED 5 MAGENTA
//6 BROWN 7 LIGHTGRAY 8 DARKGRAY 9 LIGHTBLUE 10 LIGHTGREEN 
//11 LIGHTCYAN 12 LIGHTRED 13 LIGHTMAGENTA 14 YELLOW 15 WHITE
#define BACKGROUND 0
#define FOREGROUND 7
#define ITEMSELECT 15
#define MENULEFT 20
#define MENUTOP 4

#define TH "Nr\t" << "Длина\t" << "Клиренс\t" << "Объем двигателя\t" << "Мощность\t" << "Диаметр колес\t" << "Цвет\t" << "Тип коробки"

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

struct Car {
	int width;
	int clearance;
	double displacement;
	int power;
	int wheel_size;
	char color[50];
	char transmission[50];
};

void ShowCar(Car& d) {
	cout << d.width << "\t";
	cout << d.clearance << "\t";
	cout << d.displacement << "\t\t";
	cout << d.power << "\t\t";
	cout << d.wheel_size << "\t\t";
	cout << d.color << "\t";
	cout << d.transmission;
}

void SetCar(Car& d) {
	cout << "Введите длину (мм): ";  cin >> d.width;
	cout << "Введите клиренс (мм): ";  cin >> d.clearance;
	cout << "Введите объем двигателя (л): ";  cin >> d.displacement;
	cout << "Введите мощность двигателя (л.с.): ";  cin >> d.power;
	cout << "Введите диаметр колес (дюйм): ";  cin >> d.wheel_size;
	cout << "Введите цвет: "; cin.ignore(); cin.getline(d.color, 50);
	cout << "Введите тип коробки передач: ";  cin.getline(d.transmission, 50);
}

void ShowGarage(Car* Gr, int n) {
	for (int i = 0; i < n; i++) {
		cout << i + 1 << "\t";
		ShowCar(Gr[i]);
		cout << endl;
	}
}

struct Garage {
	char name[10];
	Car* arr;
	int count;
};

void AddCar(Garage& gr, Car& st) {
	Car* temp = new Car[gr.count + 1];
	memcpy(temp, gr.arr, sizeof(Car) * gr.count);
	temp[gr.count] = st;
	delete[]gr.arr;
	gr.arr = temp;
	gr.count++;
}

void InsertCar(Garage& gr, Car& st, int p) {
	if (p < 0 || p > gr.count) { AddCar(gr, st); return; };
	if (p == gr.count) { AddCar(gr, st); return; }
	Car* temp = new Car[gr.count + 1];
	memcpy(temp, gr.arr, sizeof(Car) * p);
	memcpy(temp + p + 1, gr.arr + p, sizeof(Car) * (gr.count - p));
	temp[p] = st;
	delete[]gr.arr;
	gr.arr = temp;
	gr.count++;
}

void ShowGarage(Garage& gr) {
	cout << "Name: " << gr.name << endl << endl;
	cout << TH << endl;
	ShowGarage(gr.arr, gr.count);
}

void FindGarage(Garage& gr, const char* key) {
	cout << "Name: " << gr.name << endl << endl;
	cout << TH << endl;
	int j = 0;
	for (int i = 0; i < gr.count; i++) {
		if (strstr(NumberToString((gr.arr + i)->width), key) || strstr(NumberToString((gr.arr + i)->clearance), key) ||
			strstr(NumberToString((gr.arr + i)->displacement), key) || strstr(NumberToString((gr.arr + i)->power), key) ||
			strstr(NumberToString((gr.arr + i)->wheel_size), key) || strstr(Lowercase((gr.arr + i)->color), key) || strstr(Lowercase((gr.arr + i)->transmission), key)) {
			cout << ++j << "\t";
			ShowCar(gr.arr[i]);
			cout << endl;
		}
	}
	if (!j) cout << "\nНичего не найдено" << endl;
}

int main(void)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Color(BACKGROUND, FOREGROUND);

	Car cr;
	Garage gar_01{ "Gar 01" };
	
	cr = { 2800, 180, 1.4, 140, 16, "серый", "Автомат" };
	AddCar(gar_01, cr);
	cr = { 3110, 190, 1.8, 150, 16, "белый", "Механика" };
	AddCar(gar_01, cr);
	cr = { 2820, 170, 1.6, 120, 15, "черный", "Автомат" };
	AddCar(gar_01, cr);
	cr = { 3080, 200, 2.2, 170, 18, "зеленый", "Механика" };
	AddCar(gar_01, cr);
	cr = { 3530, 220, 3.5, 300, 22, "черный", "Механика" };
	AddCar(gar_01, cr);

	const char* s[]{
	 "Добавить авто",
	 "Показать все авто",
	 "Вставить авто",
	 "Искать авто" };
	int sizem = sizeof(s) / 4;
	int pm = 0;
	while (1) {
		pm = menu(s, sizem, pm);
		system("cls");
		if (pm < 0) break;
		if (pm == 0) {
			SetCar(cr);
			AddCar(gar_01, cr);
		};
		if (pm == 1) ShowGarage(gar_01);
		if (pm == 2) {
			int p;
			cout << "Введите позицию: "; cin >> p;
			SetCar(cr);
			InsertCar(gar_01, cr, p - 1);
		};
		if (pm == 3) {
			char* key = new char[51]{ 0 };
			cout << "Введите поисковый запрос: "; cin.getline(key, 50);
			FindGarage(gar_01, Lowercase(key));
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

char* NumberToString(double number)
{
	int ipart = (int)number;
	double fpart = number - (double)ipart;

	int i = 0;
	int num2 = ipart;
	do {
		num2 /= 10;
		i++;
	} while (num2 != 0);
	fpart = fpart * pow(10, 2);
	int i2 = i, j = 0;
	if (fpart) {
		int num3 = (int)fpart;
		do {
			num3 /= 10;
			i2++; j++;
		} while (num3 != 0);
	}

	char* temp = new char[i2 + 3]{ 0 };
	int offset = i2;
	if (number < 0) {
		*temp++ = 45;
		offset++;
	}
	for (i -= 1; i >= 0; i--, temp++)
		* temp = abs(ipart) / int(pow(10, i)) % 10 + '0';
	if (fpart) {
		*temp++ = '.';
		offset++;
		for (j -= 1; j >= 0; j--, temp++)
			* temp = (int)fpart / int(pow(10, j)) % 10 + '0';
	}
	return temp - offset;
}