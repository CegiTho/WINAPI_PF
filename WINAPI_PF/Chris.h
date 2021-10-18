#pragma once

class Chris : public Character
{
private:


public:
	Chris();
	Chris(Vector2 pos);
	~Chris();

	void CreateChris(Vector2 pos);

	virtual void Collision(vector<T_Object*> objects) override;
	virtual void CharacterCollision(T_Object* character) override;
	virtual void ObstacleCollision(T_Object* obstacle) override;

	virtual void Update() override;
	virtual void Jump() override;

	virtual void InitAgain() override;

};


