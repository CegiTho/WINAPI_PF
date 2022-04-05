#pragma once

class Laura : public Character
{
private:


public:
	Laura();
	Laura(Vector2 pos);
	~Laura();

	void CreateLaura(Vector2 pos);
	void LauraJump(Character* character);

	virtual void Update(vector<T_Object*> obj) override;
	virtual void Jump() override;



};


