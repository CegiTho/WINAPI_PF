#pragma once

/*
Light gradient
Curtain : 상수기울기
Spot : 광원 존재. 발산형 

*/


class Shade
{
private:
	T_Object* object;
	Rect* rect;

	vector<POINT*> points;

	map<PointSeq, POINT> projection;
	POINT* shadeEdge;
	PointSeq failedPoint_1;
	PointSeq failedPoint_2;

	Vector2* lSource;
	double constant;

	HBRUSH color;
	HPEN edge;

	bool isStatic;

public:
	
	Shade(Rect* rect,double constant, STAGE_NUM stage);
	Shade(Rect* rect,Vector2* lSource, STAGE_NUM stage);
	~Shade();

	void AlphaColor(STAGE_NUM stage);

	void CreateShade();

	void Update();
	void Render(HDC hdc);

	void ProjectionUpdate();
	void SelectEdge();

	POINT Direction(POINT origin,double inclination,double length);
	Vector2 Direction(Vector2 origin,double inclination,double length);


};

