// � ��� �������������� ������ ����� �������� ����������� ������������,
// �������� ��� ������� inline, ����������� ��������������.

// � ��� �������������� ������ Student �������� ����������� ������������,
// ����������, �������� ��� ������� inline, ����������� ��������������.
// ����������� �������� ������ ��� ��� �������� �����������,
// ���������� ������ ���������� ����������� � �����������.

// � ��� ������������� ������� �����, �����, Student
// �������� �������� ������������� �������������
// � ����������� ��������� ���������� ��������� �������� ���� �������.

#include <iostream>
#include <Windows.h>
#include <iomanip>
using namespace std;

class Point {
	double* coords;
public:
	static int count;
	Point();
	Point(double x, double y, double z);
	// ����������
	~Point();
	// ����������� �����������
	Point(const Point& other);
	// ����������� �����������
	Point(Point&& other) noexcept;
	// �������� ������������ ������������
	Point& operator=(const Point& other);
	// �������� ������������ ������������
	Point& operator=(Point&& other);
	friend void swap(Point& l, Point& r);
	void saveToFile(const char* fn);
	void loadFromFile(const char* fn);
	void setX(double x) { coords[0] = x; }
	double getX() { return coords[0]; }
	void setY(double y) { coords[1] = y; }
	double getY() { return coords[1]; }
	void setZ(double z) { coords[2] = z; }
	double getZ() { return coords[2]; }
	static int getCount() { return count; }
	void set() {
		printf("x = ");
		scanf_s("%lf", &coords[0]);
		printf("y = ");
		scanf_s("%lf", &coords[1]);
		printf("z = ");
		scanf_s("%lf", &coords[2]);
	}
	void show() { printf("x = %g\ny = %g\nz = %g\n", coords[0], coords[1], coords[2]); }
};
Point::Point() :Point(0, 0, 0) {}
Point::Point(double x, double y, double z) {
	coords = (double*)malloc(3 * sizeof(double));
	coords[0] = x;
	coords[1] = y;
	coords[2] = z;
	count++;
}
// ����������
Point::~Point() {
	free(coords);
	count--;
};
// ����������� �����������
Point::Point(const Point& other) {
	coords = (double*)malloc(3 * sizeof(double));
	memcpy(coords, other.coords, sizeof(coords[0]) * 3);
	count++;
}
// ����������� �����������
Point::Point(Point&& other) noexcept {
	coords = other.coords;
	other.coords = nullptr;
	count++;
}
// �������� ������������ ������������
Point& Point::operator=(const Point& other) {
	Point tmp(other);
	swap(*this, tmp);
	return *this;
}
// �������� ������������ ������������
Point& Point::operator=(Point&& other) {
	swap(*this, other);
	return *this;
}
void swap(Point& l, Point& r) {
	using std::swap;
	swap(l.coords, r.coords);
}

void Point::saveToFile(const char* fn) {
	FILE* fs;
	fopen_s(&fs, fn, "wb");
	if (!fs) {
		printf("Can't open file, exiting...\n");
		exit(-1);
	}
	if (fwrite(coords, sizeof(coords[0]), 3, fs) != 3)
		printf("������ ������ � ����.\n");
	else
		printf("������ �������� � ���� %s\n", fn);
	fclose(fs);
}
void Point::loadFromFile(const char* fn) {
	FILE* fs;
	fopen_s(&fs, fn, "rb");
	if (!fs) {
		printf("������ ������ �����.\n");
		return;
	}
	fseek(fs, 0, SEEK_END);
	int fsize = ftell(fs);
	fseek(fs, 0, SEEK_SET);
	int size = sizeof(coords);
	if (fsize % size != 0)
		printf("���� ���������.\n");
	else {
		int count = fsize / size;
		if (fread(coords, size, count, fs) != count)
			printf("������ ������ �����.\n");
		else
			printf("������ �� ����� %s ���������\n", fn);
	}
	fclose(fs);
}

int Point::count = 0;

// --------------------------------------------------------------

