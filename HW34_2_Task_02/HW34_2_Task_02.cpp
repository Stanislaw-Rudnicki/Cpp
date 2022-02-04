// �������� ���������� ���������� HTML - ������.
// ���������� ����������� � ������������ ���� � �����, ����� ���� ��������� ���� �� ����������.
// ��������� ���������� ��� ������ ������� �������� �������: ��� �������� ���� ������ �����������,
// ���� ��� ���� < ��� ������ ������� ���� >.
// �� ������ ��������� ����� ���������� ��������� �������� �� �����.
// ����������� ��� ������ � ������� ������, � ��� ������ �� �������� ����� string.


#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <map>

using namespace std;

//int Validate(string fn) {
//	ifstream file(fn);
//	if (!file.is_open()) {
//		cout << "Error read file\n";
//		return false;
//	}
//	string line;
//	size_t count = 0;
//	bool ok = true;
//	while (getline(file, line)) {
//		count++;
//		size_t pos2, postemp, pos = line.find("<", 0);
//		pos2 = line.find(">", 0);
//		if (pos > pos2) return count;
//		else if (pos != string::npos)
//			ok = false;
//		
//		while (pos != string::npos) {
//			if (!ok) {
//				postemp = pos;
//				pos = line.find(">", pos + 1);
//				pos2 = line.find("<", postemp + 1);
//				if (pos == string::npos) return count;
//				else if (pos > pos2) return count;
//				else if (pos < pos2) ok = true;
//			}
//			postemp = pos;
//			pos = line.find("<", pos);
//			pos2 = line.find(">", postemp + 1);
//			if (pos > pos2) return count;
//			else if (pos != string::npos)
//				ok = false;
//		}
//	}
//	file.close();
//	return 0;
//}

map<int, int> Validate(string fn) {
	map<int, int> map;
	ifstream file(fn);
	if (file.is_open()) {
		string line;
		size_t count = 0;
		bool ok = true;
		while (getline(file, line)) {
			count++;
			size_t pos2, postemp, pos = line.find("<", 0);
			pos2 = line.find(">", 0);
			if (pos > pos2) { map.emplace(count, pos); break; }
			else if (pos != string::npos)
				ok = false;

			while (pos != string::npos) {
				if (!ok) {
					postemp = pos;
					pos = line.find(">", pos + 1);
					pos2 = line.find("<", postemp + 1);
					if (pos == string::npos) { map.emplace(count, pos); break; }
					else if (pos > pos2) { map.emplace(count, pos); break; }
					else if (pos < pos2) ok = true;
				}
				postemp = pos;
				pos = line.find("<", pos);
				pos2 = line.find(">", postemp + 1);
				if (pos > pos2) { map.emplace(count, pos); break; }
				else if (pos != string::npos)
					ok = false;
			}
		}
		file.close();
		return map;
	}
	else
		return map;
}

template <class T, class U>
void Show(map<T, U>& map) {
	cout << "������\t�������\n";
	for (pair<T, U> i : map)
		cout << i.first << '\t' << i.second << endl;
	cout << endl;
};


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	string fn = "File.txt";
	//string fn2 = "File2.txt";

	//cout << Validate(fn) << endl;
	//cout << Validate(fn2) << endl;

	map<int, int> ErrList(Validate(fn));

	if (!ErrList.empty()) {
		cout << "��� ���� �������� ������:\n";
		Show(ErrList);
	}
	else
		cout << "��� ���� �� �������� ������\n";

	return 0;
}