#pragma once

class T_Object
{
protected:

	Rect*	rect;
	ID		id;

	HBRUSH	color;
	HPEN	edge;

public:
	T_Object();
	virtual ~T_Object();

	Rect*	GetRect()	{ return rect; }
	ID		GetID()		{ return id; }



};


