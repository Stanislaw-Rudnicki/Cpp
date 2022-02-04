// Создайте иерархию классов по работе с файлами.
// Базовый класс умеет открывать файл и отображать его содержимое в консоль,
// первый класс потомка открывает файл и отображает содержимое
// в виде ASCII-кодов символов, расположенных в файле,
// второй класс потомка открывает файл и показывает его содержимое в двоичном виде и т. д.
// Для отображения содержимого файла в базовом классе определена виртуальная функция
// void Display(const char* path);
// path — путь к файлу.
// Потомки создают свою реализацию виртуальной функции.


#include <iostream>
#include <windows.h>
#include <fstream>
//#include <bitset>

using namespace std;

class ShowText {
public:
	virtual void Display(const char* path)  {
		ifstream file;
		file.open(path, ios::in);
		if (!file.is_open()) {
			cout << "Error read file\n";
			return;
		}
		cout << file.rdbuf();
		file.close();
	}
};


class ShowAscii : public ShowText {
public:
	virtual void Display(const char* path) {
		ifstream file;
		file.open(path, ios::in);
		if (!file.is_open()) {
			cout << "Error read file\n";
			return;
		}
		char t;
		while (file.get(t))
			if (t == '\n')
				cout << endl;
			else
				cout << static_cast<int>(t) << " ";
		file.close();
	}
};

class ShowBinnary : public ShowAscii {
public:
	virtual void Display(const char* path) {
		ifstream file;
		file.open(path, ios::in);
		if (!file.is_open()) {
			cout << "Error read file\n";
			return;
		}
		char t;
		while (file.get(t))
			if (t == '\n')
				cout << endl;
			else {
				//cout << bitset<8>(t) << " ";
				for (int i = 7; i >= 0; i--)
					cout << ((static_cast<int>(t)& static_cast<int>(pow(2, i))) > 0 ? "1" : "0");
				cout << " ";
			}
		file.close();
	}
};




int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	char fn[] = "File.txt";

	ShowText ST;
	ST.Display(fn);
	cout << endl;
	system("pause");
	
	ShowAscii SA;
	SA.Display(fn);
	cout << endl;
	system("pause");
	
	ShowBinnary SB;
	SB.Display(fn);
	cout << endl;

	return 0;
}