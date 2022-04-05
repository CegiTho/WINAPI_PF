#pragma once

class Trigger : public Obstacle
{
private:
	bool isActive;
	bool isHori;
	

	vector<T_Object*> connectedObj;

	Obstacle* attachedObj;
	Vector2 offset;
	Character* owner;
public:
	Trigger(Character* owner,Obstacle* attachedObj,bool isHori,Side side,double distance);
	~Trigger();
	
	void Set();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual Rect* GetRenderRect() override { return nullptr; }

	void SetActive(bool value) { isActive = value; }
	bool GetActive() { return isActive; }
	
	void Active();

	void AddConnect(T_Object* obj) { connectedObj.emplace_back(obj); }
	Character* GetOwner() { return owner; }
};

