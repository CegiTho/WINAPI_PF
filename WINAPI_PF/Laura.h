#pragma once

class Laura : public Character
{
private:


public:
	Laura();
	~Laura();

	void CreateLaura(Vector2 pos);
	void LauraJump(Character* character);

	virtual void Collision(vector<T_Object*> objects) override;
	virtual void CharacterCollision(T_Object* character) override;
	virtual void ObstacleCollision(T_Object* obstacle) override;

	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Jump() override;

	virtual void InitAgain() override;


};


