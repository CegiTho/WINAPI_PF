#pragma once

class Scene;

class SceneManager
{
private:
	SceneManager();
	~SceneManager();


	map<string, Scene*> scenes;
	Scene* curScene;

	static SceneManager* instance;

public:
	static SceneManager* Get()
	{
		return instance;
	}

	static void Create()
	{
		instance = new SceneManager();
	}
	
	static void Delete()
	{
		delete instance;
	}

	void Update();
	void Render(HDC hdc);

	Scene* Add(string key, Scene* scene);
	void ChangeScene(string key);

};

