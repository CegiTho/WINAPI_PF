#pragma once

class TextCell
{
private:
	vector<string> renderMenu;
	vector<string> tags;

	vector<double> yLevel;	//각 메뉴 center의 y값

	int fontHeight;
	int ascent;	//윗줄간격
	int decent;	//아랫줄간격

	Vector2 hidedPos;
	Vector2 activePos;
	Vector2 targetPos;

	Rect* rect;

	HFONT font;

	int menuIndex;

	bool isActive;
	bool isMove;
	bool isSelected;
	bool isEnd;
	bool isVerticalMove;

public:
	TextCell(vector<string> renderMenu, vector<string> tags);
	~TextCell();

	void Update();
	void Render(HDC hdc);

	void Hide();
	void Out();

	void HoriMove();
	void VertMove();

	void SetSelected(bool value) { isSelected = value; }
	void SetMove(bool value) { isMove = value; }
	void SetActive(bool value) { isActive = value; }
	void SetVertical(bool value) { isVerticalMove = value; }

	bool GetSelected() { return isSelected; }
	bool GetMove() { return isMove; }
	bool GetEnd() { return isEnd; }
	bool GetActive() { return isActive; }
	bool GetVertical() { return isVerticalMove; }

	int GetMenuIndex() { return menuIndex; }
	Rect* GetRect() { return rect; }
	vector<double> GetYLevel() { return yLevel; }
	vector<string> GetTags() { return tags; }
	double GetTotalHeight() { return fontHeight + ascent + decent; }

	void Init();
};

