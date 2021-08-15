#include "Framework.h"

Circle::Circle()
    :center(0,0),radius(0)
{
}

Circle::Circle(Vector2 center, double radius)
    :center(center),radius(radius)
{
}

Circle::~Circle()
{
}

void Circle::Render(HDC hdc)
{
    Ellipse(hdc,
        (int)Left(), (int)Top(), (int)Right(), (int)Bottom()
    );
}

bool Circle::Collision(Vector2 pos)
{
    double x = center.x - pos.x;
    double y = center.y - pos.y;

    return radius * radius > x * x + y * y ? false : true;
}

bool Circle::Collision(Line* line)
{


    return false;
}

bool Circle::Collision(Circle* circle)
{
    Vector2 distance = this->center - circle->Center();
    double path = this->radius + circle->Radius();

    return distance.Length() < path ? true : false;
}

bool Circle::Collision(Rect* rect)
{
    return rect->Collision(this);
}

void Circle::Set(Vector2 center, double radius)
{
    this->center = center;
    this->radius = radius;
}
