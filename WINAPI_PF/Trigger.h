#pragma once

class Trigger : public Obstacle
{
private:
	bool isActive;
	
	vector<T_Object*> connectedObj;

	Character* owner;
public:
	Trigger();
	Trigger(Character* owner,Vector2 pos);
	~Trigger();
	
	void Set(Vector2 pos);

	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual Rect* GetRenderRect() override { return nullptr; }

	bool GetActive() { return isActive; }
	
	void Collision();
	void Active();

	void AddConnect(T_Object* obj) { connectedObj.emplace_back(obj); }
	Character* GetOwner() { return owner; }
};

