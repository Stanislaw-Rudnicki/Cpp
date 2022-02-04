// �������� ��������� ����� ������� ������� ��� ������ � ������ ����������.
// ��������� ������� ���������� ��� �������� �������� ��� ����������:
// - IsEmpty � �������� ������� �� �������
// - IsFull � �������� ������� �� ����������
// - Enqueue � ���������� �������� � �������
// - Dequeue � �������� �������� �� �������
// - Show � ����������� ���� ��������� ������� �� �����

#include <iostream>
#include <string.h>
#include <time.h>
using namespace std;

template <typename T>
class Queue
{
	T* Wait;
	int MaxQueueLength;
	int QueueLength;
public:
	Queue(int m);
	~Queue();
	bool IsEmpty();
	bool IsFull();
	void Enqueue(T c);
	T Dequeue();
	void Show();
	void Clear();
	int GetCount();
};
template <typename T>
Queue<T>::Queue(int m)
{
	MaxQueueLength = m;
	Wait = new T[MaxQueueLength];
	QueueLength = 0;
}
template <typename T>
Queue<T>::~Queue()
{
	delete[]Wait;
}
template <typename T>
bool Queue<T>::IsEmpty()
{
	return QueueLength == 0;
}
template <typename T>
bool Queue<T>::IsFull()
{
	return QueueLength == MaxQueueLength;
}
template <typename T>
void Queue<T>::Enqueue(T c)
{
	if (!IsFull())
		Wait[QueueLength++] = c;
}
template <typename T>
T Queue<T>::Dequeue()
{
	if (!IsEmpty()) {
		T temp = Wait[0];
		for (int i = 1; i < QueueLength; i++)
			Wait[i - 1] = Wait[i];
		QueueLength--;
		return temp;
	}
	else
		return -1;
}
template <typename T>
void Queue<T>::Show() {
	cout << "\n-----------------------------------\n";
	for (int i = 0; i < QueueLength; i++) {
		cout << Wait[i] << " ";
	}
	cout << "\n-----------------------------------\n\n";
}
template <typename T>
void Queue<T>::Clear()
{
	QueueLength = 0;
}
template <typename T>
int Queue<T>::GetCount()
{
	return QueueLength;
}

void main()
{
	srand(time(0));

	Queue<int> QU(25);
	for (int i = 0; i < 5; i++) {
		QU.Enqueue(rand() % 50);
	}

	QU.Show();

	cout << QU.Dequeue() << endl;

	QU.Show();
}