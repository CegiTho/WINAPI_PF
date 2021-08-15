#pragma once

class Scene;

class SceneCamera
{
private:
	enum
	{
		PRE,
		POSSESSION
	};

	SceneCamera();
	~SceneCamera();

	Rect* target;

	vector<Vector2> prePath;
	double preSpeed;

	Vector2 renderStart;

	static SceneCamera* instance;

public:
	static SceneCamera* Get()
	{
		return instance;
	}

	static void Create()
	{
		instance = new SceneCamera();
	}

	static void Delete()
	{
		delete instance;
	}

	void Update();

	void PreMove();
	void ChangeScene();

	void SetPrePath(vector<Vector2> points) { prePath = points; }
	Vector2 BltStart() { return renderStart; }
	void SetTarget(Rect* rect) { target = rect; }
	
};


