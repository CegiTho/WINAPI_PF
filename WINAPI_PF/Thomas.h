#pragma once

class Thomas : public Character
{
private:

public:
	Thomas();
	Thomas(Vector2 pos);
	~Thomas();

	void CreateThomas(Vector2 pos);

	virtual void Collision(vector<T_Object*> objects) override;
	virtual void CharacterCollision(T_Object* character) override;
	virtual void ObstacleCollision(T_Object* obstacle) override;

	virtual void Update() override;
	virtual void Jump() override;

	virtual void InitAgain() override;

};



