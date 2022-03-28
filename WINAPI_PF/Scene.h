#pragma once

class Scene
{
protected:
	bool isEnd;
	string tag;


public:
	Scene() {}
	Scene(string tag) { this->tag = tag; }
	virtual	~Scene() {}

	virtual void Update() = 0;
	virtual void Render(HDC hdc) = 0;

	virtual void Start() = 0;
	virtual void End() = 0;

	bool GetEnd() { return isEnd; }
	string GetTag() { return tag; }

}; 
