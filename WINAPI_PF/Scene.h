#pragma once

class Scene
{


public:
	virtual	~Scene() {}

	virtual void Update() = 0;
	virtual void Render(HDC hdc) = 0;

	virtual bool Start() { return true; }
	virtual bool End() { return true; }


}; 
