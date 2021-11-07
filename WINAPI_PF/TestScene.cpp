#include "Framework.h"
#include "TestScene.h"

TestScene::TestScene()
{
	//double constant = 2;
	Vector2 lSource = { 300,200 };

	m_Shade = new ShadeManager(STAGE_4, lSource);

	m_Obj = new ObjManager();

	m_Obj->LoadStage(STAGE_4);

	for (Character* character : m_Obj->GetCM()->GetObj())
	{
		if (character != nullptr)
			m_Shade->SetShade(character);
	}
	m_Shade->SetShade(m_Obj->GetOM()->GetObj()[2]);
	m_Shade->SetShade(m_Obj->GetOM()->GetObj()[3]);

	M_CAM->TargetChange(m_Obj->GetCM()->GetObj()[THOMAS]);
	m_Obj->GetCM()->SetCharacterActive(THOMAS, true);
}

TestScene::~TestScene()
{
	delete m_Obj;
	delete m_Shade;
}


void TestScene::Update()
{
	m_Obj->Update();

	m_Shade->Update();

	
}

void TestScene::Render(HDC hdc)
{
	//m_Shade->memDC : BG,Shade,Objects 전부 출력 / 크기는 맵 전체 크기
	m_Shade->Render(hdc);
	m_Obj->Render(hdc);

}
