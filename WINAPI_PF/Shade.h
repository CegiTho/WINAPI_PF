#pragma once

/*
Light gradient
Curtain : �������
Spot : ���� ����. �߻��� 

*/


class Shade
{
private:
	T_Object* object;

	vector<POINT*> points;


	Vector2* lSource;
	double constant;

	HBRUSH color;

	bool isStatic;

public:
	Shade(T_Object* obj,Vector2* lSource);
	Shade(T_Object* obj,double constant);
	~Shade();

	void CreateCurtainShade();
	void CreateSpotShade();

	void Update();
	void Render(HDC hdc);

	void CurtainUpdate();
	void SpotUpdate();

	POINT Direction(POINT origin,double inclination,double length);


};

