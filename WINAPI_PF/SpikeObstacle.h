#pragma once

#define Spike_Unit
class SpikeObstacle : public Obstacle
{
private:
	vector<Polygon2*> spikes;
	vector<bool> spikeSide;

	Rect* renderRect;


public:
	SpikeObstacle(Vector2 center, Vector2 size,bool left,bool up,bool right,bool down);
	SpikeObstacle(Vector2 center, Vector2 size,Vector2 pathEnd,double speed, bool left, bool up, bool right, bool down);
	~SpikeObstacle();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual Rect* GetRenderRect() override { return renderRect; }


	void SetObs(Vector2 center, Vector2 size, bool left, bool up, bool right, bool down);
	void SetSpikePolygon(Rect* renderRect);

	vector<bool> GetSpikeSide() { return spikeSide; }



};

