#include "Framework.h"

SpikeObstacle::SpikeObstacle(Vector2 center, Vector2 size, bool left, bool up, bool right, bool down)
{
	color = CreateSolidBrush(BLACK);
	edge = CreatePen(PS_SOLID, 1, BLACK);

	type = Type::SPIKE;

	SetObs(center, size, left, up, right, down);

}

SpikeObstacle::SpikeObstacle(Vector2 center, Vector2 size, Vector2 pathEnd, double speed, bool left, bool up, bool right, bool down)
{
}

SpikeObstacle::~SpikeObstacle()
{
	delete rect;
	delete renderRect;

	for (Polygon2* pol : spikes)
		delete pol;
	
	DeleteObject(color);
	DeleteObject(edge);

	if (path != nullptr)
		delete path;
}

void SpikeObstacle::Update()
{
}

void SpikeObstacle::Render(HDC hdc)
{
	HBRUSH tempB = (HBRUSH)SelectObject(hdc, color);
	HPEN tempP = (HPEN)SelectObject(hdc, edge);

	renderRect->Render(hdc);
	
	if (spikes.size() > 0)
	{
		for (Polygon2* pol : spikes)
		{
			pol->Render(hdc);
		}
	}

	SelectObject(hdc, tempB);
	SelectObject(hdc, tempP);
}

void SpikeObstacle::SetObs(Vector2 center, Vector2 size, bool left, bool up, bool right, bool down)
{
	//매개변수로 받은 size = x,y축 각각 spike갯수
	//구조물 크기는 (사각박스 + spike범위) 포함
	//엄밀하게 히트박스에 해당됨.
	//일단 사면 전부 spike달려있다고 가정하고 히트박스 생성.
	Vector2 boxSize;
	boxSize.x = (size.x * SPIKE_WIDTH) + (2 * SPIKE_HEIGHT);
	boxSize.y = (size.y * SPIKE_WIDTH) + (2 * SPIKE_HEIGHT);
	rect = new Rect(center, boxSize);

	this->path = nullptr;
	speed = 0;

	spikeSide.assign(4, false);

	spikeSide[Side::LEFT] = left;
	spikeSide[Side::UP] = up;
	spikeSide[Side::RIGHT] = right;
	spikeSide[Side::DOWN] = down;

	//Spike있는 면에 따른 출력용 Rect(renderRect)의 center조절
	Vector2 renderBoxPos = center;
	Vector2 renderBoxSize = boxSize;
	int delta = 0.5 * SPIKE_HEIGHT;

	if (spikeSide[Side::LEFT] == true)
	{
		renderBoxPos.x += delta;
		renderBoxSize.x -= SPIKE_HEIGHT;
	}
	if (spikeSide[Side::RIGHT] == true)
	{
		renderBoxPos.x -= delta;
		renderBoxSize.x -= SPIKE_HEIGHT;
	}
	if (spikeSide[Side::UP] == true)
	{
		renderBoxPos.y += delta;
		renderBoxSize.y -= SPIKE_HEIGHT;
	}
	if (spikeSide[Side::DOWN] == true)
	{
		renderBoxPos.y -= delta;
		renderBoxSize.y -= SPIKE_HEIGHT;
	}
	




	//spikeSide[Side::LEFT] ? renderBoxPos.x += deltaX : renderBoxPos.x -= deltaX;
	//spikeSide[Side::DOWN] ? renderBoxPos.y += deltaY : renderBoxPos.y -= deltaY;
	//
	//if (spikeSide[Side::LEFT] && spikeSide[Side::RIGHT] == true)
	//	renderBoxSize.x -= 2 * SPIKE_HEIGHT;
	//else if(spikeSide[Side::LEFT] && spikeSide[Side::RIGHT] == false)
	//	renderBoxSize.x -= SPIKE_HEIGHT;

	//if (spikeSide[Side::UP] && spikeSide[Side::DOWN] == true)
	//	renderBoxSize.y -= 2 * SPIKE_HEIGHT;
	//else if(spikeSide[Side::UP] && spikeSide[Side::DOWN] == false)
	//	renderBoxSize.y -= SPIKE_HEIGHT;

	renderRect = new Rect(renderBoxPos,renderBoxSize);
	SetSpikePolygon(renderRect);
}

