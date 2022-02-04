// —оздайте шаблонный класс двусв€зного списка дл€ работы с целыми значени€ми.
// “ребуетс€ создать реализации дл€ типичных операций над элементами:
// AddToHead Ц добавление элемента в голову;
// AddToTail Ц добавление элемента в хвост;
// DeleteFromHead Ц удаление элемента из головы;
// DeleteFromTail Ц удаление элемента из хвоста;
// DeleteAll Ц удаление всех элементов;
// Show Ц отображение всех элементов списка на экран.

// ƒобавить в класс из задани€ 1 следующие функции:
// вставка элемента в заданную позицию,
// удаление элемента по заданной позиции,
// поиск заданного элемента
// (функци€ возвращает позицию найденного элемента в случае успеха или NULL в случае неудачи),
// поиск и замена заданного элемента
// (функци€ возвращает количество замененных элементов в случае успеха или - 1 в случае неудачи),
// переворот списка.

#include <Windows.h>
#include <iostream>
using namespace std;

class Node {
	int data;
public:
	Node* next, * prev;
	Node(int d) :data(d), next(0), prev(0) {};
	int getData() const { return data; }
	void setData(int d) { data = d; }
	friend ostream& operator<<(ostream& os, const Node& N);
};

ostream& operator<<(ostream& os, const Node& N) {
	os << N.data;
	return os;
}

class List {
	Node* head, * tail;
public:
	List() { head = tail = 0; }
	~List() { DeleteAll(); }
	//  онструктор копировани€
	List(const List& other);
	//  онструктор перемещени€
	List(List&& other) noexcept;
	// ќператор присваивани€ копированием
	List& operator=(const List& other);
	// ќператор присваивани€ перемещением
	List& operator=(List&& other);
	void AddToHead(int el);
	void AddToTail(int el);
	Node* AddressPos(int pos);
	Node* Insert(Node* before, int el);
	Node* Insert(int pos, int el);
	void DeleteFromHead();
	void DeleteFromTail();
	void DeleteAll();
	Node* Delete(Node* node);
	Node* Delete(int p);
	Node* Find(int el, Node* start = 0);
	int Replace(int el, int elnew, Node* start = 0);
	List Reverse();
	void ReverseThis();
	Node* getTail() const { return tail; };
	Node* getHead() const { return head; };
	void Show();
	friend ostream& operator<<(ostream& os, List& list);
	friend void swap(List& l, List& r);
};

List::List(const List& other) {
	head = tail = 0;
	Node* temp = other.head;
	while (temp) {
		AddToTail(temp->getData());
		temp = temp->next;
	}
}

List::List(List&& other) noexcept {
	head = other.head;
	other.head = nullptr;
	tail = other.tail;
	other.tail = nullptr;
}

List& List::operator=(const List& other) {
	List tmp(other);
	swap(*this, tmp);
	return *this;
}

List& List::operator=(List&& other) {
	swap(*this, other);
	return *this;
}

void List::AddToHead(int el) {
	Node* temp = new Node(el);
	temp->next = head;
	if (head)
		head->prev = temp;
	else
		tail = temp;
	head = temp;
}

void List::AddToTail(int el) {
	Node* temp = new Node(el);
	temp->prev = tail;
	if (tail)
		tail->next = temp;
	else
		head = temp;
	tail = temp;
}

Node* List::AddressPos(int pos) {
	if (pos < 0) { return 0; }
	int p = 0;
	Node* temp = head;
	while (temp) {
		if (!pos--) break;
		temp = temp->next;
	}
	return temp;
}

Node* List::Insert(Node* before, int el) {
	if (!before) return before;
	if (head == before) { AddToHead(el); return head; }
	Node* temp = new Node(el);
	temp->next = before;
	temp->prev = before->prev;
	before->prev = temp;
	temp->prev->next = temp;
	return temp;
}

Node* List::Insert(int pos, int el) {
	return Insert(AddressPos(pos), el);
}

void List::DeleteFromHead() {
	if (head) {
		Node* temp = head;
		head = head->next;
		if (head)
			head->prev = 0;
		else
			tail = 0;
		delete temp;
	}
}

void List::DeleteFromTail() {
	if (tail) {
		Node* temp = tail;
		tail = tail->prev;
		if (tail)
			tail->next = 0;
		else
			head = 0;
		delete temp;
	}
}

void List::DeleteAll() {
	while (head) DeleteFromHead();
}

Node* List::Delete(Node* node) {
	if (!node) return 0;
	if (head == node) { DeleteFromHead(); return head; }
	if (tail == node) { DeleteFromTail(); return 0; }
	Node* r = node->next;
	node->prev->next = node->next;
	node->next->prev = node->prev;
	delete node;
	return r;
}

Node* List::Delete(int p) {
	return Delete(AddressPos(p));
}

Node* List::Find(int el, Node* start) {
	Node* node = start ? start : head;
	while (node) {
		if (node->getData() == el) break;
		node = node->next;
	}
	return node;
}

int List::Replace(int el, int elnew, Node* start) {
	Node* node = start ? start : head;
	int count = 0;
	while (node) {
		if (node->getData() == el) {
			node->setData(elnew);
			count++;
		}
		node = node->next;
	}
	// не пон€тно, почему функци€ должна возвращать -1, а не 0, но ок, пусть будет...
	return count ? count : -1;
}

List List::Reverse() {
	List Res;
	Node* temp = head;
	while (temp) {
		Res.AddToHead(temp->getData());
		temp = temp->next;
	}
	return Res;
}

void List::ReverseThis() {
	if (!head) return;
	Node* temp = head;
	if (!head->next) return;
	while (temp) {
		swap(temp->next, temp->prev);
		temp = temp->prev;
	}
	swap(head, tail);
}

void List::Show() {
	if (!head)
		cout << "list is empty";
	else {
		Node* temp = head;
		while (temp) {
			cout << *temp << "\t";
			temp = temp->next;
		}
	}
}

ostream& operator<<(ostream& os, List& list) {
	if (!list.head)
		os << "list is empty";
	else {
		Node* temp = list.head;
		while (temp) {
			os << *temp << "\t";
			temp = temp->next;
		}
	}
	return os;
}

void swap(List& l, List& r) {
	using std::swap;
	swap(l.head, r.head);
	swap(l.tail, r.tail);
}


int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	List list;
	list.AddToTail(10);
	list.AddToTail(5);
	list.AddToHead(10);
	list.AddToHead(5);
	list.Insert(0, 100);
	Node* t = list.Insert(2, 200);
	list.Insert(t, 150);
	//list.DeleteAll();
	Node* t2 = list.AddressPos(10);
	t2 = list.Delete(t2);

	cout << list << endl;

	cout << list.Find(10) << endl;
	cout << list.Find(110) << endl;

	List list2 = list.Reverse();

	cout << list2 << endl;
	
	list.ReverseThis();
	cout << list << endl;
	cout << list.Replace(5, 50) << endl;
	cout << list << endl;
	cout << list.Replace(6, 50) << endl;
	cout << list << endl;

	return 0;
}