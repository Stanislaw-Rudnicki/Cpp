// Создайте программу, имитирующую многоквартирный дом.
// Необходимо иметь классы “Человек”, “Квартира”, “Дом”.
// Класс “Квартира” содержит динамический массив объектов класса “Человек”.
// Класс “Дом” содержит массив объектов класса “Квартира”.
// Каждый из классов содержит переменные - члены и функции-члены, которые необходимы для предметной области класса.
// Обращаем ваше внимание, что память под строковые значения выделяется динамически.
// Например, для ФИО в классе “Человек”.
// Не забывайте обеспечить классы различными конструкторами (конструктор копирования обязателен), деструкторами.
// В main протестировать работу полученного набора классов.


#include <iostream>
#include <Windows.h>
#include <iomanip>
#include "myString.h" // Используется класс из предыдущего домашнего задания. Файл во вложении.
using namespace std;

// Логика следующая:
// Квартира не может существовать без дома. Поэтому класс Квартира определяется внутри класса Дом.
// Человек может одновременно проживать (или иметь в собственности) более, чем в 1 квартире.
// Людей можно заселять в квартиры, можно выселять.
// Можно смотреть кто живет в конкретном доме.
// Можно смотреть какие квартиры числятся за конкретным человеком.


class Block;
class Flat;

class Person {
	myString name;
	Block** person_block;
	int* flat_numbers;
	int flats_count;
public:
	Person() {
		flats_count = 0;
		person_block = nullptr;
		flat_numbers = nullptr;
	};
	~Person() {
		delete[]person_block;
		delete[]flat_numbers;
	};
	void setPerson(const char* n) {
		name = n;
	}
	void setPerson() {
		do {
			cout << "Введите ФИО: "; cin >> name; //name.set();
		} while (!name[0]);
	}
	void showPerson() {
		cout << name << endl;
	}
	void addFlat(Block* block_ptr, int flat_number) {
		Block** temp = new Block * [flats_count + 1];
		memcpy(temp, person_block, sizeof(person_block[0]) * flats_count);
		temp[flats_count] = block_ptr;
		delete[]person_block;
		person_block = temp;
		int* temp2 = new int [flats_count + 1];
		memcpy(temp2, flat_numbers, sizeof(flat_numbers[0]) * flats_count);
		temp2[flats_count] = flat_number;
		delete[]flat_numbers;
		flat_numbers = temp2;
		flats_count++;
	}
	void removeFlat(Block* block_ptr, int flat_number) {
		if (flat_number <= 0 || flat_number > flats_count) return;
		Block** temp = new Block * [flats_count - 1];
		if (flat_number) memcpy(temp, person_block, sizeof(person_block[0]) * (flat_number - 1));
		memcpy(temp + flat_number - 1, person_block + flat_number, sizeof(person_block[0]) * (flats_count - flat_number));
		delete[]person_block;
		person_block = temp;
		int* temp2 = new int[flats_count - 1];
		if (flat_number) memcpy(temp2, flat_numbers, sizeof(flat_numbers[0]) * (flat_number - 1));
		memcpy(temp2, flat_numbers, sizeof(flat_numbers[0]) * (flats_count - flat_number));
		delete[]flat_numbers;
		flat_numbers = temp2;
		flats_count--;
	}
	void showFlats();
	void unBind() {
		name.unBind();
	}
	
};

class Persons {
	Person* persons_mas;
	int count;
public:
	Persons() {
		count = 0;
		persons_mas = nullptr;
	};
	~Persons() {
		delete[]persons_mas;
	};
	void addPerson() {
		Person* temp = new Person[count + 1];
		memcpy(temp, persons_mas, sizeof(Person) * count);
		temp[count].setPerson();
		for (size_t i = 0; i < count; i++)
			persons_mas[i].unBind();
		delete[]persons_mas;
		persons_mas = temp;
		count++;
	}
	void addPerson(const char* name) {
		Person* temp = new Person[count + 1];
		memcpy(temp, persons_mas, sizeof(persons_mas[0]) * count);
		temp[count].setPerson(name);
		for (size_t i = 0; i < count; i++)
			persons_mas[i].unBind();
		delete[]persons_mas;
		persons_mas = temp;
		count++;
	}
	void showAll() {
		for (size_t i = 0; i < count; i++) {
			cout << setw(3) << i + 1 << " ";
			persons_mas[i].showPerson();
		}
	}
	void showFlats(int pers) {
		persons_mas[pers - 1].showFlats();
	}
	Person* getPerson_ptr(int pers) {
		return &persons_mas[pers];
	}
	void addFlat(Block* person_block, int fl_number, int pers) {
		persons_mas[pers].addFlat(person_block, fl_number);
	}
	void removeFlat(Block* person_block, int fl_number, int pers) {
		persons_mas[pers].removeFlat(person_block, fl_number);
	}
};

