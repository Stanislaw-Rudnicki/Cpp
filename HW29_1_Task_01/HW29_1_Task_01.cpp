// Создайте шаблонный класс матрица.
// Необходимо реализовать динамическое выделение памяти, очистку памяти,
// заполнение матрицы с клавиатуры, заполнение случайными значениями, отображение матрицы,
// арифметические операции с помощью перегруженных операторов(+, –,	*, /),
// поиск максимального и минимального элемента.

#include <iostream>
#include <Windows.h>
#include <time.h>
using namespace std;

template<class T>
class Matrix {
	T** arr;
	int col, row;
	void Clear();
	void NewMemomy(int r, int c);
public:
	Matrix();
	Matrix(int r, int c);
	Matrix(const Matrix& M);
	Matrix(Matrix&& M) noexcept;
	~Matrix();
	void SetRND(int max, int min);
	T Max();
	T Min();
	Matrix& operator= (const Matrix& R);
	Matrix& operator= (Matrix&& R);
	Matrix operator+ (const Matrix& R);
	Matrix operator+ (T R);
	Matrix operator- (const Matrix& R);
	Matrix operator- (T R);
	Matrix operator* (const Matrix& R);
	Matrix operator* (T R);
	//Matrix operator/ (const Matrix& R);
	// В теории матриц нет понятия «деления матрицы», матрицы можно только умножать.
	Matrix operator- ();
	Matrix operator+ ();
	friend Matrix operator+ (T L, const Matrix& R);
	template<class T>
	friend ostream& operator<<(ostream& os, const Matrix<T>& R);
	template<class T>
	friend istream& operator>>(istream& fin, Matrix<T>& R);
};

template<class T>
void Matrix<T>::Clear()
{
	if (arr) {
		for (size_t i = 0; i < row; i++)
			delete[] arr[i];
		delete[] arr;
		arr = nullptr;
	}
}

template<class T>
void Matrix<T>::NewMemomy(int r, int c)
{
	row = r;
	col = c;
	arr = new T* [row];
	for (size_t i = 0; i < row; i++)
		arr[i] = new T [c] {0};
}

template<class T>
Matrix<T>::Matrix() :Matrix(1, 1) {}

template<class T>
Matrix<T>::Matrix(int r, int c)
{
	NewMemomy(r, c);
}

template<class T>
Matrix<T>::Matrix(const Matrix& M) :Matrix(M.row, M.col)
{
	for (size_t i = 0; i < row; i++)
		memcpy(arr[i], M.arr[i], col * sizeof(*M.arr[0]));
}

template<class T>
Matrix<T>::Matrix(Matrix&& M) noexcept
{
	row = M.row;
	col = M.col;
	arr = M.arr;
	M.arr = nullptr;
}

template<class T>
Matrix<T>::~Matrix()
{
	Clear();
}

template<class T>
void Matrix<T>::SetRND(int max, int min)
{
	if (min > max) swap(min, max);
	for (size_t i = 0; i < row; i++)
		for (size_t j = 0; j < col; j++)
			arr[i][j] = min + (T)(rand() % (max - min + 1)) / 100.0 + (rand() % (max - min));
}

template<class T>
T Matrix<T>::Max()
{
	T max = 0;
	for (size_t i = 0; i < row; i++)
		for (size_t j = 0; j < col; j++)
			if (arr[i][j] > max)
				max = arr[i][j];
	return max;
}

template<class T>
T Matrix<T>::Min()
{
	T min = 0;
	for (size_t i = 0; i < row; i++)
		for (size_t j = 0; j < col; j++)
			if (arr[i][j] < min)
				min = arr[i][j];
	return min;
}

template<class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& R)
{
	if (this != &R) {
		Clear();
		NewMemomy(R.row, R.col);
		for (size_t i = 0; i < row; i++)
			memcpy(arr[i], R.arr[i], col * sizeof(*R.arr[0]));
	}
	return *this;
}

template<class T>
Matrix<T>& Matrix<T>::operator=(Matrix<T>&& R)
{
	row = R.row;
	col = R.col;
	arr = R.arr;
	R.arr = nullptr;
	return *this;
}

template<class T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& R)
{
	int r = max(row, R.row);
	int c = max(col, R.col);
	Matrix Res(r, c);
	if (row == R.row && col == R.col) {
		for (size_t i = 0; i < row; i++)
			for (size_t j = 0; j < col; j++)
				Res.arr[i][j] = arr[i][j] + R.arr[i][j];
	}
	else {
		Matrix Mthis(r, c);
		Matrix MR(r, c);
		for (size_t i = 0; i < row; i++)
			for (size_t j = 0; j < col; j++)
				Mthis.arr[i][j] = arr[i][j];

		for (size_t i = 0; i < R.row; i++)
			for (size_t j = 0; j < R.col; j++)
				MR.arr[i][j] = R.arr[i][j];

		for (size_t i = 0; i < r; i++)
			for (size_t j = 0; j < c; j++)
				Res.arr[i][j] = Mthis.arr[i][j] + MR.arr[i][j];
	}
	return Res;
}

