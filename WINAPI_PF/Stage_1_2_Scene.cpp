#include "Framework.h"
#include "Stage_1_2_Scene.h"

Stage_1_2_Scene::Stage_1_2_Scene()
{
	tag = "Stage_1-2";
	isEnd = false;

	m_Obj = new ObjManager(this, STAGE_2);
	m_Shade = new ShadeManager(this, STAGE_2);

	isStart = true;

}

Stage_1_2_Scene::Stage_1_2_Scene(string tag)
{
	this->tag = tag;
	isEnd = false;

	m_Obj = new ObjManager(this, STAGE_2);
	m_Shade = new ShadeManager(this, STAGE_2);
}

Stage_1_2_Scene::Stage_1_2_Scene(STAGE_NUM stage)
{
	tag = "Stage_1-2";
	isEnd = false;

	m_Obj = new ObjManager(this, stage);
	m_Shade = new ShadeManager(this, stage);
}

Stage_1_2_Scene::~Stage_1_2_Scene()
{
	delete m_Obj;
	delete m_Shade;
}

void Stage_1_2_Scene::Update()
{
	if (isStart == true)
	{
		if (stageRunTime > 1.0)
		{
			M_CAM->TargetChange(m_Obj->GetCM()->GetTargetCharacter()->GetRect());
			isStart = false;
			stageRunTime = 0.0;
		}
		else
		{
			stageRunTime += DELTA;
			return;
		}
		return;
	}

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

void Stage_1_2_Scene::Render(HDC hdc)
{
	m_Shade->Render(hdc);
	m_Obj->Render(hdc);
}

void Stage_1_2_Scene::Start()
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

void Stage_1_2_Scene::End()
{
	
	isEnd = true;
}
