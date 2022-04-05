#pragma once

class James : public Character
{
private:


public:
	James();
	James(Vector2 pos);
	~James();

	void CreateJames(Vector2 pos);

	virtual void Update(vector<T_Object*> obj) override;
	virtual void Jump() override;

};


