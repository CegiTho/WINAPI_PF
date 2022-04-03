#include "Framework.h"
#include "Stage_1_1_Scene.h"

Stage_1_1_Scene::Stage_1_1_Scene()
{
	tag = "Stage_1-1";
	isEnd = false;

	m_Obj = new ObjManager(this,STAGE_1);
	m_Shade = new ShadeManager(this,STAGE_1);
}

Stage_1_1_Scene::Stage_1_1_Scene(string tag)
{
	this->tag = tag;
	isEnd = false;

	m_Obj = new ObjManager(this, STAGE_1);
	m_Shade = new ShadeManager(this, STAGE_1);
}

Stage_1_1_Scene::Stage_1_1_Scene(STAGE_NUM stage)
{
	tag = "Stage_1";
	isEnd = false;

	m_Obj = new ObjManager(this,stage);
	m_Shade = new ShadeManager(this,stage);
}

Stage_1_1_Scene::~Stage_1_1_Scene()
{
	delete m_Obj;
	delete m_Shade;
}

void Stage_1_1_Scene::Update()
{
	if (KEYDOWN(VK_ESCAPE))
		SCENE->ChangeScene("Main Menu");


	m_Obj->Update();
	m_Shade->Update();

	if (isEnd == true)
		SCENE->DequeueScene();
	if (m_Obj->GetClearStage() == true)
		End();

	ClearCheck();

}

void Stage_1_1_Scene::Render(HDC hdc)
{
	m_Shade->Render(hdc);
	m_Obj->Render(hdc);
}

void Stage_1_1_Scene::Start()
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

void Stage_1_1_Scene::End()
{
	this->isEnd = true;
}
