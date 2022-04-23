#pragma once

//**처음엔 shade용도로 만들었는데
//지금은 shade는 알아서 polygon함수로 출력중이고 이건 pickTriangle이랑 spikeObs,water에만 관련됨.
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