class Block {
	class Flat 	{
		Person** person_ptr;
		int person_count;
	public:
		Flat() {
			person_count = 0;
			person_ptr = nullptr;
		};
		~Flat() {
			delete[]person_ptr;
		};
		void addPerson(Persons &persons, int pers) {
			Person** temp = new Person*[person_count + 1];
			memcpy(temp, person_ptr, sizeof(person_ptr[0]) * person_count);
			temp[person_count] = persons.getPerson_ptr(pers);
			delete[]person_ptr;
			person_ptr = temp;
			person_count++;
		}
		void removePerson(Persons& persons, int pers) {
			if (pers <= 0 || pers > person_count) return;
			Person** temp = new Person * [person_count - 1];
			if (pers) memcpy(temp, person_ptr, sizeof(person_ptr[0]) * (pers - 1));
			memcpy(temp + pers - 1, person_ptr + pers, sizeof(person_ptr[0]) * (person_count - pers));
			delete[]person_ptr;
			person_ptr = temp;
			person_count--;
		}
		void showPersons() {
			for (size_t i = 0; i < person_count; i++) {
				cout << setw(3) << i + 1 << " ";
				person_ptr[i]->showPerson();
			}
		}
		int getPersonsCount() {
			return person_count;
		}
	};
	myString address;
	Flat* flats;
	int count;
public:
	Block() :Block(0, 0) {}
	Block(size_t c, const char* addr) {
		count = c;
		if (c) {
			flats = new Flat[count];
			address = addr;
		}
		else
			flats = 0;
	}
	~Block() {
		delete[]flats;
	}
	int getFlatsCount() {
		return count;
	}
	void addPerson(Persons &persons, int pers, int fl) {
		if (0 < fl || fl < count) {
			flats[fl - 1].addPerson(persons, pers - 1);
			persons.addFlat(this, fl, pers - 1);
		}
	}
	void removePerson(Persons& persons, int pers, int fl) {
		if (0 < fl || fl < count) {
			flats[fl - 1].removePerson(persons, pers);
			persons.removeFlat(this, fl, pers - 1);
		}
	}
	void showPersons(int flat_number) {
		flats[flat_number - 1].showPersons();
	};
	void showAll() {
		for (size_t i = 0; i < count; i++) {
			if (flats[i].getPersonsCount()) {
				cout << "кв. " << setw(3) << i + 1 << endl;
				flats[i].showPersons();
			}
		}
	};
	void showAddress() {
		cout << "ул. " << address << endl;
	};
};

void Person::showFlats() {
	showPerson();
	for (size_t i = 0; i < flats_count; i++) {
		person_block[i]->showAddress();
		cout << "кв. " << setw(3) << flat_numbers[i] << endl;
	}
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	// создаем массив людей
	Persons persons;

	// в массив людей добавляем несколько человек
	persons.addPerson("Ананченко Михайло Олегович");
	persons.addPerson("Лозинський Роман Михайлович");
	persons.addPerson("Бакумов Олександр Сергійович");
	persons.addPerson("Бобровська Соломія");
	persons.addPerson("Бабенко Микола");

	cout << "Показать всех людей:" << endl;
	persons.showAll();

	cout << "\nCоздать дом на 18 квартир... ";
	Block b_01(18, "Киевская, 1");
	cout << "Готово!" << endl;
	cout << "Cоздать дом на 30 квартир... ";
	Block b_02(30, "Хлебная, 3");
	cout << "Готово!" << endl;

	cout << "Заселить человека №1 в квартиру №1 в доме b_01... ";
	b_01.addPerson(persons, 1, 1);
	cout << "Готово!" << endl;
	cout << "Заселить человека №2 в квартиру №1 в доме b_01... ";
	b_01.addPerson(persons, 2, 1);
	cout << "Готово!" << endl;
	cout << "Заселить человека №3 в квартиру №18 в доме b_01... ";
	b_01.addPerson(persons, 3, 18);
	cout << "Готово!" << endl;
	
	cout << "Заселить человека №1 в квартиру №10 в доме b_02... ";
	b_02.addPerson(persons, 1, 10);
	cout << "Готово!" << endl;

	cout << "\nПоказать кто живет в доме b_01, в квартире 1:" << endl;
	b_01.showAddress(); cout << "кв. 1" << endl;
	b_01.showPersons(1);

	cout << "\nПоказать всех людей, которые живут в доме b_01:" << endl;
	b_01.showAddress();
	b_01.showAll();

	cout << "\nПоказать все квартиры человека №1:" << endl;
	persons.showFlats(1);
	
	cout << "\nВыселить человека №1 из квартиры №1 в доме b_01... ";
	b_01.removePerson(persons, 1, 1);
	cout << "Готово!" << endl;

	cout << "\nПоказать кто живет в доме b_01, в квартире 1:" << endl;
	b_01.showAddress(); cout << "кв. 1" << endl;
	b_01.showPersons(1);
	
	cout << "\nПоказать всех людей, которые живут в доме b_01:" << endl;
	b_01.showAddress();
	b_01.showAll();

	cout << "\nПоказать все квартиры человека №1:" << endl;
	persons.showFlats(1);

	return 0;
}