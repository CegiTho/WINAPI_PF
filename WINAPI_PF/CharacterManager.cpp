#include "Framework.h"
#include "CharacterManager.h"

CharacterManager::CharacterManager()
{
	characters.assign(CHARACTER_COUNT, nullptr);
	nowActive = CHARACTER_COUNT;
}

CharacterManager::~CharacterManager()
{
	for (Character* character : characters)
		delete character;
}

void CharacterManager::Update()
{
	CharacterRotation();
	for (Character* obj : characters)
	{
		if (obj != nullptr)
			obj->Update();
	}
}

void CharacterManager::Render(HDC hdc)
{
	for (Character* obj : characters)
	{
		if(obj != nullptr && obj->GetRect()->Collision(M_CAM->GetScreen()) == true)
			obj->Render(hdc);
	}
}

T_Object* CharacterManager::PlusCharacter(Name name,Vector2 pos)
{
	switch (name)
	{
	case Name::THOMAS:
		characters[THOMAS] = new Thomas(pos);
		indices.emplace_back(THOMAS);
		return characters[THOMAS];
	case Name::CHRIS:
		characters[CHRIS] = new Chris(pos);
		indices.emplace_back(CHRIS);
		return characters[CHRIS];
	case Name::CLARE:
		characters[CLARE] = new Clare (pos);
		indices.emplace_back(CLARE);
		return characters[CLARE];
	case Name::JAMES:
		characters[JAMES] = new James(pos);
		indices.emplace_back(JAMES);
		return characters[JAMES];
	case Name::JOHN:
		characters[JOHN] = new John(pos);
		indices.emplace_back(JOHN);
		return characters[JOHN];
	case Name::LAURA:
		characters[LAURA] = new Laura(pos);
		indices.emplace_back(LAURA);
		return characters[LAURA];
	case Name::SARAH:
		characters[SARAH] = new Sarah(pos);
		indices.emplace_back(SARAH);
		return characters[SARAH];
	}

	
}

void CharacterManager::CharacterRotation()
{
	if (KEYDOWN('E') == true)
	{
		if (nowActive == CHARACTER_COUNT)
		{
			index = 0;
			for (Name name : indices)
			{
				if (characters[name]->GetActive() == true)
				{
					nowActive = name;
					break;
				}
				index++;
			}
		}

		SetCharacterActive(nowActive, false);
		nowActive = (index == indices.size() - 1) ? indices[0] : indices[++index];
		SetCharacterActive(nowActive, true);
		M_CAM->TargetChange(characters[nowActive]);
	}

	if (KEYDOWN('Q') == true)
	{
		if (nowActive == CHARACTER_COUNT)
		{
			index = 0;
			for (Name name : indices)
			{
				if (characters[name]->GetActive() == true)
				{
					nowActive = name;
					break;
				}
				index++;
			}
		}

		SetCharacterActive(nowActive, false);
		nowActive = (index == 0) ? indices[indices.size()-1] : indices[--index];
		SetCharacterActive(nowActive, true);
		M_CAM->TargetChange(characters[nowActive]);
	}
}

void CharacterManager::SetCharacterActive(Name character, bool isActive)
{
	this->characters[character]->SetActive(isActive); 
	nowActive = character;
}
