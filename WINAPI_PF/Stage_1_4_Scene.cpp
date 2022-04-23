#include "Framework.h"
#include "Stage_1_4_Scene.h"

Stage_1_4_Scene::Stage_1_4_Scene(string tag)
{
	this->tag = tag;
	isEnd = false;

	m_Obj = new ObjManager(this, STAGE_4);
	m_Shade = new ShadeManager(this, STAGE_4);
}

Stage_1_4_Scene::~Stage_1_4_Scene()
{
	delete m_Obj;
	delete m_Shade;
}

void Stage_1_4_Scene::Update()
{
	if (this->isStart == true)
		InitTarget();

	m_Obj->Update();
	m_Shade->Update();
	
	ChangeScene();
	ClearCheck();
}

void Stage_1_4_Scene::Render(HDC hdc)
{
	m_Shade->Render(hdc);
	m_Obj->Render(hdc);
}

void Stage_1_4_Scene::Start()
{
	vector<Character*> characters = m_Obj->GetCM()->GetObj();
	for (Character* character : characters)
	{
		if (character != nullptr)
			m_Shade->SetShade(character);
	}
	vector<int> needShade = m_Obj->NeedShade();
	for (int i : needShade)
	{
		m_Shade->SetShade(m_Obj->GetOM()->GetObj()[i]);
	}

	m_Obj->StartSet();
	m_Shade->StartSet();
}

void Stage_1_4_Scene::End()
{
	isEnd = true;
}
