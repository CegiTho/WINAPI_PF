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

	vector<POINT*> points;


	Vector2* lSource;
	double constant;

	HBRUSH color;
	HPEN edge;

	bool isStatic;

public:
	Shade(T_Object* obj,Vector2* lSource, STAGE_NUM stage);
	Shade(T_Object* obj,double constant, STAGE_NUM stage);
	~Shade();

	void AlphaColor(STAGE_NUM stage);

	void CreateCurtainShade();
	void CreateSpotShade();

	void Update();
	void Render(HDC hdc);

	void CurtainUpdate();
	void SpotUpdate();

	POINT Direction(POINT origin,double inclination,double length);


};

