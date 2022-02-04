// Написать функцию, выводящую на экран переданную ей игральную карту.

#include <iostream>
#include <windows.h>
using namespace std;

void showCard(int suit, int num)
{
	char charCard[13] = { '6','7','8','9','0','В','Д','К','Т' };

	cout << "\nВаша карта:\n\t.--------.\n\t|";
	if (num == 10) cout << "1";
	cout << charCard[num - 6];
	if (num != 10) cout << " ";
	cout << "      |" << endl;

	switch (suit) {
	case 1:
		cout << "\t|   _    |\n\t|  ( )   |\n\t| (_x_)  |\n\t|   Y    |" << endl;
		break;
	case 2:
		cout << "\t|   /\\   |\n\t|  /  \\  |\n\t|  \\  /  |\n\t|   \\/   |" << endl;
		break;
	case 3:
		cout << "\t|  _  _  |\n\t| ( \\/ ) |\n\t|  \\  /  |\n\t|   \\/   |" << endl;
		break;
	case 4:
		cout << "\t|   .    |\n\t|  / \\   |\n\t| (_,_)  |\n\t|   I    |" << endl;
		break;
	}

	cout << "\t|      ";
	if (num != 10) cout << " "; 
	if (num == 10) cout << "1";
	cout << charCard[num - 6] << "|\n\t'--------'" << endl;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int suit, num;
	
	cout << "Выберите масть:\nТрефы (1), Бубны (2), Червы (3), Пики (4): ";
	cin >> suit;
	while (suit < 1 || suit > 4) {
		cout << "От 1 до 4, пожалуйста: ";
		cin >> suit;
	};
	
	cout << "Выберите карту:\n6 (6), 7 (7), 8 (8), 9 (9), 10 (10), Валет (11), Дама (12), Король (13), Туз (14): ";
	cin >> num;
	while (num < 6 || num > 14) {
		cout << "От 6 до 14, пожалуйста: ";
		cin >> num;
	};

	showCard(suit, num);

	return 0;
}