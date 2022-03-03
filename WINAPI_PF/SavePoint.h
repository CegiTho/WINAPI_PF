#pragma once

class SavePoint : public T_Object
{
private:
	//color : ����ȸ��,���ķ���
	map<int,vector<Cross*>> symbol;
	vector<Character*> characters;

	double frameDelta;
	bool isAnim;
	bool isReturn;
	int index;
public:
	SavePoint(vector<Character*> characters,Vector2 pos,Vector2 size);
	~SavePoint();

	void Set(Vector2 pos, Vector2 size);

	void Update();
	void Render(HDC hdc);
	
	void Collision();
	void PlayCollision();


};


