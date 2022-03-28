#pragma once

class Trigger : public Obstacle
{
private:
	bool isActive;
	bool isHori;
	
	vector<T_Object*> connectedObj;

	Character* owner;
public:
	Trigger();
	Trigger(Character* owner,Vector2 pos,bool isHori);
	~Trigger();
	
	void Set(Vector2 pos);

	virtual void Update() override {}
	virtual void Render(HDC hdc) override;
	virtual Rect* GetRenderRect() override { return nullptr; }

	void SetActive(bool value) { isActive = value; }
	bool GetActive() { return isActive; }
	
	void Active();

	void AddConnect(T_Object* obj) { connectedObj.emplace_back(obj); }
	Character* GetOwner() { return owner; }
};

