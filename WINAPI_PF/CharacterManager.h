#pragma once

//¾ë Scene¸¶´Ù ÇÏ³ª¾¿ ÁÙ°Å¶ó¼­ ½Ì±ÛÅæ ¾È¾¸
class CharacterManager
{
private:
	vector<Character*> characters;
	


public:
	CharacterManager();
	~CharacterManager();

	void Update();
	void Render(HDC hdc);

	void PlusCharacter(Name name);

	vector<Character*> GetObj() { return characters; }
	void SetCharacter(Character* character) { characters.emplace_back(character); }



};



