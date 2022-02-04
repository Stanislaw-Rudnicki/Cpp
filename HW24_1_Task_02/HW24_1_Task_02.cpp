// Реализуйте класс “Точка”. Необходимо хранить координаты x, y, z в переменных - членах класса.
// Реализуйте функции - члены класса для ввода данных, вывода данных,
// реализуйте аксессоры для доступа к переменным - членам,
// реализуйте сохранение в файл и загрузку данных из файла.

#include <iostream>
#include <Windows.h>

using namespace std;

class point {
	double* coords;

public:
	point();
	point(double x, double y, double z);
	point(const point& other);
	~point();
	void saveToFile(const char* fn);
	void loadFromFile(const char* fn);

	void setX(double x) {
		coords[0] = x;
	}
	double getX() {
		return coords[0];
	}
	void setY(double y) {
		coords[1] = y;
	}
	double getY() {
		return coords[1];
	}
	void setZ(double z) {
		coords[2] = z;
	}
	double getZ() {
		return coords[2];
	}

	void set() {
		printf("x = ");
		scanf_s("%lf", &coords[0]);
		printf("y = ");
		scanf_s("%lf", &coords[1]);
		printf("z = ");
		scanf_s("%lf", &coords[2]);
	}

	void show() {
		printf("x = %g\ny = %g\nz = %g\n", coords[0], coords[1], coords[2]);
	}
};

point::point() {
	coords = (double*)calloc(3, sizeof(double));
}

point::point(double x, double y, double z) {
	coords = (double*)malloc(3 * sizeof(double));
	coords[0] = x;
	coords[1] = y;
	coords[2] = z;
}
point::point(const point& other) {
	coords = (double*)malloc(3 * sizeof(double));
	memcpy(coords, other.coords, sizeof(double) * 3);
}

point::~point() {
	free(coords);
};

void point::saveToFile(const char* fn) {
	FILE* fs;
	fopen_s(&fs, fn, "wb");
	if (!fs) {
		printf("Can't open file, exiting...\n");
		exit(-1);
	}
	if (fwrite(coords, sizeof(coords[0]), 3, fs) != 3)
		printf("Ошибка записи в файл.\n");
	else
		printf("Данные записаны в файл %s\n", fn);
	fclose(fs);
}

void point::loadFromFile(const char* fn) {
	FILE* fs;
	fopen_s(&fs, fn, "rb");
	if (!fs) {
		printf("Ошибка чтения файла.\n");
		return;
	}
	fseek(fs, 0, SEEK_END);
	int fsize = ftell(fs);
	fseek(fs, 0, SEEK_SET);
	int size = sizeof(coords);
	if (fsize % size != 0)
		printf("Файл поврежден.\n");
	else {
		int count = fsize / size;
		//double* temp = (double*)malloc(3 * sizeof(double));
		if (fread(coords, size, count, fs) != count)
			printf("Ошибка чтения файла.\n");
		else
			printf("Данные из файла %s загружены\n", fn);
		//free(coords);
		//coords = temp;
	}
	fclose(fs);
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	point a, c;
	point b(3.6, 4, 0.7);

	printf("Ввести а:\n");
	a.set();
	
	printf("\nПоказать а:\n");
	a.show();

	printf("\nПоказать b:\n");
	b.show();
	
	printf("\nЗаписать b в файл:\n");
	b.saveToFile("Point_b.bin");
	
	printf("\nЗагрузить из файла в с:\n");
	c.loadFromFile("Point_b.bin");
	
	printf("\nПоказать с:\n");
	c.show();
	
	/*point d(b);
	d.show();*/

	return 0;
}