class Fraction {
	int numerator, denominator;
public:
	static int count;
	Fraction() : Fraction(0, 1) {} //numerator(0), denominator(1) { count++; }
	Fraction(const int& number) : Fraction(number, 1) {} //numerator(number), denominator(1) { count++; }
	Fraction(const int& numerator, const int& denominator) : numerator(numerator), denominator(denominator) { count++; }
	const int& getNumerator() const { return numerator; }
	const int& getDenominator() const { return denominator; }
	Fraction getReduced() const {
		int gcd = getGCD(getNumerator(), getDenominator());
		int numerator = getNumerator() / gcd;
		int denominator = getDenominator() / gcd;
		if (denominator < 0) {
			numerator = -numerator;
			denominator = -denominator;
		}
		return Fraction(numerator, denominator);
	}
	static int getGCD(const int& a, const int& b) {
		int x = abs(a);
		int y = abs(b);
		while (1) {
			x = x % y;
			if (x == 0)
				return y;
			y = y % x;
			if (y == 0) 
				return x;
		}
	}
	static int getCount() { return count; }
	// ����������
	~Fraction() {
		count--;
	};
	// ����������� �����������
	Fraction(const Fraction& other) : numerator(other.numerator), denominator(other.denominator) {
		count++;
	}
	// �������� ������������ ������������
	Fraction& operator=(const Fraction& other) {
		Fraction tmp(other);
		swap(*this, tmp);
		return *this;
	}
	friend void swap(Fraction& l, Fraction& r);
	void show() {
		Fraction reduced = getReduced();
		cout << reduced.getNumerator() << "/" << reduced.getDenominator();
	}
};
void swap(Fraction& l, Fraction& r) {
	using std::swap;
	swap(l.numerator, r.numerator);
	swap(l.denominator, r.denominator);
}

int Fraction::count = 0;

Fraction foo() {
	Fraction temp(2, 4);
	return temp;
}

// --------------------------------------------------------------

class Student {
	char* name;
	char city[50], country[50], university[50], uniCity[50], uniCountry[50], phone[14], group[14];
	unsigned int d : 5;
	unsigned int m : 4;
	unsigned int y : 12;
public:
	static int count;
	Student() : Student("", "", "", "", "", "", "", "", 01, 01, 1900) {}
	Student(const char* n = "", const char* city = "", const char* country = "", const char* university = "",
			const char* uniCity = "", const char* uniCountry = "", const char* phone = "", const char* group = "",
			int d = 01, int m = 01, int y = 1900) {
		name = _strdup(n);
		strcpy(this->city, city);
		strcpy(this->country, country);
		strcpy(this->university, university);
		strcpy(this->uniCity, uniCity);
		strcpy(this->uniCountry, uniCountry);
		strcpy(this->phone, phone);
		strcpy(this->group, group);
		this->d = d;
		this->m = m;
		this->y = y;
		count++;
	}
	// ����������
	~Student() {
		delete[]name;
		count--;
	}
	// ����������� �����������
	Student(const Student& other) {
		name = _strdup(other.name);
		strcpy(city, other.city);
		strcpy(country, other.country);
		strcpy(university, other.university);
		strcpy(uniCity, other.uniCity);
		strcpy(uniCountry, other.uniCountry);
		strcpy(phone, other.phone);
		strcpy(group, other.group);
		d = d;
		m = m;
		y = y;
		count++;
	}
	// ����������� �����������
	Student(Student&& other) {
		name = other.name;
		other.name = nullptr;
		strcpy(city, other.city);
		strcpy(country, other.country);
		strcpy(university, other.university);
		strcpy(uniCity, other.uniCity);
		strcpy(uniCountry, other.uniCountry);
		strcpy(phone, other.phone);
		strcpy(group, other.group);
		d = other.d;
		m = other.m;
		y = other.y;
		count++;
	}
	// �������� ������������ ������������
	Student& operator = (const Student& other) {
		Student tmp(other);
		swap(*this, tmp);
		return *this;
	}
	// �������� ������������ ������������
	Student& operator = (Student&& other) {
		swap(*this, other);
		return *this;
	}
	friend void swap(Student& l, Student& r);
	void setName(const char* name) {
		strcpy(this->name, name);
	}
	char* getName() {
		return name;
	}
	void setD(int d) {
		this->d = d;
	}
	int getD() {
		return d;
	}
	void setM(int m) {
		this->m = m;
	}
	int getM() {
		return m;
	}
	void setY(int y) {
		this->y = y;
	}
	int getY() {
		return y;
	}
	void setPhone(const char* phone) {
		strcpy_s(this->phone, phone);
	}
	char* getPhone() {
		return phone;
	}
	void setCity(const char* city) {
		strcpy_s(this->city, city);
	}
	char* getCity() {
		return city;
	}
	void setCountry(const char* country) {
		strcpy_s(this->country, country);
	}
	char* getCountry() {
		return country;
	}
	void setUniversity(const char* university) {
		strcpy_s(this->university, university);
	}
	char* getUniversity() {
		return university;
	}
	void setUniCity(const char* uniCity) {
		strcpy_s(this->uniCity, uniCity);
	}
	char* getuniCity() {
		return uniCity;
	}
	void setUniCountry(const char* uniCountry) {
		strcpy_s(this->uniCountry, uniCountry);
	}
	char* getUniCountry() {
		return uniCountry;
	}
	void setGroup(const char* group) {
		strcpy_s(this->group, group);
	}
	char* getGroup() {
		return group;
	}

