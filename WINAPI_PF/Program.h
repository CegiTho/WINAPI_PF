#pragma once

class Program
{
private:



public:
	Program(HWND hWindow);
	~Program();

	void Update();
	void Render(HDC hdc);

	void LoadSound();

	void RenderMousePos(HDC hdc);

};
