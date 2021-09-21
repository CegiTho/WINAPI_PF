#pragma once

class John : public Character
{
private:


public:
	John();
	~John();

	void CreateJohn(Vector2 pos);

	virtual void Collision(vector<T_Object*> objects) override;
	virtual void CharacterCollision(T_Object* character) override;
	virtual void ObstacleCollision(T_Object* obstacle) override;

	virtual void InitAgain() override;
	virtual void Update() override;
	virtual void Jump() override;


};


