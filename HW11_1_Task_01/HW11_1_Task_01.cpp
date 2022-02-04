// Ќаписать функцию, котора€ принимает две даты (т.е. функци€ принимает шесть параметров)
// и вычисл€ет разность в дн€х между этими датами.
// ƒл€ решени€ этой задачи необходимо также написать функцию,
// котора€ определ€ет, €вл€етс€ ли год високосным.

#include <iostream>
#include <windows.h>
using namespace std;

bool is_leap(int year)
{
	return ((year) % 4 == 0 && ((year) % 100 != 0 || (year) % 400 == 0));
}
int datediff(int day, int day1, int month, int month1, int year, int year1)
{
	int days_before_month = 30 * month + (month + 5) * 4 / 7 - 35 + 2 * (month < 3);
	int y = year - 1;
	int date = day + days_before_month + (is_leap(year) && month > 2) + y * 365 + y / 4 - y / 100 + y / 400;

	int days_before_month1 = 30 * month1 + (month1 + 5) * 4 / 7 - 35 + 2 * (month1 < 3);
	int y1 = year1 - 1;
	int date1 = day1 + days_before_month1 + (is_leap(year1) && month1 > 2) + y1 * 365 + y1 / 4 - y1 / 100 + y1 / 400;

	return (date1 - date);
}

int main() {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int day, day1, month, month1, year, year1, date, date1;
	cout << "¬ведите день первой даты: ";
	cin >> day;
	cout << "¬ведите мес€ц первой даты: ";
	cin >> month;
	cout << "¬ведите год первой даты: ";
	cin >> year;
	cout << "¬ведите день второй даты: ";
	cin >> day1;
	cout << "¬ведите мес€ц второй даты: ";
	cin >> month1;
	cout << "¬ведите год второй даты: ";
	cin >> year1;

	cout << "\n\t" << datediff(day, day1, month, month1, year, year1) << " дн≥в м≥ж цими двома датами" << endl;

	return 0;
}