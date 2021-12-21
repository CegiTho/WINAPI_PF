#pragma once

class ShadeManager
{
private:
	vector<Shade*> shade;
	Vector2 mapSize;

	STAGE_NUM stage;

	HBRUSH stageColor;

	Vector2* lSource;
	double constant;


public:
	ShadeManager(STAGE_NUM num, Vector2 lSource);
	ShadeManager(STAGE_NUM num, double constant);
	~ShadeManager();

	void LoadDCSize(STAGE_NUM num);

	void CreateAlphaDC(STAGE_NUM num);
	void Update();
	void Render(HDC hdc);		//BG관련 함수의 DC에 뒷배경 그린 다음에 호출

	void SetShade(T_Object* objects);
};


