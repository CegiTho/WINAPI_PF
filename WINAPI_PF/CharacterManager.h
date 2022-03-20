#pragma once

class CharacterManager
{
private:
	vector<Character*> characters;
	vector<Name> indices;

	Name nowActive;
	Name prevActive;

	int index;

	Polygon2* pick;
	HBRUSH pickColor;
	HPEN pickEdge;

public:
	CharacterManager();
	~CharacterManager();

	void Update(vector<T_Object*> obj);
	void Render(HDC hdc);

	T_Object* PlusCharacter(Name name,Vector2 pos);

	vector<Character*> GetObj() { return characters; }
	void SetCharacter(Character* character) { characters.emplace_back(character); }

	void CharacterRotation();

	void SetCharacterActive(Name character, bool isActive);

	void Collision(vector<T_Object*> obj);

};





