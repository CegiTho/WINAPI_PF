#pragma once

class ShadeManager
{
private:
	vector<Shade*> shade;

	STAGE_NUM stage;

	HDC memDC;
	HBITMAP bitmap;

	HDC alphaMemDC;
	HBITMAP alphaBitmap;

	HBRUSH stageColor;

	Vector2* lSource;
	double constant;

	BLENDFUNCTION blendFunc;

public:
	ShadeManager(STAGE_NUM num, Vector2 lSource);
	ShadeManager(STAGE_NUM num, double constant);
	~ShadeManager();

	void CreateAlphaDC(STAGE_NUM num);
	void Update();
	void Render(HDC hdc);		//BG���� �Լ��� DC�� �޹�� �׸� ������ ȣ��

	void AlphaRender();	

	void SetShade(T_Object* objects);


};


