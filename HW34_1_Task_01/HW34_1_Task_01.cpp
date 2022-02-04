// »спользу€ пон€тие множественного наследовани€,
// разработайте класс Ђќкружность, вписанна€ в квадратї.

#include <iostream>
using namespace std;

class Square {
    float Side;
public:
    Square(float side) : Side(side) {}
};

class Circle {
    float Radius;
public:
    Circle(float radius) : Radius(radius) {}
    float getRadius() { return Radius; }
};

class CircleInSquare : public Circle, public Square {
public:
    CircleInSquare(float radius) : Square(radius * 2), Circle(radius) {}
};

int main()
{
    float r = 10;
    float a = r * 2;
    Square S = Square(a);
    CircleInSquare CS = CircleInSquare(r);
    cout << "R = " << CS.getRadius() << endl;
    
    return 0;
}