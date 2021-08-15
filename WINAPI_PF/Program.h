#pragma once

class Program
{
private:
	HBITMAP hBit;



public:
	Program(HWND hWindow);
	~Program();

	void Update();
	void Render(HDC hdc);

	static HDC backBuffer;


};
