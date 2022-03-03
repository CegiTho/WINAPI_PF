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
	WATER
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

