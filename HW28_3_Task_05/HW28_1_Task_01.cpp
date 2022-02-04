// ����������� ����� var - �������������� �����������.
// ������� ���������� ����� ������ �������� ������� � ���� �������� ��������� �����:
// int, double, String (������ � ��� ������� �����).
// ��������:
// void main()
// {
//     var a = 15;
//     var b = �Hello�;
//     var c = 7.8;
//     var d = �50�;
//     b = a + d;
//     b.Show(); // ������� 65
//     if (a == b) cout << �Equal\n�;
//     else cout << �Not Equal\n�;
// }
// ��� ������ var ����������: 
// - ����������� �������������� ���������: +, -, *, / , +=, -=, *=, /=
// - � ��������� ���������: <, >, <= , >= , == , != (��� ���������� �������������� ��� �������-����� ������ var)
// � ���������� ���� var � ����� ������ ������� ����� ��������� ������ ���� �������� (��� int, ��� double, ��� String).
// ��� ���������� ���������� ��������� ���������: ���� � �������� ���� �������� ���� ��������� ���� var ������,
// �� ���������� ��������� (��������������) �������� �� ������� �������� � ���� �������� ������� ��������
// � ������ ����� ����� ��������� ��������. (��� ���� �������� (� ���) ������� �������� � ����� ������� var �� ��������)
//
// ��������:
// var a = 10, b = �120�, c;
// c = a + b;
// c.Show(); //������� 130
// c = b + a;
// c.Show(); //������� �12010�
//
// ��� ���� ������ ��������* ������ ���������� ����� ������, ��������� ������ �� �������� ������ ������,
// ������� ���� �� ������ ������, ��������:
//
// var a = �Microsoft�, b = �Windows�, c;
// c = a * b;
// c.Show(); //������� �ioso�
//
// ��� ���� ������ �������� / ������ ���������� ����� ������, ��������� �� �������� ������ ������,
// ������� ��� �� ������ ������, ��������:
//
// var a = �Microsoft�, b = �Windows�, c;
// c = a / b;
// c.Show(); //������� �Mcrft�
//
// ���������� ��� ������ *= � /=
// �������� � ����� var �������������� � �����: int, double, char*.


#include <iostream>
#include <string>
using namespace std;

const string operator * (const string& leftStr, const string& rightStr);
const string operator / (const string& leftStr, const string& rightStr);
const string operator - (const string& leftStr, const string& rightStr);

class var
{
private:
    int* pInt;
    double* pDouble;
    string* pStr;
    int typeID; // 0 - int, 1 - double, 2 - string
public:
    var() { typeID = -1; pInt = NULL; pDouble = NULL; pStr = NULL; };
    var(const int& number);
    var(const double& number);
    var(const char* str) : var(string(str)) {}
    var(const string& str);
    void Show();
    operator int()const;
    operator double()const;
    operator char* ()const;
    var& operator = (const var& rightVar);
    var& operator = (const int& number);
    var& operator = (const double& number);
    var& operator = (const string& str);
    const var operator + (const var& rightVar);
    const var operator - (const var& rightVar);
    const var operator * (const var& rightVar);
    const var operator / (const var& rightVar);
    var& operator += (const var& rightVar);
    var& operator -= (const var& rightVar);
    var& operator *= (const var& rightVar);
    var& operator /= (const var& rightVar);
    bool operator < (const var& rightVar);
    bool operator > (const var& rightVar);
    bool operator <= (const var& rightVar);
    bool operator >= (const var& rightVar);
    bool operator == (const var& rightVar);
    bool operator != (const var& rightVar);
};

var::var(const int& number)
{
    typeID = 0;
    pInt = new int(number);
}

var::var(const double& number)
{
    typeID = 1;
    pDouble = new double(number);
}

var::var(const string& str)
{
    typeID = 2;
    pStr = new string(str);
}

void var::Show()
{
    switch (typeID)
    {
    case 0: cout << *pInt; return;
    case 1: cout << *pDouble; return;
    case 2: cout << *pStr; return;
    }
    cout << "NULL";
}

