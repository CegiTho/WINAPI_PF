#include "Framework.h"
#include "TestScene.h"

TestScene::TestScene()
{
	//double constant = 2;
	Vector2 lSource = { 300,200 };

	m_Shade = new ShadeManager(STAGE_4, lSource);

	m_Obj = new ObjManager();

	m_Obj->PlusCharacter(Name::THOMAS);
	m_Obj->PlusCharacter(Name::CLARE);
	m_Obj->PlusCharacter(Name::CHRIS);
	m_Obj->PlusCharacter(Name::JAMES);
	m_Obj->PlusCharacter(Name::JOHN);
	m_Obj->PlusCharacter(Name::LAURA);
	//m_Obj->PlusCharacter(Name::SARAH);

	m_Obj->PlusObstacle(Type::NORMAL, { CENTER_X,WIN_HEIGHT - 25 }, { WIN_WIDTH,50 });
	m_Obj->PlusObstacle(Type::NORMAL, { CENTER_X,100 }, { WIN_WIDTH,50 });
	m_Obj->PlusObstacle(Type::NORMAL, { 200,900 }, { 400,50 });

	for (Character* character : m_Obj->GetCM()->GetObj())
	{
		if(character != nullptr)
			m_Shade->SetShade(dynamic_cast<T_Object*>(character));
	}
	m_Shade->SetShade(dynamic_cast<T_Object*>(m_Obj->GetOM()->GetObj()[2]));

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
