// Создать шаблонный класс-контейнер Array, который представляет собой массив,
// позволяющий хранить объекты заданного типа.
// Класс должен реализовывать следующие функции:
// - GetSize – получение размера массива (количество элементов, под которые выделена память);
// - SetSize(int size, int grow = 1) – установка размера массива
//   (если параметр size больше предыдущего размера массива,
//   то выделяется дополнительный блок памяти, если нет, то «лишние» элементы теряются и память освобождается);
//   параметр grow определяет для какого количества элементов необходимо выделить память,
//   если количество элементов превосходит текущий размер массива.
//   Например, SetSize(5, 5); означает, что при добавлении 6-го элемента размер массива становится равным 10,
//   при добавлении 11-го - 15 и т. д.;
// - GetUpperBound - получение последнего допустимого индекса в массиве.
//   Например, если при размере массива 10, вы добавляете в него 4 элемента, то функция вернет 3;
// - IsEmpty - массив пуст?;
// - FreeExtra - удалить «лишнюю» память (выше последнего допустимого индекса);
// - RemoveAll - удалить все;
// - GetAt - получение определенного элемента (по индексу);
// - SetAt – установка нового значения для определенного элемента
//   (индекс элемента должен быть меньше текущего размера массива);
// - operator [] – для реализации двух предыдущих функций;
// - Add – добавление элемента в массив
//   (при необходимости массив увеличивается на значение grow функции SetSize);
// - Append – «сложение» двух массивов;
// - operator =;
// - GetData – получения адреса массива с данными;
// - InsertAt – вставка элемента(-ов) в заданную позицию;
// - RemoveAt – удаление элемента(-ов) с заданной позиции.

#include <iostream>
using namespace std;

template <typename T>
class Array {
	T* mas_;
	int count_;
	int cap_;
	int grow_;

public:
	Array();
	~Array();
	Array<T>(const Array& obj);
	Array<T>& operator=(const Array& obj);
	int GetSize();
	void SetSize(size_t size, int grow = 1);
	int GetUpperBound();
	bool IsEmpty();
	void FreeExtra();
	void RemoveAll();
	T GetAt(int index);
	void SetAt(int index, T val);
	T& operator[](int index);
	void Add(T val);
	Array<T>& Append(const Array& obj);
	T** GetData();
	void InsertAt(int pos, T val);
	void RemoveAt(int pos);
	
	template<class T>
	friend ostream& operator<<(ostream& out, const Array<T>& obj);
};

template <typename T>
Array<T>::Array()
{
	mas_ = 0;
	count_ = 0;
	cap_ = 0;
	grow_ = 1;
}

template <typename T>
Array<T>::~Array()
{
	if (mas_)
		delete[]mas_;
	mas_ = 0;
}

template<typename T>
Array<T>::Array(const Array& obj)
{
	count_ = obj.count_;
	cap_ = obj.cap_;
	grow_ = obj.grow_;
	mas_ = new int[cap_];
	memcpy(mas_, obj.mas_, sizeof(T) * cap_);
}

template <typename T>
Array<T>& Array<T>::operator=(const Array& obj)
{
	if (this != &obj) {
		delete[] mas_;
		count_ = obj.count_;
		cap_ = obj.cap_;
		grow_ = obj.grow_;
		mas_ = new int[obj.cap_];
		memcpy(mas_, obj.mas_, sizeof(T) * cap_);
	}
	return *this;
}

template <typename T>
int Array<T>::GetSize()
{
	return cap_;
}

template <typename T>
void Array<T>::SetSize(size_t size, int grow)
{
	grow_ = grow;
	if (size <= cap_) {
		mas_ = (T*)realloc(mas_, sizeof(T) * size);
		cap_ = size;
		if (count_ > cap_)
			count_ = cap_;
		return;
	}
	else {
		if (size % grow != 0)
			size = size + (grow - (size % grow));
		mas_ = (T*)realloc(mas_, sizeof(T) * size);
		cap_ = size;
	}
}

template <typename T>
int Array<T>::GetUpperBound()
{
	return count_ - 1;
}

template <typename T>
bool Array<T>::IsEmpty()
{
	return count_ == 0;
}

template <typename T>
void Array<T>::FreeExtra()
{
	if (cap_ % grow_ != 0) {
		mas_ = (T*)realloc(mas_, sizeof(T) * (count_ + (grow_ - count_ % grow_)));;
		cap_ = count_ + (grow_ - count_ % grow_);
	}
	else if (cap_ % grow_ == 0) {
		mas_ = (T*)realloc(mas_, sizeof(T) * count_);
		cap_ = count_;
	}
}

template <typename T>
void Array<T>::RemoveAll()
{
	delete[]mas_;;
	mas_ = 0;
	cap_ = 0;
	count_ = 0;
}

