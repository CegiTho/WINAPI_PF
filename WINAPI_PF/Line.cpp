#include "Framework.h"
#include "Object.h"
Line::Line()
    :start(0,0),end(0,0)
{
}

Line::Line(Vector2 start, Vector2 end)
    :start(start),end(end)
{
}

Line::~Line()
{
}

void Line::Render(HDC hdc)
{
    MoveToEx(hdc, (int)start.x, (int)start.y, nullptr);
    LineTo(hdc, (int)end.x, (int)end.y);
}

bool Line::Collision(Line* line)
{
    return this->IsBetween(line);
}

bool Line::Collision(Circle* circle)
{
    return false;
}

bool Line::Collision(Rect* rect)
{
    return false;
}

bool Line::Intersection(OUT Vector2& intersection, IN Line* line)
{


    return false;
}

bool Line::IsBetween(Line* line)
{
    Vector2 temp_1 = line->Start() - this->End();
    Vector2 temp_2 = line->End() - this->End();
    Vector2 origin = this->End() - this->Start();

    if (origin.Cross(temp_1) * origin.Cross(temp_2) < 0)
    {
        //line의 연장선은 접촉하는데 start - end 사이에는 접촉하지 않는 경우를 제외해줘야함
        temp_1 = this->Start() - line->End();
        temp_2 = this->End() - line->End();
        origin = line->End() - line->Start();

        if (origin.Cross(temp_1) * origin.Cross(temp_2) < 0)
            return true;
    }

    return false;
}
