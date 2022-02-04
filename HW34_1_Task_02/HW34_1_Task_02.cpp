// Используя механизм множественного наследования разработайте класс “Автомобиль”.
// Должны быть классы “Колеса», «Двигатель», «Двери» и т. д.

#include <Windows.h>
#include <iostream>
using namespace std;

class Wheel {
	int R;
public:
	Wheel(int r) : R(r) {};
	int GetR() { return R; }
	void SetR(int r) { R = r; }
};

class Engine {
	double Volume;
public:
	Engine(double v) : Volume(v) {};
	double GetVolume() { return Volume; }
	void SetVolume(double r) { Volume = r; }
};

class Door {
	int N;
public:
	Door(int n) : N(n) {};
	int GetN() { return N; }
	void SetN(int n) { N = n; }
	void Open() { cout << "Двери открылись" << endl; }
	void Close() { cout << "Двери закрылись" << endl; }
};

class Car : public Wheel, public Engine, public Door {
	string make, model;
public:
	Car(string make, string model, int r, double v, int n) : make(make), model(model), Wheel(r), Engine(v), Door(n) {};
	string GetMake() { return make; };
	string GetModel() { return model; };
	void Drive() {
		cout << "ехать" << endl;
	}
};


int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Car car("Toyota", "Corolla", 16, 1.8, 5);

	cout << "Это автомобиль " << car.GetMake() << " " << car.GetModel() << endl;
	cout << "Двигатель: " << car.GetVolume() << endl;
	cout << "Дверей: " << car.GetN() << endl;
	cout << "Колеса: " << car.GetR() << endl;
	cout << "Автомобиль может: ";
	car.Drive();

	cout << endl;

	return 0;
}