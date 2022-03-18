#pragma once

//**ó���� shade�뵵�� ������µ�
//������ shade�� �˾Ƽ� polygon�Լ��� ������̰� �̰� pickTriangle�̶� spikeObs,water���� ���õ�.
//

class Polygon2 : public Object
{
private:
	vector<Vector2*> vertices;
	Rect* rect;

	POINT* points;



public:
	Polygon2(vector<Vector2*> vertices);
	Polygon2(vector<Vector2> vertices);
	Polygon2(POINT* vertices);
	Polygon2(POINT* vertices,int size);
	Polygon2(Rect* rect);
	~Polygon2();

	virtual void Render(HDC hdc) override;
	void Update();

	void SetArr();
	void InitArr();

	vector<Vector2*> GetVertices() { return vertices; }

	void SetNewVertices(POINT* newVertices);

	virtual bool Collision(Line* line) override;
	virtual bool Collision(Circle* circle) override;
	virtual bool Collision(Rect* rect) override;

	void Shift(vector<Vector2> vertices);

};

