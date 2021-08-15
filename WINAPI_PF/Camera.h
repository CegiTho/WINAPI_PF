#pragma once

class Camera
{
private:
	Camera();
	~Camera();

	Rect* rect;
	double speed;

	Rect* target;
	Vector2 offset;

	double left;
	double right;
	double top;
	double bottom;



public:
	static Camera* Get()
	{
		static Camera instance;
		return &instance;
	}

	void Update();

	Vector2 Pos() { return rect->center; }
	void SetTarget(Rect* value) { target = value; }

	void SetMapSize(double left, double right, double top, double bottom);


};


