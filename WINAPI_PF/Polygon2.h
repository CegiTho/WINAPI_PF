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
	Polygon2();
	Polygon2(vector<Vector2*> vertices);
	~Polygon2();

	virtual void Render(HDC hdc) override;
	
	void InitArr();
	void SetArr(class Character* character);

	vector<Vector2*> GetVertices() { return vertices; }

	void Shift(vector<Vector2>& vertices);


};