var::operator int() const
{
    switch (typeID)
    {
    case 0: return *pInt;
    case 1: return (int)*pDouble;
    case 2: return atoi((*pStr).c_str());
    }
    return 0;
}

var::operator double() const
{
    switch (typeID)
    {
    case 0: return (double)*pInt;
    case 1: return *pDouble;
    case 2: return (double)atof((*pStr).c_str());
    }
    return 0;
}

var::operator char* () const
{
    switch (typeID) {
    case 0: {
        char* tmpStr = new char[17];
        return itoa(*pInt, tmpStr, 10); }
    case 1: {
        char* tmpStr = new char[80];
        sprintf(tmpStr, "%lf", *pDouble);
        return tmpStr; }
    case 2:
        char* cstr = new char[(*pStr).length() + 1];
        strcpy(cstr, (*pStr).c_str());
        return cstr;
    }
    return NULL;
}

const var var::operator + (const var& rightVar)
{
    switch (typeID)
    {
    case 0:
        return var(*pInt + (int)rightVar);
    case 1:
        return var(*pDouble + (double)rightVar);
    case 2:
        return var(*pStr + (char*)rightVar);
    }
    return *this;
}

const var var::operator - (const var& rightVar)
{
    switch (typeID)
    {
    case 0:
        return var(*pInt - (int)rightVar);
    case 1:
        return var(*pDouble - (double)rightVar);
    case 2:
        return var(*pStr - (char*)rightVar);
    }
    return *this;
}

const var var::operator * (const var& rightVar)
{
    switch (typeID)
    {
    case 0:
        return var(*pInt * (int)rightVar);
    case 1:
        return var(*pDouble * (double)rightVar);
    case 2:
        return var(*pStr * (char*)rightVar);
    }
    return *this;
}

const var var::operator / (const var& rightVar)
{
    switch (typeID)
    {
    case 0:
        return var(*pInt / (int)rightVar);
    case 1:
        return var(*pDouble / (double)rightVar);
    case 2:
        return var(*pStr / (char*)rightVar);
    }
    return *this;
}

var& var::operator += (const var& rightVar)
{
    switch (typeID)
    {
    case 0:
        *pInt = *pInt + (int)rightVar;
        return *this;
    case 1:
        *pDouble = *pDouble + (double)rightVar;
        return *this;
    case 2:
        *pStr = *pStr + (char*)rightVar;
        return *this;
    }
    return *this;
}

var& var::operator -= (const var& rightVar)
{
    switch (typeID)
    {
    case 0:
        *pInt = *pInt - (int)rightVar;
        return *this;
    case 1:
        *pDouble = *pDouble - (double)rightVar;
        return *this;
    case 2:
        *pStr = *pStr - (char*)rightVar;
        return *this;
    }
    return *this;
}

var& var::operator *= (const var& rightVar)
{
    switch (typeID)
    {
    case 0:
        *pInt = *pInt * (int)rightVar;
        break;
    case 1:
        *pDouble = *pDouble * (double)rightVar;
        break;
    case 2:
        *pStr = *pStr * (char*)rightVar;
        break;
    }
    return *this;
}

var& var::operator /= (const var& rightVar)
{
    switch (typeID)
    {
    case 0:
        *pInt = *pInt / (int)rightVar;
        break;
    case 1:
        *pDouble = *pDouble / (double)rightVar;
        break;
    case 2:
        *pStr = *pStr / (char*)rightVar;
        break;
    }
    return *this;
}

bool var::operator > (const var& rightVar)
{
    switch (typeID)
    {
    case 0:
        return *pInt > (int)rightVar;
    case 1:
        return *pDouble > (double)rightVar;
    case 2:
        return *pStr > (char*)rightVar;
    }
    return false;
}

bool var::operator < (const var& rightVar)
{
    switch (typeID)
    {
    case 0:
        return *pInt < (int)rightVar;
    case 1:
        return *pDouble < (double)rightVar;
    case 2:
        return *pStr < (char*)rightVar;
    }
    return false;
}

