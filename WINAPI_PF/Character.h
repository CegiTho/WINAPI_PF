#pragma once

class Character : public T_Object
{
protected:
	Name name;
	
	double speed;
	double thrust;
	double gravity;
	bool isActive;
	bool isJump;
	bool isDoubleJump;
	bool isFalling;
	bool isGoal;
	
	vector<bool> side;

	RectAnimation* anim;
	
	HBRUSH goalColor;
	HPEN goalEdge;

public:
	Character();
	Character(Vector2 pos);
	virtual ~Character();

	void Move();
	
	vector<bool> GetSide()	{ return side; }
	bool GetActive()		{ return isActive; }
	bool GetJump()			{ return isJump; }
	bool GetDoubleJump()	{ return isDoubleJump; }
	Name GetName()			{ return name; }

	void SetActive(bool active) { this->isActive = active; }
	void SetAnim(State value) { anim->SetState(value); }
	void SetSide(Side index, bool value) { side[index] = value; }
	void SetJump(bool value) { isJump = value; }
	void SetThrust(double value) { thrust = value; }
	void SetGoal(bool value) { isGoal = value; }
	double& Thrust() { return thrust; }

	void PrintElement(HDC hdc,int x);

	Side Collision(T_Object* obj);

	void Render(HDC hdc);

	virtual void Collision(vector<T_Object*> objects) = 0;
	virtual void CharacterCollision(T_Object* character) = 0;
	virtual void ObstacleCollision(T_Object* obstacle) = 0;
	//virtual void CharacterCollision(T_Object* goal) = 0;
	
	virtual void InitAgain() = 0;

	virtual void Update() = 0;
	virtual void Jump() = 0;



};



