#pragma once

class TextCell
{
private:
	vector<string> menu;

	vector<double> yLevel;	//각 메뉴 center의 y값
	Vector2 offset;
	int fontHeight;
	int ascent;	//윗줄간격
	int decent;	//아랫줄간격

	Vector2 hidedPos;
	Vector2 activePos;
	Vector2 targetPos;

	Rect* rect;

	HFONT font;

	int menuIndex;

	bool isHided;
	bool isActive;
	bool isMove;
	bool isSelected;
	bool isVerticalMove;

	HPEN test;
	vector<Line*> testLine;

public:
	TextCell(vector<string> menu);
	~TextCell();

	void Update();
	void Render(HDC hdc);

	void Hide();
	void Out();

	void HoriMove();
	void VertMove();

	void SetSelected(bool value) { isSelected = value; }
	void SetMove(bool value) { isMove = value; }

	bool GetSelected() { return isSelected; }
	bool GetMove() { return isMove; }
	Rect* GetRect() { return rect; }
	vector<double> GetYLevel() { return yLevel; }
	vector<string> GetMenu() { return menu; }
	double GetTotalHeight() { return fontHeight + ascent + decent; }

	void SetVerticalMove(bool value) { isVerticalMove = value; }
	bool GetVerticalMove() { return isVerticalMove; }
	int GetMenuIndex() { return menuIndex; }

};

