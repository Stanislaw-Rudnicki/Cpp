// ������� ��������� �����-��������� Array, ������� ������������ ����� ������,
// ����������� ������� ������� ��������� ����.
// ����� ������ ������������� ��������� �������:
// - GetSize � ��������� ������� ������� (���������� ���������, ��� ������� �������� ������);
// - SetSize(int size, int grow = 1) � ��������� ������� �������
//   (���� �������� size ������ ����������� ������� �������,
//   �� ���������� �������������� ���� ������, ���� ���, �� ������� �������� �������� � ������ �������������);
//   �������� grow ���������� ��� ������ ���������� ��������� ���������� �������� ������,
//   ���� ���������� ��������� ����������� ������� ������ �������.
//   ��������, SetSize(5, 5); ��������, ��� ��� ���������� 6-�� �������� ������ ������� ���������� ������ 10,
//   ��� ���������� 11-�� - 15 � �. �.;
// - GetUpperBound - ��������� ���������� ����������� ������� � �������.
//   ��������, ���� ��� ������� ������� 10, �� ���������� � ���� 4 ��������, �� ������� ������ 3;
// - IsEmpty - ������ ����?;
// - FreeExtra - ������� �������� ������ (���� ���������� ����������� �������);
// - RemoveAll - ������� ���;
// - GetAt - ��������� ������������� �������� (�� �������);
// - SetAt � ��������� ������ �������� ��� ������������� ��������
//   (������ �������� ������ ���� ������ �������� ������� �������);
// - operator [] � ��� ���������� ���� ���������� �������;
// - Add � ���������� �������� � ������
//   (��� ������������� ������ ������������� �� �������� grow ������� SetSize);
// - Append � ��������� ���� ��������;
// - operator =;
// - GetData � ��������� ������ ������� � �������;
// - InsertAt � ������� ��������(-��) � �������� �������;
// - RemoveAt � �������� ��������(-��) � �������� �������.

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

	cout << "����� \"GetSize\":\n";
	cout << test.GetSize() << endl << endl;

	test.Add(1);
	test.Add(2);
	test.Add(3);
	cout << "����� \"Add\":\n";
	cout << test << endl << endl;

	cout << "����� \"GetUpperBound\":\n";
	cout << test.GetUpperBound() << endl << endl;

	cout << "����� \"IsEmpty\":\n";
	cout << boolalpha << test.IsEmpty() << endl << endl;

	cout << "����� \"GetSize\" (���������� ���������� ��������� �������, ��� ������� �������� ������):\n";
	cout << test.GetSize() << endl << endl;

	test.SetSize(5, 5);
	cout << "����� \"SetSize\" (������������� ������ ������� 5):\n";
	cout << test.GetSize() << endl << endl;

	test.SetAt(3, 4);
	test.SetAt(4, 5);
	cout << "����� \"SetAt\" (������������� �������� 4 � 5):\n";
	cout << test << endl << endl;

	cout << "����� \"FreeExtra\" (������������� ������ 10, ���������� ��� ������):\n";
	test.SetSize(10, 5);
	test.FreeExtra();
	cout << test.GetSize() << endl << endl;

	cout << "����� \"GetAt\" (�������� �������� 3-�� ��������):\n";
	try {
		cout << test.GetAt(2) << endl << endl;	
	}
	catch (int ex) {
		cout << "Error: The element with index " << ex << " does not exist" << endl << endl;
	}

	cout << "����� \"operator[]\" (�������� �������� 3-�� ��������):\n";
	try {
			cout << test[2] << endl << endl;
	}
	catch (int ex) {
		cout << "Error: The element with index " << ex << " does not exist" << endl << endl;
	}

	Array<int> test2;
	test2 = test;
	cout << "����� \"operator=\" (������� ������ ������ � ���������� �������.)\n";
	cout << test2 << endl << endl;

	cout << "����� \"GetData\" (�������� ����� �������):\n";
	cout << test.GetData() << endl << endl;

	cout << "����� \"Append\" (��������� � ������� ������� ������):\n";
	test.Append(test2);
	cout << test << endl << endl;

	cout << "����� \"InsertAt\" (�������� �� ������ ������� ����� 256):\n";
	test.InsertAt(2, 256);
	cout << test << endl << endl;

	cout << "����� \"RemoveAt\" (������ �� ������ ������� ����� 256):\n";
	test.RemoveAt(2);
	cout << test << endl << endl;

	return 0;
}