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
	
	vector<bool> side;

	RectAnimation* anim;
	
	HBRUSH goalColor;
	HPEN goalEdge;

	Polygon2* pick;

	vector<Character*> fused;

	Vector2 spawnPoint;

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

	void Render(HDC hdc);
	
	void InitAgain();

	virtual void Update(vector<T_Object*> obj) = 0;
	virtual void Jump() = 0;

	virtual void Collision(vector<T_Object*> objects);
	virtual void CharacterCollision(Character* character);
	virtual void ObstacleCollision(Obstacle* obstacle);
	
	virtual void NormalCollision(NormalObstacle* obstacle);
	virtual void SpikeCollision(SpikeObstacle* obstacle) ;
	virtual void WaterCollision(Water* obstacle);

	void ReturnSpawnPoint();
	void SetSpawnPoint(Rect* rect);
	Vector2 GetSpawnPoint() { return spawnPoint; }

};



