#pragma once

class PercentType : public TextCellSelect
{
private:
	Rect* rect;
	Line* line;

	vector<string> volMem;
	HFONT font;

public:
	PercentType(TextCell* menu);
	~PercentType();

	void Update();
	void Render(HDC hdc);

	virtual void Select() override;
	virtual void Move() override;
	virtual void Init() override;

	void VolumeUpdate();
};


