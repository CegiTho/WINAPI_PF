#pragma once

class Sarah : public Character
{
private:


public:
	Sarah();
	Sarah(Vector2 pos);
	~Sarah();

	void CreateSarah(Vector2 pos);

	void SetDoubleJump(bool value) { isDoubleJump = value; }

	virtual void Update(vector<T_Object*> obj) override;
	virtual void Jump() override;


};


