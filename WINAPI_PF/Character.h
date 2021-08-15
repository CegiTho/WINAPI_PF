#pragma once

class Character : public T_Object
{
protected:
	double speed;
	double thrust;
	double gravity;

	bool isActive;
	bool isJump;
	bool isDoubleJump;
	bool isFalling;
	
	Name name;

	vector<bool> side;

	RectAnimation* anim;
	

public:
	Character();
	virtual ~Character();

	void Move();
	
	vector<bool> GetSide()	{ return side; }
	bool GetActive()		{ return isActive; }
	bool GetJump()			{ return isJump; }
	bool GetDoubleJump()	{ return isDoubleJump; }
	Name GetName()			{ return name; }

	void SetAnim(State value) { anim->SetState(value); }
	void SetSide(Side index, bool value) { side[index] = value; }
	void SetJump(bool value) { isJump = value; }
	void SetThrust(double value) { thrust = value; }
	double& Thrust() { return thrust; }

	void PrintElement(int x);


	Side Collision(T_Object* obj);


	virtual void Collision(vector<T_Object*> objects) = 0;
	virtual void CharacterCollision(T_Object* character) = 0;
	virtual void ObstacleCollision(T_Object* obstacle) = 0;
	//virtual void CharacterCollision(T_Object* goal) = 0;
	
	virtual void InitAgain() = 0;

	virtual void Update() = 0;
	virtual void Render(HDC hdc) = 0;
	virtual void Jump() = 0;



};



