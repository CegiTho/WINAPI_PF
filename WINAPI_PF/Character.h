#pragma once

class Obstacle;
class SpikeObstacle;
class NormalObstacle;
class Water;

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

	bool playOnce;
	bool isFloat;
	bool isPenetrated;

	double respawnDelay;

	vector<bool> side;

	RectAnimation* anim;
	Rect* renderRect;
	
	HBRUSH goalColor;
	HPEN goalEdge;

	Vector2 spawnPoint;

	vector<Character*> moveWith;
public:
	Character();
	Character(Vector2 pos);
	virtual ~Character();

	void Move();
	void AddMoveWith(Character* character) { moveWith.emplace_back(character); }
	
	vector<bool> GetSide()	{ return side; }
	bool GetActive()		{ return isActive; }
	bool GetJump()			{ return isJump; }
	bool GetDoubleJump()	{ return isDoubleJump; }
	Name GetName()			{ return name; }
	Rect* GetRenderRect()	{ return renderRect; }

	void SetActive(bool active) { this->isActive = active; }
	void SetAnim(State value) { anim->SetState(value); }
	void SetSide(Side index, bool value) { side[index] = value; }
	void SetJump(bool value) { isJump = value; }
	void SetThrust(double value) { thrust = value; }
	void SetGoal(bool value) { isGoal = value; }
	double& Thrust() { return thrust; }

	void PrintElement(HDC hdc,int x);

	void Render(HDC hdc);
	
	void InitAgain();

	virtual void Update(vector<T_Object*> obj) = 0;
	virtual void Jump() = 0;

	virtual void Collision(vector<T_Object*> objects);
	virtual void CharacterCollision(Character* character);
	virtual void ObstacleCollision(Obstacle* obstacle);
	
	void NormalCollision(NormalObstacle* obstacle);
	void SpikeCollision(SpikeObstacle* obstacle) ;
	void WaterCollision(Water* obstacle);
	void TriggerCollision(class Trigger* trigger);

	virtual void ReturnSpawnPoint();
	void SetSpawnPoint(Rect* rect);
	Vector2 GetSpawnPoint() { return spawnPoint; }

	string GetNameString();

};



