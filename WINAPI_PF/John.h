#pragma once

class John : public Character
{
private:


public:
	John();
	John(Vector2 pos);
	~John();

	void CreateJohn(Vector2 pos);

	virtual void Update(vector<T_Object*> obj) override;
	virtual void Jump() override;
};


