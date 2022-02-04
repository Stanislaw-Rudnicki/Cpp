// �������� �������, ��������� �� ����� ���������� �� ��������� �����.

#include <iostream>
#include <windows.h>
using namespace std;

void showCard(int suit, int num)
{
	char charCard[13] = { '6','7','8','9','0','�','�','�','�' };

	cout << "\n���� �����:\n\t.--------.\n\t|";
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
	
	cout << "�������� �����:\n����� (1), ����� (2), ����� (3), ���� (4): ";
	cin >> suit;
	while (suit < 1 || suit > 4) {
		cout << "�� 1 �� 4, ����������: ";
		cin >> suit;
	};
	
	cout << "�������� �����:\n6 (6), 7 (7), 8 (8), 9 (9), 10 (10), ����� (11), ���� (12), ������ (13), ��� (14): ";
	cin >> num;
	while (num < 6 || num > 14) {
		cout << "�� 6 �� 14, ����������: ";
		cin >> num;
	};

	showCard(suit, num);

	return 0;
}