	void set();
	void show();
};
void swap(Student& l, Student& r) {
	using std::swap;
	swap(l.name, r.name);
	swap(l.city, r.city);
	swap(l.country, r.country);
	swap(l.university, r.university);
	swap(l.uniCity, r.uniCity);
	swap(l.uniCountry, r.uniCountry);
	swap(l.phone, r.phone);
	swap(l.group, r.group);
	l.d = r.d;
	l.m = r.m;
	l.y = r.y;
}

int Student::count = 0;

void Student::set() {
	int n;
	char buf[255];
	SYSTEMTIME st;
	GetSystemTime(&st);
	do {
		cout << "������� ���: "; cin.getline(buf, 255);
	} while (!*buf);
	setName(buf);
	do {
		cout << "������� ���� ��������. ����: ";
		cin >> n;	cin.clear(); cin.ignore(cin.rdbuf()->in_avail());
	} while (n < 1 || 31 < n);
	setD(n);
	do {
		cout << "������� ���� ��������. �����: ";
		cin >> n; cin.clear(); cin.ignore(cin.rdbuf()->in_avail());
	} while (n < 1 || 12 < n);
	setM(n);
	do {
		cout << "������� ���� ��������. ���: ";
		cin >> n; cin.clear(); cin.ignore(cin.rdbuf()->in_avail());
	} while (n < 1 || st.wYear < n);
	setY(n);
	cout << "������� ���������� �������: "; cin.getline(buf, 14);
	setPhone(buf);
	cout << "������� �����: "; cin.getline(buf, 50);
	setCity(buf);
	cout << "������� ������: "; cin.getline(buf, 50);
	setCountry(buf);
	cout << "������� �������� �������� ���������: "; cin.getline(buf, 50);
	setUniversity(buf);
	cout << "������� ����� (��� ��������� ������� ���������): "; cin.getline(buf, 50);
	setUniCity(buf);
	cout << "������� ������ (��� ��������� ������� ���������): "; cin.getline(buf, 50);
	setUniCountry(buf);
	cout << "������� ����� ������: "; cin.getline(buf, 50);
	setGroup(buf);
}

void Student::show() {
	cout << "���: " << name << endl;
	cout << "���� ��������: " << setfill('0') << setw(2) << d << "." << setfill('0') << setw(2) << m << "." << y << endl;
	cout << "���������� �������: " << phone << endl;
	cout << "�����: " << city << endl;
	cout << "������: " << country << endl;
	cout << "�������� �������� ���������: " << university << endl;
	cout << "����� (��� ��������� ������� ���������): " << uniCity << endl;
	cout << "������ (��� ��������� ������� ���������): " << uniCountry << endl;
	cout << "����� ������: " << group << endl;
}

Student newStud() {
	Student P("Pavlo", "", "", "", "", "", "", "", 22, 01, 1999);
	P.show();
	cout << endl;
	return P;
}

Student newStud2() {
	return Student("Pasha", "", "", "", "", "", "", "", 25, 11, 2000);
}


int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Point a, c;
	Point b(3.6, 4, 0.7);

	printf("������ �:\n");
	//a.set();
	a = { 5, 4, 3 };

	printf("\n�������� �:\n");
	a.show();

	printf("\n�������� b:\n");
	b.show();

	printf("\n�������� b � ����:\n");
	b.saveToFile("Point_b.bin");

	printf("\n��������� �� ����� � �:\n");
	c.loadFromFile("Point_b.bin");

	printf("\n�������� �:\n");
	c.show();

	/*Point d(b);
	d.show();
	d = c;
	d.show();*/
	
	cout << "\n���������� ��������� ��������: " << Point::count << endl;
	cout << "--------------------------------------------------------------" << endl << endl;


	Fraction fra(2, 3);
	fra.show(); cout << endl;
	Fraction fra2;
	fra2 = fra;
	fra2.show(); cout << endl;
	fra = foo();
	fra.show(); cout << endl;
	fra = { 4, 3 };
	fra.show(); cout << endl;
	cout << "\n���������� ��������� ��������: " << Fraction::count << endl;
	cout << "--------------------------------------------------------------" << endl << endl;

	Student NP("Ira", "", "", "", "", "", "", "", 20, 05, 1998);
	NP.show();
	cout << endl;
	NP = newStud();
	NP.show();
	cout << endl;

	NP = newStud2();
	NP.show();
	
	cout << "\n���������� ��������� ��������: " << Student::count << endl;

	return 0;
}