bool var::operator == (const var& rightVar)
{
    switch (typeID)
    {
    case 0:
        return *pInt == (int)rightVar;
    case 1:
        return *pDouble == (double)rightVar;
    case 2:
        return *pStr == (char*)rightVar;
    }
    return false;
}

bool var::operator <= (const var& rightVar)
{
    return(!(*this > rightVar));
}

bool var::operator >= (const var& rightVar)
{
    return(!(*this < rightVar));
}

bool var::operator != (const var& rightVar)
{
    return(!(*this == rightVar));
}
var& var::operator =(const var& rightVar)
{
    if (this == &rightVar)
    {
        return *this;
    }
    switch (typeID)
    {
    case 0:
        delete pInt;
        break;
    case 1:
        delete pDouble;
        break;
    case 2:
        delete pStr;
        break;
    }
    typeID = -1;
    switch (rightVar.typeID)
    {
    case 0:
        pInt = new int(*(rightVar.pInt));
        break;
    case 1:
        pDouble = new double(*(rightVar.pDouble));
        break;
    case 2:
        pStr = new string(*(rightVar.pStr));
        break;
    }
    typeID = rightVar.typeID;
    return *this;
}
var& var::operator = (const int& number)
{
    switch (typeID)
    {
    case 0:
        delete pInt;
        break;
    case 1:
        delete pDouble;
        break;
    case 2:
        delete pStr;
        break;
    }
    typeID = 0;
    pInt = new int(number);
    return *this;
}

var& var::operator = (const double& number)
{
    switch (typeID)
    {
    case 0:
        delete pInt;
        break;
    case 1:
        delete pDouble;
        break;
    case 2:
        delete pStr;
        break;
    }
    typeID = 1;
    pDouble = new double(number);
    return *this;
}

var& var::operator = (const string& str)
{
    switch (typeID)
    {
    case 0:
        delete pInt;
        break;
    case 1:
        delete pDouble;
        break;
    case 2:
        delete pStr;
        break;
    }
    typeID = 2;
    pStr = new string(str);
    return *this;
}

const string operator * (const string& leftStr, const string& rightStr)
{
    string tmp;
    string::const_iterator i;
    string::const_iterator j;
    for (i = leftStr.cbegin(); i != leftStr.cend(); i++)
        for (j = rightStr.cbegin(); j != rightStr.cend(); j++)
            if (*i == *j)
            {
                tmp.push_back(*i);
                break;
            }
    return tmp;
}
const string operator / (const string& leftStr, const string& rightStr)
{
    bool flag = true;
    string tmp;
    string::const_iterator i;
    string::const_iterator j;
    for (i = leftStr.cbegin(); i != leftStr.cend(); i++)
    {
        for (j = rightStr.cbegin(); j != rightStr.cend(); j++)
        {
            if (*i == *j)
            {
                flag = false;
                break;
            }
        }
        if (!flag)
        {
            flag = true;
            continue;
        }
        tmp.push_back(*i);
    }
    return tmp;
}

const string operator - (const string& leftStr, const string& rightStr)
{
    return leftStr;
}

void test1()
{
    var a = 10, b = "120", c;
    c = a + b;
    c.Show();       // ������� 130
    cout << "  ";
    c = b + a;
    c.Show(); // ������� �12010�
}

void test2()
{
    var a = "Microsoft", b = "Windows", c;
    c = a * b;
    c.Show();       // ������� �ioso�
}

void test3()
{
    var a = "Microsoft", b = "Windows", c;
    c = a / b;
    c.Show();       // ������� �Mcrft�
}

int main()
{
    var a = 15;
    var b = "Hello";
    var c = 7.8;
    var d = "50";
    b = a + d;
    b.Show();       // ������� 65
    if (a == b) cout << "\nEqual\n"; else cout << "\nNot Equal\n";
    cout << endl;
    test1();
    cout << endl;
    test2();
    cout << endl;
    test3();
    cout << endl;

    return 0;
}