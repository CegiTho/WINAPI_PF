#include "Framework.h"
#include "CharacterManager.h"

CharacterManager::CharacterManager()
{
	characters.assign(CHARACTER_COUNT, nullptr);
}

CharacterManager::~CharacterManager()
{
	for (Character* character : characters)
		delete character;
}

void CharacterManager::Update()
{
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

void CharacterManager::Render(HDC hdc, Vector2 offset)
{
	for (Character* obj : characters)
	{
		if (obj != nullptr && obj->GetRect()->Collision(M_CAM->GetScreen()) == true)
			obj->Render(hdc);
	}

}

T_Object* CharacterManager::PlusCharacter(Name name,Vector2 pos)
{
	switch (name)
	{
	case Name::THOMAS:
		characters[THOMAS] = new Thomas(pos);
		return characters[THOMAS];
	case Name::CHRIS:
		characters[CHRIS] = new Chris(pos);
		return characters[CHRIS];
	case Name::CLARE:
		characters[CLARE] = new Clare (pos);
		return characters[CLARE];
	case Name::JAMES:
		characters[JAMES] = new James(pos);
		return characters[JAMES];
	case Name::JOHN:
		characters[JOHN] = new John(pos);
		return characters[JOHN];
	case Name::LAURA:
		characters[LAURA] = new Laura(pos);
		return characters[LAURA];
	case Name::SARAH:
		characters[SARAH] = new Sarah(pos);
		return characters[SARAH];
	}

	
}
