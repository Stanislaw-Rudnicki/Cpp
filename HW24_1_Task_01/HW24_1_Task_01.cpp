// ���������� ����� ��������. ���������� ������� � ���������� - ������ ������: ���, ���� ��������, ���������� �������,
// �����, ������, �������� �������� ���������, ����� � ������ (��� ��������� ������� ���������), ����� ������.
// ���������� ������� - ����� ������ ��� ����� ������, ������ ������,
// ���������� ��������� ��� ������� � ��������� ���������� - ������.
	
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
		cout << "������� �������: "; cin.getline(buf, 50);
	} while (!*buf);
	setLname(buf);
	do {
		cout << "������� ���: "; cin.getline(buf, 50);
	} while (!*buf);
	setFname(buf);
	do {
		cout << "������� ��������: "; cin.getline(buf, 50);
	} while (!*buf);
	setMname(buf);
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

void student::showStudent() {
	cout << "���: " << lname << " " << mname << " " << fname << endl;
	cout << "���� ��������: " << setfill('0') << setw(2) << d << "." << setfill('0') << setw(2) << m << "." << y << endl;
	cout << "���������� �������: " << phone << endl;
	cout << "�����: " << city << endl;
	cout << "������: " << country << endl;
	cout << "�������� �������� ���������: " << university << endl;
	cout << "����� (��� ��������� ������� ���������): " << uniCity << endl;
	cout << "������ (��� ��������� ������� ���������): " << uniCountry << endl;
	cout << "����� ������: " << group << endl;
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