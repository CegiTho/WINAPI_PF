#pragma once

class GameStreamManager
{
private:
	map<string, Scene*> scenes;




	GameStreamManager();
	~GameStreamManager();
public:
	static GameStreamManager* Get()
	{
		static GameStreamManager instance;
		return &instance;
	}

	void Update();
	void Render(HDC hdc);





};