template<class T>
Matrix<T> Matrix<T>::operator+(T R)
{
	Matrix Res(row, col);
	for (size_t i = 0; i < row; i++)
		for (size_t j = 0; j < col; j++)
			Res.arr[i][j] = arr[i][j] + R;
	return Res;
}

template<class T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& R)
{
	int r = max(row, R.row);
	int c = max(col, R.col);
	Matrix Res(r, c);
	if (row == R.row && col == R.col) {
		for (size_t i = 0; i < row; i++)
			for (size_t j = 0; j < col; j++)
				Res.arr[i][j] = arr[i][j] - R.arr[i][j];
	}
	else {
		Matrix Mthis(r, c);
		Matrix MR(r, c);
		for (size_t i = 0; i < row; i++)
			for (size_t j = 0; j < col; j++)
				Mthis.arr[i][j] = arr[i][j];

		for (size_t i = 0; i < R.row; i++)
			for (size_t j = 0; j < R.col; j++)
				MR.arr[i][j] = R.arr[i][j];

		for (size_t i = 0; i < r; i++)
			for (size_t j = 0; j < c; j++)
				Res.arr[i][j] = Mthis.arr[i][j] - MR.arr[i][j];
	}
	return Res;
}

template<class T>
Matrix<T> Matrix<T>::operator-(T R)
{
	Matrix Res(row, col);
	for (size_t i = 0; i < row; i++)
		for (size_t j = 0; j < col; j++)
			Res.arr[i][j] = arr[i][j] - R;
	return Res;
}

template<class T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& R)
{
	if (row == R.col)
	{
		Matrix Res(row, R.col);
		for (int i = 0; i < row; i++)
			for (int j = 0; j < R.col; j++)
			{
				Res.arr[i][j] = 0;
				for (int k = 0; k < col; k++)
					Res.arr[i][j] += arr[i][k] * R.arr[k][j];
			}
		return Res;
	}
	else
		throw "Умножение невозможно";
}

template<class T>
Matrix<T> Matrix<T>::operator*(T R)
{
	Matrix Res(row, col);
	for (size_t i = 0; i < row; i++)
		for (size_t j = 0; j < col; j++)
			Res.arr[i][j] = arr[i][j] * R;
	return Res;
}

template<class T>
Matrix<T> Matrix<T>::operator-()
{
	Matrix Res(*this);
	for (size_t i = 0; i < row; i++)
		for (size_t j = 0; j < col; j++)
			Res.arr[i][j] = -Res.arr[i][j];
	return Res;
}

template<class T>
Matrix<T> Matrix<T>::operator+()
{
	return Matrix(*this);
}

template<class T>
Matrix<T> operator+ (T L, const Matrix<T>& R) {
	//return R + L;
	Matrix Res(R.row, R.col);
	for (size_t i = 0; i < R.row; i++)
		for (size_t j = 0; j < R.col; j++)
			Res.arr[i][j] = R.arr[i][j] + L;
	return Res;

}

template<class T>
ostream& operator<< (ostream& os, const Matrix<T>& R) {
	for (size_t i = 0; i < R.row; i++) {
		for (size_t j = 0; j < R.col; j++)
			os << R.arr[i][j] << "\t";
		os << "\n";
	}
	return os;
}

template<class T>
istream& operator>>(istream& fin, Matrix<T>& R) {
	for (size_t i = 0; i < R.row; i++)
		for (size_t j = 0; j < R.col; j++)
			fin >> R.arr[i][j];
	return fin;
}



int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(0));
	//srand(10);
	Matrix<double> A(3, 4);
	A.SetRND(-10, 10);
	
	cout << "A:\n" << A << endl;
	cout << "Max: " << A.Max() << endl;
	cout << "Min: " << A.Min() << endl << endl;
	
	Matrix<double> B(4, 3);
	B.SetRND(-10, 10);
	cout << "B:\n" << B << endl;
	cout << "A + B:\n" << A + B << endl << endl;
	cout << "A - B\n" << A - B << endl << endl;
	try {
		cout << "A * B:\n" << A * B << endl << endl;
	}
	catch (const char* ex) {
		cout << "Error = " << ex << endl;
	}
	
	cout << A * 5 << endl << endl;

	Matrix<double> C(2, 2);
	cout << "заполнение матрицы с клавиатуры: ";
	cin >> C;
	cout << "C:\n" << C << endl;
	try {
		cout << "A * C:\n" << A * C << endl << endl;
	}
	catch (const char* ex) {
		cout << "Error = " << ex << endl;
	}
	
	return 0;
}