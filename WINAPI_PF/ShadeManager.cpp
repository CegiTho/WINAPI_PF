#include "Framework.h"

ShadeManager::ShadeManager(STAGE_NUM num, Vector2 lSource)
	:constant(0),stage(num)
{
	this->lSource = new Vector2(lSource.x, lSource.y);
	mapSize = { 0,0 };
	
	LoadDCSize(num);
	CreateAlphaDC(num);
}

ShadeManager::ShadeManager(STAGE_NUM num, double constant)
	:lSource(nullptr),stage(num)
{
	this->constant = constant;
	mapSize = { 0,0 };

	LoadDCSize(num);
	CreateAlphaDC(num);
}

ShadeManager::~ShadeManager()
{
	DeleteObject(stageColor);

	if (lSource != nullptr)
		delete lSource;
}

void ShadeManager::LoadDCSize(STAGE_NUM num)
{
	string file;
	switch (num)
	{
	case STAGE_1:
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
	
	M_CAM->SetMapSize(mapSize);
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
	PatBlt(hdc, 0, 0, mapSize.x, mapSize.y, PATCOPY);

	for (Shade* s : shade)
	{
		s->Render(hdc);
	}
}

void ShadeManager::SetShade(T_Object* objects)
{
	if (lSource == nullptr)
		shade.emplace_back(new Shade(objects, constant,stage));
	else
		shade.emplace_back(new Shade(objects, lSource, stage));
}

void ShadeManager::SpikeSetShade(Rect* rect)
{
	
	if (lSource == nullptr)
		shade.emplace_back(new Shade(rect, constant, stage));
	else
		shade.emplace_back(new Shade(rect, lSource, stage));
	
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

	SelectObject(MasterCamera::backBuffer, stageColor);

}