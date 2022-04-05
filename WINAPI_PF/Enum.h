#pragma once

enum STAGE_NUM
{
	STAGE_1,
	STAGE_2,
	STAGE_3,
	STAGE_4,
	STAGE_5,
};

enum MenuList
{
	MAIN,
	NEW_GAME,
	SCENARIO_SELECT,
	SETTING
};

struct MenuInfo
{
	string tag;
	MenuList menu;
};

enum Type
{
	NORMAL,
	SPIKE,
	WATER,
	TRIGGER
};

enum Name
{
	THOMAS,
	CHRIS,
	CLARE,
	JAMES,
	JOHN,
	LAURA,
	SARAH,
	CHARACTER_COUNT
};

enum Side
{
	UP,
	DOWN,
	RIGHT,
	LEFT,
	NONE
};

enum class ID
{
	CHARACTER,
	OBSTACLE,
	GOAL
};

enum CHANNEL
{
	MAIN_FX_CHANNEL,
	SUB_FX_CHANNEL,
	BG_CHANNEL,
	CHANNEL_COUNT
	//FMOD soundSystem 초기화할 때 채널갯수 필요함
};

enum PointSeq
{
	LEFTTOP = 0,
	RIGHTTOP = 1,
	LEFTBOTTOM = 2,
	RIGHTBOTTOM = 3
};