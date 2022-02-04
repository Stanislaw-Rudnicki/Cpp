// Создать класс Airplane (самолет).
// С помощью перегрузки операторов реализовать:
// - Проверка на равенство типов самолетов (операция ==)
// - Увеличение и уменьшение пассажиров в салоне самолета (операции ++ и -- в префиксной форме)
// - Сравнение двух самолетов по максимально возможному количеству пассажиров на борту (операция >)


#include <iostream>
#include <Windows.h>
using namespace std;

class Airplane {
	char* type_;
	int maxpass_;
public:
	Airplane() :Airplane("", 0) {}
	Airplane(const char*, int);
	// Деструктор
	~Airplane();
	// Конструктор копирования
	Airplane(const Airplane&);
	// Конструктор перемещения
	Airplane(Airplane&&);
	// Оператор присваивания копированием
	Airplane& operator=(const Airplane&);
	// Оператор присваивания перемещением
	Airplane& operator=(Airplane&&);
	bool operator==(const Airplane&);
	bool operator!=(const Airplane&);
	bool operator>(const Airplane&);
	bool operator<(const Airplane&);
	Airplane operator++();
	Airplane operator--();
	friend ostream& operator<<(ostream&, const Airplane&);
	friend void swap(Airplane&, Airplane&);
};
Airplane::Airplane(const char* type, int maxpass) {
	type_ = _strdup(type);
	maxpass_ = maxpass;
}
Airplane::~Airplane() {
	delete[]type_;
}
Airplane::Airplane(const Airplane& other) {
	type_ = _strdup(other.type_);
	maxpass_ = other.maxpass_;
}
Airplane::Airplane(Airplane&& other) {
	type_ = other.type_;
	other.type_ = nullptr;
	maxpass_ = other.maxpass_;
}
Airplane& Airplane::operator=(const Airplane& other) {
	Airplane tmp(other);
	swap(*this, tmp);
	return *this;
}
Airplane& Airplane::operator=(Airplane&& other) {
	swap(*this, other);
	return *this;
}
bool Airplane::operator==(const Airplane& other) {
	if (strlen(type_) != strlen(other.type_))
		return false;
	if (strcmp(type_, other.type_))
		return false;
	return true;
}
bool Airplane::operator!=(const Airplane& other) {
	return !(operator == (other));
}
bool Airplane::operator>(const Airplane& other) {
	return maxpass_ > other.maxpass_;
}
bool Airplane::operator<(const Airplane& other) {
	return maxpass_ < other.maxpass_;
}
Airplane Airplane::operator++() {
	++maxpass_;
	return *this;
}
Airplane Airplane::operator--() {
	--maxpass_;
	return *this;
}
ostream& operator<<(ostream& out, const Airplane& other) {
	out << "Тип: " << other.type_ << ", Пассажиров: " << other.maxpass_;
	return out;
}
void swap(Airplane& l, Airplane& r) {
	using std::swap;
	swap(l.type_, r.type_);
	swap(l.maxpass_, r.maxpass_);
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Airplane a01("Boeing 737-400", 168);
	Airplane a02("Airbus A320-200", 180);
	Airplane a03;
	a03 = a01;

	cout << "p01:\t" << a01 << endl;
	cout << "p02:\t" << a02 << endl;
	cout << "p03:\t" << a03 << endl;
	cout << endl;
	cout << "p01" << " == " << "p02" << ": " << boolalpha << (a01 == a02) << endl;
	cout << "p01" << " == " << "p03" << ": " << boolalpha << (a01 == a03) << endl;
	cout << "p01" << " <  " << "p02" << ": " << boolalpha << (a01 < a02) << endl;
	cout << "p01" << " >  " << "p02" << ": " << boolalpha << (a01 > a02) << endl;
	cout << "++p03:\t" << ++a03 << endl;
	cout << "--p03:\t" << --a03 << endl;
	return 0;
}