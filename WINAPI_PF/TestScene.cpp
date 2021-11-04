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

	M_CAM->TargetChange(m_Obj->GetCM()->GetObj()[THOMAS]);
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
	m_Shade->Render();

	m_Obj->Render(m_Shade->GetMemDC());

	BitBlt(
		hdc, 0, 0, WIN_WIDTH, WIN_HEIGHT,
		m_Shade->GetMemDC(), M_CAM->GetPos().x, M_CAM->GetPos().y,
	SRCCOPY);
}
