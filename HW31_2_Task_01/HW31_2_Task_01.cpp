// ����������� ���� ������ ��� �� �������� ���������� � ������� ��������� ������.
// ������ ����� ������� ����� ����������, ��������� ���� � ������ ��������������.
// ���� ��������� ����������� � ������ ���, �� � ������ ���������� ����� ����,
// � � ������ ������ �� ��������������;
// ���� ���, �� ������ ��������� � ������������ ������.
// ���������� ����� ����������� ��������� ��������:
// - ������ ���������� ���� ������ (�� ������� ����� � ������ ��������������, ���������� �� ����);
// - ���������� ������ �� ��������� ������;
// - ���������� ������ �� ��������� �������.


#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <string>
#include <iomanip>

using namespace std;

class Node {
    string violation;
public:
    Node* next;
    Node(string str) :violation(str), next(0) {};
    string getViolation() const { return violation; }
    void setViolation(string str) { violation = str; }
    friend ostream& operator<<(ostream& os, const Node& Obj);
};

ostream& operator<<(ostream& os, const Node& Obj) {
    os << Obj.violation << endl;
    return os;
}

class List {
    Node* begin, * end;
public:
    List() { begin = end = 0; }
    ~List() { Clear(); }
    List(const List& other);
    List& operator=(const List& other);
    void Push(Node* n);
    void Push(string);
    void Clear();
    void PushHead(string);
    friend ostream& operator<<(ostream& os, const List& list);
};

List::List(const List& other) {
    begin = end = 0;
    Node* temp = other.begin;
    while (temp) {
        Push(temp->getViolation());
        temp = temp->next;
    }
}

List& List::operator=(const List& other) {
    List tmp(other);
    swap(*this, tmp);
    return *this;
}

void List::Push(Node* n) {
    if (!end)
        begin = n;
    else
        end->next = n;
    end = n;
}

void List::Push(string str) {
    Push(new Node(str));
}

void List::Clear() {
    Node* temp = 0;
    while (begin) {
        temp = begin;
        begin = begin->next;
        delete temp;
    }
    end = 0;
}

void List::PushHead(string str) {
    Node* temp = new Node(str);
    temp->next = begin;
    begin = temp;
    if (!end)
        end = begin;
}

ostream& operator<<(ostream& os, const List& list) {
    if (!list.begin)
        os << "";
    else {
        int count = 1;
        Node* temp = list.begin;
        while (temp) {
            os << setw(3) << right << count++ << " " << *temp;
            temp = temp->next;
        }
        os << endl;
    }
    return os;
}


class TreeNode {
    string car;
    List violations;
public:
    TreeNode* left, * right, * parent;
    TreeNode(string str, string violation) : car(str), left(0), right(0), parent(0) { violations.PushHead(violation); };
    string getCar() const { return car; }
    List getViolations() const { return violations; }
    void Push(string violation) { violations.PushHead(violation); }
    friend ostream& operator<<(ostream& os, const TreeNode& N);
};

ostream& operator<<(ostream& os, const TreeNode& N) {
    os << N.car;
    return os;
}


class database {
private:
    TreeNode* root;
public:
    database() { root = 0; };
    ~database() { Clear(root); };
    void Add(string, string);
    void Add(TreeNode*&, TreeNode*, string, string);
    void PrintAll(TreeNode*);
    void PrintNumber(string);
    TreeNode* PrintNumber(TreeNode*, string);
    void PrintRangeNumber(string min, string max);
    void PrintRangeNumber(TreeNode* node, string min, string max);
    TreeNode* ReturnRoot() { return root; };
    void Clear(TreeNode* temp);
};

void database::Clear(TreeNode* temp) {
    if (temp) {
        Clear(temp->left);
        Clear(temp->right);
        delete temp;
    }
}

void database::Add(TreeNode*& head, TreeNode* parent, string car, string str) {
    TreeNode* temp = new TreeNode(car, str);
    temp->left = temp->right = temp->parent = 0;
    if (!head)
        head = temp;
    else {
        if (car < head->getCar())
            Add(head->left, head, car, str);
        else if (car > head->getCar())
            Add(head->right, head, car, str);
        else
            head->Push(str);
    }
}

void database::Add(string car, string str) {
    Add(root, NULL, car, str);
}

void database::PrintAll(TreeNode* temp) {
    if (temp) {
        PrintAll(temp->left);
        cout << "����� ������: " << temp->getCar() << endl;
        cout << "���������: " << endl;
        cout << temp->getViolations();
        PrintAll(temp->right);
    }
}

TreeNode* database::PrintNumber(TreeNode* node, string input) {
    if (!node)
        return 0;
    if (input == node->getCar())
        return node;
    else if (input < node->getCar())
        return  PrintNumber(node->left, input);
    else
        return  PrintNumber(node->right, input);
}

void database::PrintNumber(string input) {
    TreeNode* node = PrintNumber(root, input);
    if (!node)
        cout << "Not found." << endl;
    else {
        cout << "����� ������: " << node->getCar() << endl;
        cout << "���������: " << endl;
        cout << node->getViolations();
    }
}

void database::PrintRangeNumber(TreeNode* node, string min, string max) {
    if (!node)
        return;
    if (node->getCar() > min)
        PrintRangeNumber(node->left, min, max);
    if (node->getCar() >= min && node->getCar() <= max)
        PrintNumber(node->getCar());
    if (node->getCar() < max)
        PrintRangeNumber(node->right, min, max);
}

void database::PrintRangeNumber(string min, string max) {
    PrintRangeNumber(root, min, max);
}


int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    database bd;

    bd.Add("AM9999CH", "��������� �");
    bd.Add("AM9999CH", "��������� �");
    bd.Add("AM9999CH", "��������� �");
    bd.Add("AA2099AB", "��������� �");
    bd.Add("BH1000CI", "��������� �");
    bd.Add("AM9333BA", "��������� �");
    bd.Add("AM9055CT", "��������� �");
    bd.Add("AM9055CT", "��������� �");

    cout << "������ ���������� ���� ������" << endl;
    bd.PrintAll(bd.ReturnRoot());

    cout << "\n���������� ������ �� ��������� ������: BH1000CI" << endl;
    bd.PrintNumber("BH1000CI");
    
    cout << "\n���������� ������ �� ��������� �������: AA0000AA - XX9999XX" << endl;
    bd.PrintRangeNumber("AA0000AA", "XX9999XX");

    return 0;
}