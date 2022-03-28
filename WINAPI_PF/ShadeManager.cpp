#include "Framework.h"

ShadeManager::ShadeManager(Scene* owner, STAGE_NUM num)
	:constant (0),stage(num),lSource(nullptr), owner(owner)
{
	mapSize = { 0,0 };

	LoadDCSize(num);
	CreateAlphaDC(num);
}

ShadeManager::ShadeManager(Scene* owner, STAGE_NUM num, Vector2 lSource)
	:constant(0),stage(num),isSpotLight(true),owner(owner)
{
	this->lSource = new Vector2(lSource.x, lSource.y);
	mapSize = { 0,0 };
	
	LoadDCSize(num);
	CreateAlphaDC(num);
}

ShadeManager::ShadeManager(Scene* owner, STAGE_NUM num, double constant)
	:lSource(nullptr),stage(num),isSpotLight(false), owner(owner)
{
	this->constant = constant;
	mapSize = { 0,0 };

	LoadDCSize(num);
	CreateAlphaDC(num);
}

ShadeManager::~ShadeManager()
{
	DeleteObject(stageColor);

	if (isSpotLight == true)
		delete lSource;
}

void ShadeManager::LoadDCSize(STAGE_NUM num)
{
	string file;
	switch (num)
	{
	case STAGE_1:
		file = "Stage_1_Data.xml";
		break;
	case STAGE_2:
		break;
	case STAGE_3:
		break;
	case STAGE_4:		
		file = "Resource/Stage_4_Data.xml";
		break;
	case STAGE_5:
		break;
	}

	XmlDocument* document = new XmlDocument();
	document->LoadFile(file.c_str());

	XmlElement* root = document->FirstChildElement("StageElement");
	XmlElement* stageSize = root->FirstChildElement("StageSize");
	stageSize = stageSize->FirstChildElement("size");

	mapSize.x = stageSize->IntAttribute("sizeX");
	mapSize.y = stageSize->IntAttribute("sizeY");

	XmlElement* light = stageSize->NextSiblingElement("light");
	if (light != nullptr)
	{
		bool spotLight = light->IntAttribute("isspot");
		if (spotLight == true)
		{
			Vector2 pos;
			pos.x = light->IntAttribute("posX");
			pos.y = light->IntAttribute("posY");
			lSource = new Vector2(pos);
		}
		else if (spotLight == false)
		{
			double cons = light->DoubleAttribute("constant");
			this->constant = cons;
		}
	}
	
	M_CAM->SetMapSize(mapSize,false);
}

void ShadeManager::StartSet()
{
	M_CAM->SetMapSize(mapSize, false);
}

void ShadeManager::Update()
{
	for (Shade* s : shade)
	{
		s->Update();
	}
}

void ShadeManager::Render(HDC hdc)
{
	SelectObject(hdc, stageColor);
	PatBlt(hdc, 0, 0, mapSize.x, mapSize.y, PATCOPY);

	for (Shade* s : shade)
	{
		s->Render(hdc);
	}
}

void ShadeManager::SetShade(T_Object* objects)
{
	switch (objects->GetID())
	{
	case ID::CHARACTER:
		if (lSource == nullptr)
			shade.emplace_back(new Shade(dynamic_cast<Character*>(objects)->GetRenderRect(), constant, stage));
		else
			shade.emplace_back(new Shade(dynamic_cast<Character*>(objects)->GetRenderRect(), lSource, stage));
		break;
	case ID::OBSTACLE:
		if (lSource == nullptr)
			shade.emplace_back(new Shade(static_cast<Obstacle*>(objects)->GetRenderRect(), constant, stage));
		else
			shade.emplace_back(new Shade(static_cast<Obstacle*>(objects)->GetRenderRect(), lSource, stage));
		break;

	}
}

void ShadeManager::CreateAlphaDC(STAGE_NUM num)
{
	switch (num)
	{
	case STAGE_1:
		stageColor = CreateSolidBrush(BG_COLOR_1);
		break;
	case STAGE_2:
		stageColor = CreateSolidBrush(BG_COLOR_2);
		break;
	case STAGE_3:
		stageColor = CreateSolidBrush(BG_COLOR_3);
		break;
	case STAGE_4:
		stageColor = CreateSolidBrush(BG_COLOR_4);
		break;
	case STAGE_5:
		stageColor = CreateSolidBrush(BG_COLOR_5);
		break;
	}
}