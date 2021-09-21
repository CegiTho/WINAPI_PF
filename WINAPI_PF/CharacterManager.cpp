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
		if(obj != nullptr)
			obj->Render(hdc);
		
	}
}

T_Object* CharacterManager::PlusCharacter(Name name)
{
	switch (name)
	{
	case Name::THOMAS:
		characters[THOMAS] = new Thomas();
		return characters[THOMAS];
	case Name::CHRIS:
		characters[CHRIS] = new Chris();
		return characters[CHRIS];
	case Name::CLARE:
		characters[CLARE] = new Clare ();
		return characters[CLARE];
	case Name::JAMES:
		characters[JAMES] = new James();
		return characters[JAMES];
	case Name::JOHN:
		characters[JOHN] = new John();
		return characters[JOHN];
	case Name::LAURA:
		characters[LAURA] = new Laura();
		return characters[LAURA];
	case Name::SARAH:
		characters[SARAH] = new Sarah();
		return characters[SARAH];
	}

	
}
