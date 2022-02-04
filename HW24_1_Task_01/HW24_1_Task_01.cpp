// Реализуйте класс “Студент”. Необходимо хранить в переменных - членах класса: ФИО, дату рождения, контактный телефон,
// город, страну, название учебного заведения, город и страну (где находится учебное заведение), номер группы.
// Реализуйте функции - члены класса для ввода данных, вывода данных,
// реализуйте аксессоры для доступа к отдельным переменным - членам.
	
#include <iostream>
#include <windows.h>
#include <iomanip>

using namespace std;

class student {
private:
	char fname[50], lname[50], mname[50], city[50], country[50], university[50], uniCity[50], uniCountry[50], phone[14], group[14];
	unsigned int d : 5;
	unsigned int m : 4;
	unsigned int y : 12;

public:
	student() {
		strcpy_s(fname, "");
		strcpy_s(lname, "");
		strcpy_s(mname, "");
		strcpy_s(city, "");
		strcpy_s(country, "");
		strcpy_s(university, "");
		strcpy_s(uniCity, "");
		strcpy_s(uniCountry, "");
		strcpy_s(phone, "");
		strcpy_s(group, "");
		d = 01;
		m = 01;
		y = 1900;
	}
	void setFname(const char* fname) {
		strcpy_s(this->fname, fname);
	}
	char* getFname() {
		return fname;
	}
	void setLname(const char* lname) {
		strcpy_s(this->lname, lname);
	}
	char* getLname() {
		return lname;
	}
	void setMname(const char* mname) {
		strcpy_s(this->mname, mname);
	}
	char* getmname() {
		return mname;
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

	void setStudent();
	void showStudent();
};

	   	 
void student::setStudent() {
	int n;
	char buf[50];
	SYSTEMTIME st;
	GetSystemTime(&st);
	do {
		cout << "Введите фамилию: "; cin.getline(buf, 50);
	} while (!*buf);
	setLname(buf);
	do {
		cout << "Введите имя: "; cin.getline(buf, 50);
	} while (!*buf);
	setFname(buf);
	do {
		cout << "Введите отчество: "; cin.getline(buf, 50);
	} while (!*buf);
	setMname(buf);
	do {
		cout << "Введите дату рождения. День: ";
		cin >> n;	cin.clear(); cin.ignore(cin.rdbuf()->in_avail());
	} while (n < 1 || 31 < n);
	setD(n);
	do {
		cout << "Введите дату рождения. Месяц: ";
		cin >> n; cin.clear(); cin.ignore(cin.rdbuf()->in_avail());
	} while (n < 1 || 12 < n);
	setM(n);
	do {
		cout << "Введите дату рождения. Год: ";
		cin >> n; cin.clear(); cin.ignore(cin.rdbuf()->in_avail());
	} while (n < 1 || st.wYear < n);
	setY(n);
	cout << "Введите контактный телефон: "; cin.getline(buf, 14);
	setPhone(buf);
	cout << "Введите город: "; cin.getline(buf, 50);
	setCity(buf);
	cout << "Введите страну: "; cin.getline(buf, 50);
	setCountry(buf);
	cout << "Введите название учебного заведения: "; cin.getline(buf, 50);
	setUniversity(buf);
	cout << "Введите город (где находится учебное заведение): "; cin.getline(buf, 50);
	setUniCity(buf);
	cout << "Введите страну (где находится учебное заведение): "; cin.getline(buf, 50);
	setUniCountry(buf);
	cout << "Введите номер группы: "; cin.getline(buf, 50);
	setGroup(buf);
}

void student::showStudent() {
	cout << "ФИО: " << lname << " " << mname << " " << fname << endl;
	cout << "Дата рождения: " << setfill('0') << setw(2) << d << "." << setfill('0') << setw(2) << m << "." << y << endl;
	cout << "Контактный телефон: " << phone << endl;
	cout << "Город: " << city << endl;
	cout << "Страна: " << country << endl;
	cout << "Название учебного заведения: " << university << endl;
	cout << "Город (где находится учебное заведение): " << uniCity << endl;
	cout << "Страна (где находится учебное заведение): " << uniCountry << endl;
	cout << "Номер группы: " << group << endl;
}


int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	student st;
	st.setStudent();
	cout << endl;
	st.showStudent();

	return 0;
}