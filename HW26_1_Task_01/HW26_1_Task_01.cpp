// Создайте приложение "Телефонная книга".
// Необходимо хранить данные об абоненте
// (ФИО, домашний телефон, рабочий телефон, мобильный телефон, дополнительная информация о контакте)
// внутри соответствующего класса. Наполните класс переменными - членами, функциями-членами, конструкторами, inline-функциями-членами,
// используйте инициализаторы, реализуйте деструктор.
// Обязательно необходимо выделять динамически память под ФИО.
// Предоставьте пользователю возможность добавлять новых абонентов,
// удалять абонентов, искать абонентов по ФИО, показывать всех абонентов,
// сохранять информацию в файл и загружать из файла.


#include <iostream>
#include <conio.h>
#include <windows.h>
#include "myString.h" // Используется класс из предыдущего домашнего задания. Файл во вложении.

using namespace std;
char* lowerCase(char* str);

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
	for (size_t i = 0; i < length; i++) 	{
		gotorc(MENULEFT, MENUTOP + i + 1);
		cout << (i == a ? Color(BACKGROUND, ITEMSELECT), "=>" : "  ");
		cout << s[i] << endl;
		Color(BACKGROUND, FOREGROUND);
	}
}
int menu(const char** s, int sizem, int act = 0) {
	char c = 80;
	while (1) 	{
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


class Contact {
	myString name;
	myString hTel;
	myString wTel;
	myString mTel;
	myString info;
public:

	void setContact(const char* n, const char* h, const char* w, const char* m, const char* i) {
		name = n;
		hTel = h;
		wTel = w;
		mTel = m;
		info = i;
	}
	void setContact() {
		do {
			cout << "Введите ФИО: "; cin >> name; //name.set();
		} while (!name[0]);
		cout << "Введите домашний телефон: "; hTel.set();
		cout << "Введите рабочий телефон: "; wTel.set();
		cout << "Введите мобильний телефон: "; mTel.set();
		cout << "Дополнительную информацию о контакте: "; info.set();
	}
	void showContact() {
		cout << name << "\tдом. " << hTel << "\tраб. " << wTel << "\tмоб. " << mTel << "\tинфо: " << info << endl;
	}
	bool findByFname(const char*& key) {
		return *key ? (strstr(lowerCase(name.get()), key)) : 0;
	}
	void unBind() {
		name.unBind();
		hTel.unBind();
		wTel.unBind();
		mTel.unBind();
		info.unBind();
	}
	void writeContact(const char* fn) {
		FILE* fs;
		fopen_s(&fs, fn, "ab");
		if (!fs) {
			cout << "Error write file\n"; return;
		}
		int len = name.showcap();
		fwrite(&len, sizeof(len), 1, fs);
		fwrite(name.get(), sizeof(char), len, fs);
		len = hTel.showcap();
		fwrite(&len, sizeof(len), 1, fs);
		fwrite(hTel.get(), sizeof(char), len, fs);
		len = wTel.showcap();
		fwrite(&len, sizeof(len), 1, fs);
		fwrite(wTel.get(), sizeof(char), len, fs);
		len = mTel.showcap();
		fwrite(&len, sizeof(len), 1, fs);
		fwrite(mTel.get(), sizeof(char), len, fs);
		len = info.showcap();
		fwrite(&len, sizeof(len), 1, fs);
		fwrite(info.get(), sizeof(char), len, fs);
		fclose(fs);
	}
};
class PhoneBook {
	int count;
	Contact* book;
public:
	PhoneBook() :PhoneBook(0) {}
	PhoneBook(size_t c) {
		count = c;
		if (c)
			book = new Contact[count];
		else
			book = 0;
	}
	~PhoneBook() {
		delete[]book;
	}
	int getCount() {
		return count;
	}
	void addContact(const Contact& contact) {
		Contact* temp = new Contact[count + 1];
		memcpy(temp, book, sizeof(book[0]) * count);
		temp[count] = contact;
		for (size_t i = 0; i < count; i++)
			book[i].unBind();
		delete[]book;
		book = temp;
		count++;
	}
	void addContact() {
		Contact* temp = new Contact[count + 1];
		memcpy(temp, book, sizeof(Contact) * count);
		temp[count].setContact();
		for (size_t i = 0; i < count; i++)
			book[i].unBind();
		delete[]book;
		book = temp;
		count++;
	}
	void showAll() {
		for (size_t i = 0; i < count; i++) {
			cout << i + 1 << " ";
			book[i].showContact();
		}
	}
	void findContact(const char* key) {
		int j = 0;
		for (int i = 0; i < count; i++) {
			if (book[i].findByFname(key)) {
				j = 1;
				break;
			}
		}
		if (j) {
			for (int i = 0; i < count; i++) {
				if (book[i].findByFname(key)) {
					cout << i + 1 << " ";
					book[i].showContact();
				}
			}
		}
		else cout << "\nНічого не знайдено" << endl;
	}
	void delContact(int n) {
		if (n <= 0 || n > count) return;
		Contact* temp = new Contact[count - 1];
		if (n) memcpy(temp, book, sizeof(Contact) * (n - 1));
		memcpy(temp + n - 1, book + n, sizeof(Contact) * (count - n));
		for (size_t i = 0; i < n - 1; i++)
			book[i].unBind();
		for (size_t i = n; i < count; i++)
			book[i].unBind();
		delete[]book;
		book = temp;
		count--;
	}
	void saveToFile(const char* fn) {
		FILE* fs = fopen(fn, "wb");
		if (!fs) {
			printf("Can't open, exiting...\n");
			exit(-1);
		}
		fwrite(&count, sizeof(count), 1, fs);
		fclose(fs);
		for (size_t i = 0; i < count; i++) {
			book[i].writeContact(fn);
		}
	}
	void loadFromFile(const char* fn) {
		FILE* fs;
		fopen_s(&fs, fn, "rb");
		if (!fs) {
			cout << "Error read file\n"; return;
		}
		fread(&count, sizeof(count), 1, fs);
		Contact* temp = new Contact[count];
		for (size_t i = 0; i < count; i++) {
			int len = 0;
			fread(&len, sizeof(len), 1, fs);
			char* name = new char[len] {0};
			fread(name, sizeof(char), len, fs);
			fread(&len, sizeof(len), 1, fs);
			char* hTel = new char[len] {0};
			fread(hTel, sizeof(char), len, fs);
			fread(&len, sizeof(len), 1, fs);
			char* wTel = new char[len] {0};
			fread(wTel, sizeof(char), len, fs);
			fread(&len, sizeof(len), 1, fs);
			char* mTel = new char[len] {0};
			fread(mTel, sizeof(char), len, fs);
			fread(&len, sizeof(len), 1, fs);
			char* info = new char[len] {0};
			fread(info, sizeof(char), len, fs);
			temp[i].setContact(name, hTel, wTel, mTel, info);
			delete[]info;
			delete[]mTel;
			delete[]wTel;
			delete[]hTel;
			delete[]name;
		}
		delete[]book;
		book = temp;
		fclose(fs);
	}
};

int main(void) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Color(BACKGROUND, FOREGROUND);

	//Contact c;
	PhoneBook tel;
	/*c.setContact("Ананченко Михайло Олегович", "04125356913", "0933065883", "", "Кур'єр");
	tel.addContact(c);
	c.setContact("Лозинський Роман Михайлович", "", "0638370791", "0638370791", "");
	tel.addContact(c);
	c.setContact("Бакумов Олександр Сергійович", "", "+380934432524", "", "Водій");
	tel.addContact(c);
	c.setContact("Бобровська Соломія", "", "0937032210", "0937032210", "Бухгалтер");
	tel.addContact(c);
	c.setContact("Бабенко Микола", "+380449443959", "0969762454", "", "Юрист");
	tel.addContact(c);*/

	const char* s[]{
	 "Загрузить телефонную книгу из файла",
	 "Показать всех абонентов",
	 "Добавить нового абонента",
	 "Удалить абонента",
	 "Искать абонентов по ФИО",
	 "Сохранить телефонную книгу в файл" };
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
			tel.loadFromFile(fn);
			delete[]fn;
		};
		if (pm == 1) {
			tel.showAll();
		}
		if (pm == 2) {
			tel.addContact();
		};
		if (pm == 3) {
			int p;
			cout << "Введите порядковый номер абонента для удаления (1 - " << tel.getCount() << "): ";
			cin >> p; cin.clear(); cin.ignore(cin.rdbuf()->in_avail());
			if (0 < p && p <= tel.getCount())
				tel.delContact(p);
			else
				cout << "\nАбонента под номером " << p << " не существует" << endl;
		};
		if (pm == 4) {
			char* key = new char[50]{ 0 };
			cout << "Введите поисковый запрос: "; cin.getline(key, 50);
			tel.findContact(lowerCase(key));
			delete[]key;
		};
		if (pm == 5) {
			char fn[] = "File.bin";
			tel.saveToFile(fn);
			cout << "Телефонная книга сохранена в файл " << fn << endl;
		}
		Color(BACKGROUND, 2);
		cout << "\ndone\n";
		(void)_getch();
	}
	return 0;
}

char* lowerCase(char* str) {
	if (!str) return str;
	int len = strlen(str);
	char* temp = new char[len + 1]{ 0 };
	while (*str) {
		(*str >= 65 && *str <= 90 || *str >= -64 && *str <= -33) ? *temp++ = *str + 32 : *temp++ = *str;
		str++;
	}
	return temp - len;
}