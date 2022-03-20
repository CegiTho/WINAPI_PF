#pragma once

class Clare : public Character
{
private:
	bool isEscape;
	double floatingTime;


public:
	Clare();
	Clare(Vector2 pos);
	~Clare();

	void CreateClare(Vector2 pos);

	virtual void Update(vector<T_Object*> obj) override;
	virtual void Jump() override;

	virtual void ReturnSpawnPoint() override;

	void OnWater(Water* obs);
};