void SpikeObstacle::SetSpikePolygon(Rect* renderRect)
{
	int delta = SPIKE_WIDTH / 2;

	if (spikeSide[LEFT] == true)
	{
		vector<Vector2*> vertices;
		Vector2 startPoint = renderRect->LeftTopV();
		vertices.emplace_back(new Vector2(startPoint));

		//count : 해당 모서리의 spike갯수 , level : spike꼭지점들의 x혹은 y값
		int count = renderRect->size.y / SPIKE_WIDTH;
		int level = renderRect->LeftTopV().x - SPIKE_HEIGHT;
		for (int i = 0; i < count; i++)
		{
			vertices.emplace_back(new Vector2({ (double)level,renderRect->LeftTopV().y + (delta * (2 * i + 1)) }));		//가시끝부분
			vertices.emplace_back(new Vector2({ startPoint.x , startPoint.y + (delta * (2 * i + 2)) }));		//모서리랑 붙어있는부분
		}

		spikes.emplace_back(new Polygon2(vertices));
		for (Vector2* vector : vertices)
			delete vector;
	}
	if (spikeSide[RIGHT] == true)
	{
		vector<Vector2*> vertices;
		Vector2 startPoint = renderRect->RightTopV();
		vertices.emplace_back(new Vector2(startPoint));

		//count : 해당 모서리의 spike갯수 , level : spike꼭지점들의 x혹은 y값
		int count = renderRect->size.y / SPIKE_WIDTH;
		int level = renderRect->RightTopV().x + SPIKE_HEIGHT;
		for (int i = 0; i < count; i++)
		{
			vertices.emplace_back(new Vector2({ (double)level,renderRect->RightTopV().y + (delta * (2 * i + 1)) }));	//가시끝부분
			vertices.emplace_back(new Vector2({ startPoint.x , startPoint.y + (delta * (2 * i + 2)) }));		//모서리랑 붙어있는부분
		}

		spikes.emplace_back(new Polygon2(vertices));
		for (Vector2* vector : vertices)
			delete vector;

	}

	if (spikeSide[UP] == true)
	{
		vector<Vector2*> vertices;
		Vector2 startPoint = renderRect->LeftTopV();
		vertices.emplace_back(new Vector2(startPoint));

		//count : 해당 모서리의 spike갯수 , level : spike꼭지점들의 x혹은 y값
		int count = renderRect->size.x / SPIKE_WIDTH;
		int level = renderRect->LeftTopV().y - SPIKE_HEIGHT;
		for (int i = 0; i < count; i++)
		{
			vertices.emplace_back(new Vector2({ renderRect->LeftTopV().x + (delta * (2 * i + 1)) , (double)level }));	//가시끝부분
			vertices.emplace_back(new Vector2({ startPoint.x + (delta * (2 * i + 2)) , startPoint.y }));		//모서리랑 붙어있는부분
		}

		spikes.emplace_back(new Polygon2(vertices));
		for (Vector2* vector : vertices)
			delete vector;
	}
	if (spikeSide[DOWN] == true)
	{
		vector<Vector2*> vertices;
		Vector2 startPoint = renderRect->LeftBottomV();
		vertices.emplace_back(new Vector2(startPoint));

		//count : 해당 모서리의 spike갯수 , level : spike꼭지점들의 x혹은 y값
		int count = renderRect->size.x / SPIKE_WIDTH;
		int level = renderRect->LeftBottomV().y + SPIKE_HEIGHT;
		for (int i = 0; i < count; i++)
		{
			vertices.emplace_back(new Vector2({ renderRect->LeftBottomV().x + (delta * (2 * i + 1)) , (double)level }));	//가시끝부분
			vertices.emplace_back(new Vector2({ startPoint.x + (delta * (2 * i + 2)) , startPoint.y }));			//모서리랑 붙어있는부분
		}

		spikes.emplace_back(new Polygon2(vertices));
		for (Vector2* vector : vertices)
			delete vector;
	}

	
}
