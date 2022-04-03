#include "Framework.h"
#include "CharacterManager.h"

CharacterManager::CharacterManager()
{
	characters.assign(CHARACTER_COUNT, nullptr);
	nowActive = CHARACTER_COUNT;
	pick = new Polygon2();
	pickColor = CreateSolidBrush(WHITE);
	pickEdge = CreatePen(PS_SOLID, 1, WHITE);
}

CharacterManager::~CharacterManager()
{
	for (Character* character : characters)
		delete character;
}

void CharacterManager::Update(vector<T_Object*> obj)
{
	CharacterRotation();
	for (Character* character : characters)
	{
		if (character != nullptr)
			character->Update(obj);
	}
	pick->SetArr(characters[nowActive]);
}

void CharacterManager::Render(HDC hdc)
{
	for (Character* obj : characters)
	{
		if (obj != nullptr && obj->GetRect()->Collision(M_CAM->GetScreen()) == true)
			obj->Render(hdc);
	}
}

void CharacterManager::PickRender(HDC hdc)
{
	HBRUSH oldB = (HBRUSH)SelectObject(hdc, pickColor);
	HPEN oldP = (HPEN)SelectObject(hdc, pickEdge);
	pick->Render(hdc);

	SelectObject(hdc, oldB);
	SelectObject(hdc, oldP);
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
	if (KEYDOWN(KEYBOARD->GetNextCharKey()) == true)
	{
		if (characters[nowActive]->GetActive() == false)
			return;

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
		if (index == indices.size() - 1)
		{
			nowActive = indices[0];
			index = 0;
		}
		else
			nowActive = indices[++index];
		
		SetCharacterActive(nowActive, true);
		M_CAM->TargetChange(characters[nowActive]->GetRect());
	}

	if (KEYDOWN(KEYBOARD->GetPrevCharKey()) == true)
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
		if (index == 0)
		{
			nowActive = indices[indices.size() - 1];
			index = indices.size() - 1;
		}
		else
			nowActive = indices[--index];
		
		SetCharacterActive(nowActive, true);
		M_CAM->TargetChange(characters[nowActive]->GetRect());
	}
}

void CharacterManager::SetCharacterActive(Name character, bool isActive)
{
	this->characters[character]->SetActive(isActive); 
	nowActive = character;
}

void CharacterManager::Collision(vector<T_Object*> obj)
{
	for (Character* character : characters)
	{
		if (character != nullptr)	//이거 나중에 지워도 되는지 확인 
			character->Collision(obj);
	}
}

Character* CharacterManager::GetTargetCharacter()
{
	for (auto character : characters)
	{
		if (character != nullptr)
			return character;
	}
}
