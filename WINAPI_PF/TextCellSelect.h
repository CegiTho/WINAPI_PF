#pragma once

class TextCellSelect
{
private:
	TextCell* menu;

	Rect* visualBar;

	HBRUSH color;
	HPEN edge;

	int menuIndex;
	bool selected;


public:
	TextCellSelect(TextCell* menu);
	~TextCellSelect();

	void Update();
	void Render(HDC hdc);

	void Select();
	void Move();

};
