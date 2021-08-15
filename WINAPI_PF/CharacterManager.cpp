#include "Framework.h"
#include "CharacterManager.h"

CharacterManager::CharacterManager()
	:characters{}
{
}

CharacterManager::~CharacterManager()
{
	for (Character* character : characters)
		delete character;
}

void CharacterManager::Update()
{
	for (Character* obj : characters)
		obj->Update();
}

void CharacterManager::Render(HDC hdc)
{
	for (Character* obj : characters)
		obj->Render(hdc);
}

void CharacterManager::PlusCharacter(Name name)
{
	switch (name)
	{
	case Name::THOMAS:
		characters.emplace_back(new Thomas());
		break;
	case Name::CHRIS:
		characters.emplace_back(new Chris());
		break;
	case Name::CLARE:
		characters.emplace_back(new Clare());
		break;
	case Name::JAMES:
		characters.emplace_back(new James());
		break;
	case Name::JOHN:
		characters.emplace_back(new John());
		break;
	case Name::LAURA:
		characters.emplace_back(new Laura());
		break;
	case Name::SARAH:
		characters.emplace_back(new Sarah());
		break;
	default:
		break;
	}
}
