#include "Framework.h"
#include "TestScene.h"

TestScene::TestScene()
{
	Vector2 lSource = { 300,200 };

	m_Shade = new ShadeManager(STAGE_4, lSource);		//여기서 masterCamera의 DC랑 연결된 bitmap사이즈가 결정됨.

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

	vector<string> tag;
	tag.emplace_back("New Game");
	tag.emplace_back("Scenario Select");
	tag.emplace_back("Setting");
	tag.emplace_back("Exit");

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
	m_Shade->Render(hdc);
	m_Obj->Render(hdc);

}
