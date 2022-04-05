#pragma once

class Chris : public Character
{
private:


public:
	Chris();
	Chris(Vector2 pos);
	~Chris();

	void CreateChris(Vector2 pos);

	virtual void Update(vector<T_Object*> obj) override;
	virtual void Jump() override;

};


