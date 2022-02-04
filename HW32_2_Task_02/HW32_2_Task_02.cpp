// Создать базовый класс «Домашнее животное» и производные классы «Собака», «Кошка», «Попугай».
// С помощью конструктора установить имя каждого животного и его характеристики.

#include <iostream>
#include <Windows.h>
#include <string>
using namespace std;

class Animal {
protected:
	string species;
	string name;
public:
	Animal(string species, string name) :species(species), name(name) {}
	string GetName() { return name; }
	string GetSpecies() { return species; }
	virtual string GetVoice() = 0;
};

class Dog : public Animal {
public:
	Dog(string species, string name) : Animal(species, name) {}
	string GetVoice() { return "Гав-гав!"; }
};

class Cat : public Animal {
public:
	Cat(string species, string name) : Animal(species, name) {}
	string GetVoice() { return "Мяу-мяу!"; }
};

class Parrot : public Animal {
public:
	Parrot(string species, string name) : Animal(species, name) {}
	string GetVoice() { return name + " харрроший!"; }
};


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Animal** animals = new Animal * [3]{
		new Dog("Пёс", "Бим"),
		new Cat("Кошка", "Мурка"),
		new Parrot("Попугай", "Кеша")
	};
	
	for (size_t i = 0; i < 3; i++) {
		cout << animals[i]->GetSpecies() << " " << animals[i]->GetName() << " говорит: \"" << animals[i]->GetVoice() << "\"" << endl;
		delete animals[i];
	}
	delete animals;
	return 0;
}