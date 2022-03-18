#pragma once

class TextCellSelect
{
protected:
	TextCell* menu;

	Rect* visualBar;
	vector<Triangle*> deco;
	Vector2 offset;

	HBRUSH color;
	HPEN edge;

	int menuIndex;
	bool selected;

	bool isActive;

public:
	TextCellSelect() {};
	TextCellSelect(TextCell* menu);
	~TextCellSelect();

	void Update();
	void Render(HDC hdc);

	virtual void Select();
	virtual void Move();
	virtual void Init();

	void SetActive(bool value) { isActive = value; }


};
