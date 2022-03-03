#pragma once

class Goal : public T_Object
{
private:
	bool isGoal;
	Character* character;

	//Render할때 사용
	vector<Line*> lines;

	HPEN goalEdge;
	Name name;

public:
	Goal(Character* character,Vector2 pos);
	~Goal();

	void CreateElement(Character* character, Vector2 pos);

	void Render(HDC hdc);

	void Collision();
	
	bool GoalCheck() { return isGoal; }
	Name GetName() { return name; }



};


