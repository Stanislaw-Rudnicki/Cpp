// Напишіть програму, яка знаходить найбільше число паліндром,
// яке утворюється шляхом множення двох простих п'ятизначних чисел.
// Програма має вивести на екран саме число паліндром та два співмножники.
// Просте число — це натуральне число, яке має рівно два різних натуральних дільники (лише 1 і саме число).
// Послідовність простих чисел починається так : 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, …
// Паліндром - рядок, що однаково читається в обох напрямках (зліва направо та справа наліво). Наприклад 11, 12321, А мене нема...

#include <iostream>
#include <ctime>
#include <omp.h>

using namespace std;

bool isSimple(int x) {
	for (int i = sqrt((double)x); i > 1; i--)
		if (x % i == 0)
			return false;
	return true;
}

long long NumReverse(long long x) {
	long long y = 0;
	while (x) {
		y = y * 10 + x % 10;
		x /= 10;
	}
	return y;
}

int* CreateMas(int n) {
	int* mas = new int[n];
	if (!mas) {
		cout << "Error memory" << endl;
		exit(-1);
	}
	return mas;
}

void DelMas(int* arr) {
	delete[]arr;
}

int NumDigits(long long x) {
	
	x = abs(x);
	return (x < 10 ? 1 :
		(x < 100 ? 2 :
		(x < 1000 ? 3 :
			(x < 10000 ? 4 :
			(x < 100000 ? 5 :
				(x < 1000000 ? 6 :
				(x < 10000000 ? 7 :
					(x < 100000000 ? 8 :
					(x < 1000000000 ? 9 :
						10)))))))));
}

int fiGetDigit(const long long n, const int k) {
	//Get K-th Digit from a Number (zero-based index)
	switch (k) {
	case 1:return n % 10;
	case 2:return n / 10 % 10;
	case 3:return n / 100 % 10;
	case 4:return n / 1000 % 10;
	case 5:return n / 10000 % 10;
	case 6:return n / 100000 % 10;
	case 7:return n / 1000000 % 10;
	case 8:return n / 10000000 % 10;
	case 9:return n / 100000000 % 10;
	case 10:return n / 1000000000 % 10;
	}
	return 0;
}

bool isPal(long long num) {
	int digits = NumDigits(num);
	for (int i = 1; i <= digits / 2; i++) {
		if (fiGetDigit(num, i) != fiGetDigit(num, digits + 1 - i))
			return false;
	}
	return true;
}


int main() {

	int a = 10000;
	int b = 99999;

	long long pal = 0, maxpal = 0;
	int pal_a = 0, pal_b = 0, count = 0;

	for (int i = a; i <= b; i++)
		if (isSimple(i))
			count++;

	int* mas = CreateMas(count);
	for (int j = 0, i = a; i <= b; i++)
		if (isSimple(i))
			mas[j++] = i;

	#pragma omp parallel for private(pal)
	for (int i = 0; i < count; i++)
		for (int j = 0; j < count; j++) {
			pal = (long long)mas[i] * mas[j];
			//if (pal == NumReverse(pal)) {
			if (isPal(pal)) {
				//cout << pal << " ";
				if (maxpal < pal) {
					maxpal = pal;
					pal_a = mas[i];
					pal_b = mas[j];
				}
			}
		}
	
	/*for (int i = a; i <= b; i++) {
		if (isSimple(i))
			for (int j = a; j <= b; j++) {
				if (isSimple(j)) {
					pal = (long long int)i * j;
					if (pal == NumReverse(pal)) {
						cout << pal << " ";
						if (maxpal < pal) {
							maxpal = pal;
							pal_a = i;
							pal_b = j;
						}
					}
				}
			}
	}*/

	DelMas(mas);

	cout << "\n" << maxpal << " = " << pal_a << " * " << pal_b << endl;
	cout << "\nruntime = " << clock() / 1000.0 << endl;
	return 0;
}
