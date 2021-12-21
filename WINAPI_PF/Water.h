#pragma once

//�ϴ� �Ͼ������ ����� alpha�� ��û ���� �غ���.
class Water : public Obstacle
{
private:
	HBRUSH surfaceColor;
	HPEN surfaceEdge;
	
	HDC memDC;
	HDC rectDC;
	HDC transparentDC;
	HDC surfaceDC;

	HBITMAP bitmap;
	HBITMAP rectBitmap;
	HBITMAP transparentBitmap;
	HBITMAP surfaceBitmap;
	
	BLENDFUNCTION blendFunc;

	double time;
	POINT** areaPoints;
	POINT* centerPoints;

	vector<vector<Vector2*>> surfaceArea;
	vector<Polygon2*> surface;

	random_device rd;

	WaveElem elem;


public :
	Water(Vector2 pos,Vector2 size);
	~Water();    

	void Set( Vector2 pos, Vector2 size);
	void SurfaceEffect();
	void SurfaceUpdate();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual Rect* GetRenderRect() override;


	void DampingWave(POINT center, int x,double time,POINT& upper,POINT& lower);
	

};
