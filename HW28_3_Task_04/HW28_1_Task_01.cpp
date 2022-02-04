// В ранее созданный класс Array добавьте перегрузку [], (), преобразования типов к int и char*:
// - [] – возвращает элемент по указанному индексу
// - () – увеличивает все элементы массива на указанную величину
// Преобразование к int возвращает сумму элементов массива
// Преобразование к char* возвращает значения элементов массива в виде строки


#include <iostream>
#include <stdio.h>
#include <ctime>
using namespace std;

class myArray {
	int* mas;
	size_t cap;
public:
	myArray() :myArray(1) {}
	myArray(size_t c);
	~myArray();
	// Конструктор копирования
	myArray(const myArray& obj);
	// Конструктор переноса
	myArray(myArray&& obj);
	myArray operator=(const myArray& obj);
	myArray operator=(myArray&& obj);
	myArray operator+(const myArray& obj);
	int& operator[](int index);
	myArray& operator()(int val);
	operator int();
	operator char*();
	friend ostream& operator<<(ostream& out, const myArray& obj);
	friend istream& operator>>(istream& in, myArray& obj);
	void showMas();
	void showCap();
	void setMasRand(int b = 100, int a = -100);
	void setMasMan();
	void setSize(size_t size);
	void sortMas();
	int minMas();
	int maxMas();
};
myArray::myArray(size_t c) {
	cap = c;
	if (c)
		mas = new int[cap] {0};
	else
		mas = 0;
}
myArray::~myArray() {
	delete[]mas;
}
myArray::myArray(const myArray& obj) {
	cap = obj.cap;
	mas = new int[cap];
	memcpy(mas, obj.mas, sizeof(int) * cap);
}
myArray::myArray(myArray&& obj) {
	cap = obj.cap;
	mas = obj.mas;
	obj.mas = 0;
}
myArray myArray::operator=(const myArray& obj) {
	if (this != &obj) {
		delete[] mas;
		cap = obj.cap;
		mas = new int[obj.cap];
		memcpy(mas, obj.mas, sizeof(int) * cap);
	}
	return *this;
}
myArray myArray::operator=(myArray&& obj) {
	delete[] mas;
	cap = obj.cap;
	mas = obj.mas;
	obj.mas = 0;
	return *this;
}
myArray myArray::operator+(const myArray& obj) {
	myArray temp(cap + obj.cap);
	memcpy(temp.mas, mas, sizeof(int) * cap);
	memcpy(temp.mas + cap, obj.mas, sizeof(int) * obj.cap);
	return temp;
}
int& myArray::operator[](int index) {
	if (index <= cap)
		return mas[index];
	else
		return mas[cap];
}
myArray& myArray::operator()(int val) {
	for (int i = 0; i < cap; i++)
		mas[i] += val;
	return *this;
}
myArray::operator int() {
	int sum = 0;
	for (int i = 0; i < cap; i++)
		sum += mas[i];
	return sum;
}
myArray::operator char* () {
	int b_size = 255, cx = 0;
	char* buf = new char[b_size] {0};
	for (int i = 0; i < cap; i++) {
		if (cx > b_size - 11)
			buf = (char*)realloc(buf, b_size += 255);
		cx += snprintf(buf + cx, b_size - cx, "%d", mas[i]);
	}
	return buf;
}
void myArray::showMas() {
	for (int i = 0; i < cap; i++)
		cout << mas[i] << " ";
	cout << endl;
}
void myArray::showCap() {
	cout << "Capacity: " << cap << endl;
}
void myArray::setMasRand(int b, int a) {
	if (a > b)swap(b, a);
	for (int i = 0; i < cap; ++i)
		mas[i] = a + rand() % (b - a + 1);
}
void myArray::setMasMan() {
	for (int i = 0; i < cap; ++i) {
		cout << "mas[" << i << "] = ";
		cin >> mas[i];
	}
}
void myArray::setSize(size_t size) {
	mas = (int*)realloc(mas, size * sizeof(int));
	for (int i = cap; i < size; ++i)
		mas[i] = 0;
	cap = size;
}
void myArray::sortMas() {
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
int myArray::minMas() {
	int pmin = 0;
	for (int i = 0; i < cap; i++)
		if (mas[pmin] > mas[i])
			pmin = i;
	return pmin;
}
int myArray::maxMas() {
	int pmax = 0;
	for (int i = 0; i < cap; i++)
		if (mas[pmax] < mas[i])
			pmax = i;
	return pmax;
}
ostream& operator<<(ostream& out, const myArray& obj) {
	for (int i = 0; i < obj.cap; i++)
		out << obj.mas[i] << " ";
	return out;
}
istream& operator>>(istream& in, myArray& obj) {
	for (int i = 0; i < obj.cap; ++i) {
		cout << "mas[" << i << "] = ";
		in >> obj.mas[i];
	}
	return in;
}

myArray func() {
	myArray ob(20);
	return ob;
}


int main() {
	setlocale(LC_ALL, "Russian");
	srand(time(0));

	cout << "Размер массива может быть передан в качестве параметра или задан с помощью вызова функции-члена." << endl;
	myArray S1;
	cout << "S1 ";
	S1.showCap();
	myArray S2(5);
	cout << "S2 ";
	S2.showCap();
	cout << "Класс должен позволять заполнять массив значениями," << endl;
	S2.setMasRand(-1000, 1000);
	cout << S2 << endl;
	//S2.setMasMan();
	cout << "отображать содержимое массива," << endl;
	cout << S2 << endl;
	cout << "изменять размер массива," << endl;
	S2.setSize(12);
	cout << S2 << endl;
	cout << "сортировать массив," << endl;
	S2.sortMas();
	S2.showMas();
	cout << "определять минимальное и максимальное значение." << endl;
	cout << S2[S2.maxMas()] << endl;
	cout << S2[S2.minMas()] << endl;
	cout << "Класс должен содержать набор конструкторов (конструктор копирования обязателен), деструктор." << endl;
	S1 = S2;
	S1.showMas();
	myArray S3(S2);
	S3.showMas();
	S3 = S1 + S2;
	S3.showMas();
	/*S3 = func();
	S3.showMas();*/
	cout << "[] – возвращает элемент по указанному индексу" << endl;
	cout << S3[0] << endl;
	cout << "() – увеличивает все элементы массива на указанную величину" << endl;
	cout << S3(10) << endl;
	cout << "Преобразование к int возвращает сумму элементов массива" << endl;
	cout << (int)S3 << endl;
	cout << "Преобразование к char* возвращает значения элементов массива в виде строки" << endl;
	cout << (char*)S3 << endl;
	
	return 0;
}