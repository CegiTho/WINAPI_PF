#pragma once

class TextType : public TextCellSelect
{
private:
	HFONT font;

	map<string,char> key;


public:
	TextType(TextCell* menu);
	~TextType();

	void Update();
	void Render(HDC hdc);

	virtual void Select() override;
	virtual void Move() override;
	virtual void Init() override;
	


};

