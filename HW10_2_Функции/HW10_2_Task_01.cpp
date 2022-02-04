// Написать функцию, которая принимает два параметра:
// основание степени и показатель степени,
// и вычисляет степень числа на основе полученных данных.

#include <iostream>
#include <windows.h>
using namespace std;

double power(double chislo, int step)
{
	int i = 1;
	double res = chislo;
	if (step < 0) {
		step = -step;
		do {
			res *= chislo;
			i++;
		} while (i != step);
		double z = res;
		res = 1;
		res /= z;
		return res;
	}
	else if (step > 1) {
		do {
			res *= chislo;
			i++;
		} while (i != step);
		return res;
	}
	if (step == 1) return res;
	if (step == 0) return 1; 
	return res;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
    
	int p;
    double n;
        
    cout << "Введите число (double): " << char(03);
    cin >> n;
    cout << "Введите степень (int): ";
    cin >> p; 
				
	cout << endl << n << " ^ " << p << " = " << power(n, p) << endl;
    
    return 0;
}
