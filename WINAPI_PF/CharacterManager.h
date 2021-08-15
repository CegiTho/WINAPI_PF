#pragma once

//�� Scene���� �ϳ��� �ٰŶ� �̱��� �Ⱦ�
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



