// —оздайте класс очереди с приоритетами дл€ работы с целыми значени€ми.
// “ребуетс€ создать реализации дл€ типичных операций над элементами очереди:
// - IsEmpty Ц проверка очереди на пустоту
// - IsFull Ц проверка очереди на заполнение
// - InsertWithPriority Ц добавление элемента c приоритетом в очередь
// - PullHighestPriorityElement Ц удаление элемента с самым высоким приоритетом из очереди
// - Peek Ц возврат самого большого по приоритету элемента. ќбращаем ваше внимание, что элемент не удал€етс€ из очереди.
// - Show Ц отображение всех элементов очереди на экран. ѕрипоказе элемента также необходимо отображать приоритет.
//
// »змените класс из задани€ 2 на шаблонный класс.

#include <iostream>
#include <string.h>
#include <time.h>
using namespace std;

template <typename T>
class QueuePriority
{
	T* Wait;
	int* Pri;
	int MaxQueueLength;
	int QueueLength;
public:
	QueuePriority(int m);
	~QueuePriority();
	bool IsEmpty();
	bool IsFull();
	void InsertWithPriority(T c, int p);
	T PullHighestPriorityElement();
	T Peek();
	void Show();
	void Clear();
	int GetCount();
};
template <typename T>
QueuePriority<T>::QueuePriority(int m)
{
	MaxQueueLength = m;
	Wait = new T[MaxQueueLength];
	Pri = new int[MaxQueueLength];
	QueueLength = 0;
}
template <typename T>
QueuePriority<T>::~QueuePriority()
{
	delete[]Wait;
	delete[]Pri;
}
template <typename T>
bool QueuePriority<T>::IsEmpty()
{
	return QueueLength == 0;
}
template <typename T>
bool QueuePriority<T>::IsFull()
{
	return QueueLength == MaxQueueLength;
}
template <typename T>
void QueuePriority<T>::InsertWithPriority(T c, int p)
{
	if (!IsFull()) {
		Wait[QueueLength] = c;
		Pri[QueueLength] = p;
		QueueLength++;
	}
}
template <typename T>
T QueuePriority<T>::PullHighestPriorityElement()
{
	if (!IsEmpty()) {
		int max_pri = Pri[0];
		int pos_max_pri = 0;
		for (int i = 1; i < QueueLength; i++)
			if (max_pri < Pri[i]) {
				max_pri = Pri[i];
				pos_max_pri = i;
			}
		T temp1 = Wait[pos_max_pri];
		int temp2 = Pri[pos_max_pri];
		for (int i = pos_max_pri; i < QueueLength - 1; i++) {
			Wait[i] = Wait[i + 1];
			Pri[i] = Pri[i + 1];
		}
		QueueLength--;
		return temp1;
	}
	else return -1;
}
template <typename T>
T QueuePriority<T>::Peek()
{
	if (!IsEmpty()) {
		int max_pri = Pri[0];
		int pos_max_pri = 0;
		for (int i = 1; i < QueueLength; i++)
			if (max_pri < Pri[i]) {
				max_pri = Pri[i];
				pos_max_pri = i;
			}
		T temp1 = Wait[pos_max_pri];
		return temp1;
	}
	else return -1;
}
template <typename T>
void QueuePriority<T>::Show() {
	cout << "\n-----------------------------------\n";
	for (int i = 0; i < QueueLength; i++) {
		cout << Wait[i] << " - " << Pri[i] << "\n\n";
	}
	cout << "\n-----------------------------------\n\n";
}
template <typename T>
void QueuePriority<T>::Clear()
{
	QueueLength = 0;
}
template <typename T>
int QueuePriority<T>::GetCount()
{
	return QueueLength;
}


void main()
{
	srand(time(0));

	QueuePriority<int> QUP(25);

	for (int i = 0; i < 5; i++) {
		QUP.InsertWithPriority(rand() % 100, rand() % 12);
	}

	QUP.Show();

	cout << QUP.Peek() << endl;

	QUP.PullHighestPriorityElement();

	QUP.Show();
}