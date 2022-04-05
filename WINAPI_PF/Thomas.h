#pragma once

class Thomas : public Character
{
private:

public:
	Thomas();
	Thomas(Vector2 pos);
	~Thomas();

	void CreateThomas(Vector2 pos);

	virtual void Update(vector<T_Object*> obj) override;
	virtual void Jump() override;


};

