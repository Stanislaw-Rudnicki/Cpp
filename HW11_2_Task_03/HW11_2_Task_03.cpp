// �������� ������� ��� �������� �����, ����������� � �������� ����, � ���������� �������������.

#include <iostream>
#include <windows.h>
using namespace std;

int bin2dec(long long int num)
{
	int i = 0, rest = 1;
	long long int num2 = num;
	while (num2 >= 1 && rest <= 1) { // ���������� ���������� ��������
		rest = num2 % 10;
		num2 /= 10;
		i++;
	}
	int digit = 1, sum = 0;
	num2 = num;
	if (rest > 1) //�������� �� ����������
		return -1;
	else {
		while (i) {
			rest = num2 % 10;
			num2 /= 10;
			sum += rest * digit;
			digit *= 2;
			i--;
		}
		return sum;
	}
}

int bin2dec_Horner(long long int num)
{
	int mas[19]{ 0 };
	int i = 0, rest = 1;
	while (num >= 1 && rest <= 1) { // ���������� ���������� ��������
		rest = mas[i] = num % 10;
		num /= 10;
		i++;
	}
	if (rest > 1) //�������� �� ����������
		return -1;
	else {
		int sum = 0;
		while (i) {
			i--;
			sum = sum * 2 + mas[i];
		}
		return sum;
	}
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	cout << "������� ����� � �������� ������� (����. 19 ����): ";
	long long int num;
	cin >> num;
	
	int dec = bin2dec(num);
	int dec2 = bin2dec_Horner(num);

	if (dec == -1 || dec2 == -1)
		cout << "\n��� �� �������� ������� ���� ����� ������� �������. ���������� ����. 19 ����." << endl;
	else	
		cout << "\n������������ �������:\t" << dec << "\n������� �������:\t" << dec2 << endl;

	return 0;
}
