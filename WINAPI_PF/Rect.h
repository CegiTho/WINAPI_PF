#pragma once

class Rect : public Object
{
public:
	Vector2 center;
	Vector2 size;





	Rect();
	Rect(Vector2 center, Vector2 size);
	Rect(double left, double top, double right, double bottom);
	~Rect();

	virtual void Render(HDC hdc) override;
	void Render(HDC hdc,Vector2 size);
	void Render(HDC hdc, int left,int right,int top,int bottom);

	//======object collision======
	virtual bool Collision(Vector2 pos) override;
	virtual bool Collision(Line* line) override;
	virtual bool Collision(Circle* circle) override;
	virtual bool Collision(Rect* rect) ;
	bool Collision(OUT Rect* overlap, IN Rect* rect);
	//======object collision======

	virtual void Set(Vector2 center, double radius) override;

	void Move(double deltaX = 0.0, double deltaY = 0.0);
	void SetRect(double left, double top, double right, double bottom);
	void SetRect(Vector2 center, Vector2 size);

	double Left() { return center.x - size.x * 0.5; }
	double Right() { return center.x + size.x * 0.5; }
	double Top() { return center.y - size.y * 0.5; }
	double Bottom() { return center.y + size.y * 0.5; }
	Vector2& Center() { return center; }
	Vector2& Size() { return size; }
	Vector2 Half() { return Vector2(size.x * 0.5, size.y * 0.5); }

	Vector2 LeftTopV() { return Vector2(Left(), Top()); }
	Vector2 RightTopV() { return Vector2(Right(), Top()); }
	Vector2 LeftBottomV() { return Vector2(Left(), Bottom()); }
	Vector2 RightBottomV() { return Vector2(Right(), Bottom()); }

	POINT LeftTop() 
	{
		POINT result;
		result.x = (LONG)Left();
		result.y =  (LONG)Top(); 
		return result;
	}
	POINT RightTop() 
	{
		POINT result;
		result.x = (LONG)Right();
		result.y = (LONG)Top();
		return result;
	} 
	POINT LeftBottom() 
	{
		POINT result;
		result.x = (LONG)Left();
		result.y = (LONG)Bottom();
		return result;
	} 
	POINT RightBottom()
	{
		POINT result;
		result.x = (LONG)Right();
		result.y = (LONG)Bottom();
		return result;
	}

	double Area() { return (size.x * size.y); }

	
	//아래 두개함수는 사실 똑같은 함수임. POINT랑 Vector2가 호환이 지랄같아서 따로 만들어진것뿐임.
	Vector2 GetPoint(PointSeq tag)
	{
		switch (tag)
			{
			case LEFTTOP:
				return this->LeftTopV();
				break;
			case RIGHTTOP:
				return this->RightTopV();
				break;
			case LEFTBOTTOM:
				return this->LeftBottomV();
				break;
			case RIGHTBOTTOM:
				return this->RightBottomV();
				break;
			default:
				break;
			}
	}

	POINT GetPOINT(PointSeq tag)
	{
		switch (tag)
			{
			case LEFTTOP:
				return this->LeftTop();
				break;
			case RIGHTTOP:
				return this->RightTop();
				break;
			case LEFTBOTTOM:
				return this->LeftBottom();
				break;
			case RIGHTBOTTOM:
				return this->RightBottom();
				break;
			default:
				break;
			}
	}
	
};
