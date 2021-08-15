#pragma once

class Goal : public T_Object
{
private:
	bool isGoal;
	Character* character;

	Name name;

public:
	Goal(Character* character,Vector2 pos, STAGE_NUM stage);
	~Goal();

	void CreateElement(Character* character, Vector2 pos,STAGE_NUM stage);

	void Update();
	void Render(HDC hdc);

	void Collision();
	
	bool GoalCheck() { return isGoal; }
	Name GetName() { return name; }

	void SetCheck(function<bool()> Check) { this->Check = Check; }
	function<bool()> Check;

};


