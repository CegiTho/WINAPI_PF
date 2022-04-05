#pragma once

class RectListType : public TextCellSelect
{
private:
	vector<Rect*> list;
	Rect* leftSide;

	HFONT font;
	HBRUSH stageColor;
	HPEN stageEdge;
	int stage;

	double normalSize;
	double highlightedSize;
	
public:
	RectListType(TextCell* menu);
	~RectListType();

	void Update();
	void Render(HDC hdc);

	virtual void Select() override;
	virtual void Move() override;
	virtual void Init() override;

};

