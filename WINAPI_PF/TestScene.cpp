#include "Framework.h"
#include "TestScene.h"

TestScene::TestScene()
{
	isEnd = false;
	Vector2 lSource = { 300,200 };

	m_Obj = new ObjManager(STAGE_4);
	m_Shade = new ShadeManager(this,STAGE_4, lSource);		//여기서 masterCamera의 DC랑 연결된 bitmap사이즈가 결정됨.


	for (Character* character : m_Obj->GetCM()->GetObj())
	{
		if (character != nullptr)
			m_Shade->SetShade(character);
	}
	for (int i : m_Obj->NeedShade())
	{
		m_Shade->SetShade(m_Obj->GetOM()->GetObj()[i]);
	}


	M_CAM->TargetChange(m_Obj->GetCM()->GetObj()[THOMAS]);
	m_Obj->GetCM()->SetCharacterActive(THOMAS, true);

	SOUND->Play("BGM");
}

TestScene::~TestScene()
{
	delete m_Obj;
	delete m_Shade;
}


void TestScene::Update()
{
	if (KEYDOWN(VK_ESCAPE))
		SCENE->ChangeScene("Main Menu");

	m_Obj->Update();
	m_Shade->Update();
	
	if (isEnd == true)
		SCENE->DequeueScene();
}

void TestScene::Render(HDC hdc)
{
	m_Shade->Render(hdc);
	m_Obj->Render(hdc);

}
