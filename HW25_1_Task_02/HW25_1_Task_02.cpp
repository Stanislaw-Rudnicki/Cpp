// —оздайте класс Array (или используйте ранее созданный вами).
//  ласс Array Ц это класс динамического массива.
// –азмер массива может быть передан в качестве параметра или задан с помощью вызова функции-члена.
// -  ласс должен позвол€ть заполн€ть массив значени€ми,
// - отображать содержимое массива,
// - измен€ть размер массива,
// - сортировать массив,
// - определ€ть минимальное и максимальное значение.
//  ласс должен содержать набор конструкторов (конструктор копировани€ об€зателен), деструктор.


#include <iostream>
#include <stdio.h>
#include <ctime>
using namespace std;

class myArray {
	int* mas;
	size_t cap;
public:

	//  онструктор по умолчанию
	myArray() :myArray(1) {}

	myArray(size_t c) {
		cap = c;
		if (c) 
			mas = new int[cap] {0};
		else
			mas = 0;
	}
	//  онструктор копировани€
	myArray(const myArray& obj) {
		cap = obj.cap;
		mas = new int[cap];
		memcpy(mas, obj.mas, sizeof(int) * cap);
	}

	//  онструктор переноса
	myArray(myArray&& obj) {
		cap = obj.cap;
		mas = obj.mas;
		obj.mas = 0;
	}

	myArray operator= (const myArray& obj) {
		if (this != &obj) {
			delete[] mas;
			cap = obj.cap;
			mas = new int[obj.cap];
			memcpy(mas, obj.mas, sizeof(int) * cap);
		}
		return *this;
	}

	myArray operator= (myArray&& obj) {
		delete[] mas;
		cap = obj.cap;
		mas = obj.mas;
		obj.mas = 0;
		return *this;
	}

	myArray operator+ (const myArray& obj) {
		myArray temp(cap + obj.cap);
		memcpy(temp.mas, mas, sizeof(int) * cap);
		memcpy(temp.mas + cap, obj.mas, sizeof(int) * obj.cap);
		return temp;
	}

	int& operator [](int index) {
		if (index <= cap)
			return mas[index];
		else
			return mas[cap];
	}

	friend ostream& operator<< (ostream& out, const myArray& obj) {
		for (int i = 0; i < obj.cap; i++)
			out << obj.mas[i] << " ";
		return out;
	}

	friend istream& operator>> (istream& in, myArray& obj) {
		for (int i = 0; i < obj.cap; ++i) {
			cout << "mas[" << i << "] = ";
			in >> obj.mas[i];
		}
		return in;
	}

	~myArray() {
		delete[]mas;
	}

	void showMas() {
		for (int i = 0; i < cap; i++)
			cout << mas[i] << " ";
		cout << endl;
	}

	void showCap() {
		cout << "Capacity: " << cap << endl;
	}

	void setMasRand(int b = 100, int a = -100) {
		if (a > b)swap(b, a);
		for (int i = 0; i < cap; ++i)
			mas[i] = a + rand() % (b - a + 1);
	}

	void setMasMan() {
		for (int i = 0; i < cap; ++i) {
			cout << "mas[" << i << "] = ";
			cin >> mas[i];
		}
	}

	void setSize(size_t size) {
		mas = (int*)realloc(mas, size * sizeof(int));
		for (int i = cap; i < size; ++i)
			mas[i] = 0;
		cap = size;
	}

	void sortMas() {
		int f;
		do {
			f = 0;
			for (int i = 0; i < cap - 1; i++)
				if (mas[i] > mas[i + 1]) {
					swap(mas[i], mas[i + 1]);
					f = 1;
				}
		} while (f);
	}

	int minMas() {
		int pmin = 0;
		for (int i = 0; i < cap; i++)
			if (mas[pmin] > mas[i])
				pmin = i;
		return pmin;
	}

	int maxMas() {
		int pmax = 0;
		for (int i = 0; i < cap; i++)
			if (mas[pmax] < mas[i])
				pmax = i;
		return pmax;
	}
	
};

myArray func() {
	myArray ob(20);
	return ob;
}


int main() {

	setlocale(LC_ALL, "Russian");
	srand(time(0));

	cout << "–азмер массива может быть передан в качестве параметра или задан с помощью вызова функции-члена." << endl;
	myArray S1;
	cout << "S1 ";
	S1.showCap();
	myArray S2(5);
	cout << "S2 ";
	S2.showCap();
	cout << " ласс должен позвол€ть заполн€ть массив значени€ми," << endl;
	S2.setMasRand(0, 100);
	cout << S2 << endl;
	S2.setMasMan();
	cout << "отображать содержимое массива," << endl;
	cout << S2 << endl;
	cout << "измен€ть размер массива," << endl;
	S2.setSize(12);
	cout << S2 << endl;
	cout << "сортировать массив," << endl;
	S2.sortMas();
	S2.showMas();
	cout << "определ€ть минимальное и максимальное значение." << endl;
	cout << S2[S2.maxMas()] << endl;
	cout << S2[S2.minMas()] << endl;
	cout << " ласс должен содержать набор конструкторов (конструктор копировани€ об€зателен), деструктор." << endl;
	S1 = S2;
	S1.showMas();
	myArray S3(S2);
	S3.showMas();
	S3 = S1 + S2;
	S3.showMas();
	S3 = func();
	S3.showMas();
	return 0;
}