template <typename T>
T Array<T>::GetAt(int index)
{
	if (index >= 0 && index < count_) return mas_[index];
	else throw index;
}

template <typename T>
void Array<T>::SetAt(int index, T val)
{
	if (index >= 0 && index <= count_ && index < cap_) 	{
		mas_[index] = val;
		if (index == count_)
			count_++;
	}
}

template <typename T>
T& Array<T>::operator[](int index)
{
	if (index == count_ && index < cap_) {
		count_++;
		return mas_[index];
	}
	if (index >= 0 && index < count_) return mas_[index];
	else throw index;
}

template <typename T>
void Array<T>::Add(T val)
{
	if (count_ < cap_)
		mas_[count_++] = val;
	else if (count_ >= cap_) {
		SetSize(cap_ + grow_, grow_);
		mas_[count_++] = val;
	}
}

template <typename T>
Array<T>& Array<T>::Append(const Array& obj)
{
	SetSize(count_ + obj.count_, grow_);
	memcpy(mas_ + count_, obj.mas_, sizeof(T) * obj.count_);
	count_ = count_ + obj.count_;
	return *this;
}

template <typename T>
T** Array<T>::GetData()
{
	return &mas_;
}

template <typename T>
void Array<T>::InsertAt(int pos, T val)
{
	if (0 <= pos && pos <= count_) {
		if (cap_ < count_ + 1)
			SetSize(cap_ + 1, grow_);
		if (pos > count_)
			mas_[pos] = val;
		else {
			for (int i = count_; i >= pos; i--) {
				mas_[i] = mas_[i - 1];
			}
			mas_[pos] = val;
		}
		count_++;
	}
	else
		return;
}

template <typename T>
void Array<T>::RemoveAt(int pos)
{
	if (pos < 0 || pos >= count_)
		return;
	for (int i = pos; i < count_; i++)
		mas_[i] = mas_[i + 1];
	count_--;
}

template<class T>
ostream& operator<<(ostream& out, const Array<T>& obj)
{
	for (int i = 0; i < obj.count_; i++) {
		out << obj.mas_[i] << " ";
	}
	return out;
}

int main() {

	setlocale(0, "");
	Array<int> test;

	cout << "метод \"GetSize\":\n";
	cout << test.GetSize() << endl << endl;

	test.Add(1);
	test.Add(2);
	test.Add(3);
	cout << "метод \"Add\":\n";
	cout << test << endl << endl;

	cout << "метод \"GetUpperBound\":\n";
	cout << test.GetUpperBound() << endl << endl;

	cout << "метод \"IsEmpty\":\n";
	cout << boolalpha << test.IsEmpty() << endl << endl;

	cout << "метод \"GetSize\" (показываем количество элементов массива, под которые выделена память):\n";
	cout << test.GetSize() << endl << endl;

	test.SetSize(5, 5);
	cout << "метод \"SetSize\" (устанавилваем размер равнывй 5):\n";
	cout << test.GetSize() << endl << endl;

	test.SetAt(3, 4);
	test.SetAt(4, 5);
	cout << "метод \"SetAt\" (устанавилваем значение 4 и 5):\n";
	cout << test << endl << endl;

	cout << "метод \"FreeExtra\" (устанавливаем размер 10, используем фри экстра):\n";
	test.SetSize(10, 5);
	test.FreeExtra();
	cout << test.GetSize() << endl << endl;

	cout << "метод \"GetAt\" (Получаем значение 3-го элемента):\n";
	try {
		cout << test.GetAt(2) << endl << endl;	
	}
	catch (int ex) {
		cout << "Error: The element with index " << ex << " does not exist" << endl << endl;
	}

	cout << "метод \"operator[]\" (Получаем значение 3-го элемента):\n";
	try {
			cout << test[2] << endl << endl;
	}
	catch (int ex) {
		cout << "Error: The element with index " << ex << " does not exist" << endl << endl;
	}

	Array<int> test2;
	test2 = test;
	cout << "метод \"operator=\" (создали второй массив и приравняли первому.)\n";
	cout << test2 << endl << endl;

	cout << "метод \"GetData\" (Получаем адрес массива):\n";
	cout << test.GetData() << endl << endl;

	cout << "метод \"Append\" (Прибавили к первому массиву второй):\n";
	test.Append(test2);
	cout << test << endl << endl;

	cout << "метод \"InsertAt\" (Вставили во вторую позицию цифру 256):\n";
	test.InsertAt(2, 256);
	cout << test << endl << endl;

	cout << "метод \"RemoveAt\" (Убрали со второй позиции цифру 256):\n";
	test.RemoveAt(2);
	cout << test << endl << endl;

	return 0;
}