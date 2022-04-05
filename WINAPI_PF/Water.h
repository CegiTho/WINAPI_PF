#pragma once


class Water : public Obstacle
{
private:
	random_device rd;


	Rect* renderRect;
	
	HBRUSH magenta;
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

	
	POINT* centerPoints;
	WaveElem elem;

	vector<Wave*> right;
	vector<Wave*> left;
	

	vector<double> randRotPerRight;
	vector<double> randRotPerLeft;
	vector<double> rotSecRight;
	vector<double> rotSecLeft;
	
public :
	Water(Vector2 pos,Vector2 size);
	~Water();    

	void Set( Vector2 pos, Vector2 size);
	void SurfaceEffect();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual Rect* GetRenderRect() override;

	void SurfaceRot();
	void RectDamp();

};
