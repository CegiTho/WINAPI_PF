#pragma once

class CharacterManager
{
private:
	vector<Character*> characters;
	


public:
	CharacterManager();
	~CharacterManager();

	void Update();
	void Render(HDC hdc);

	T_Object* PlusCharacter(Name name,Vector2 pos);

	vector<Character*> GetObj() { return characters; }
	void SetCharacter(Character* character) { characters.emplace_back(character); }



};



