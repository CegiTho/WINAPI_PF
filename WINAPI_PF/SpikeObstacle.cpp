#include "Framework.h"

SpikeObstacle::SpikeObstacle(Vector2 center, Vector2 size, bool left, bool up, bool right, bool down)
{
	color = CreateSolidBrush(BLACK);
	edge = CreatePen(PS_SOLID, 1, BLACK);

	type = Type::SPIKE;

	this->isMove = false;
	this->isLoop = false;
	this->times = 0;
	this->startPos = center;
	this->destPos = center;

	SetObs(center, size, left, up, right, down);
}

SpikeObstacle::SpikeObstacle(Vector2 center, Vector2 size, Vector2 pathEnd, 
	double times, bool isMove, bool isLoop, bool left, bool up, bool right, bool down)
{
	color = CreateSolidBrush(BLACK);
	edge = CreatePen(PS_SOLID, 1, BLACK);

	type = Type::SPIKE;

	this->isLoop = isLoop;
	this->times = times;
	this->startPos = center;
	this->destPos = pathEnd;
	this->isMove = isMove;

	SetObs(center, size, left, up, right, down);
}

SpikeObstacle::~SpikeObstacle()
{
	delete rect;
	delete renderRect;

	for (Polygon2* pol : spikes)
		delete pol;
	
	DeleteObject(color);
	DeleteObject(edge);
}

void SpikeObstacle::Update()
{
	if (isMove == false)
		return;

	Move();
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
			if(pol != nullptr)
				pol->Render(hdc);
		}
	}

	SelectObject(hdc, tempB);
	SelectObject(hdc, tempP);

	moveWith.clear();
	moveWith.shrink_to_fit();
}

void SpikeObstacle::Move()
{
	if (isGoback == false)	//start -> end
	{
		time += DELTA;
		Vector2 newPos = Math::SineInterpolation(startPos, destPos, times, time);
		Vector2 delta = newPos - this->rect->center;
		this->renderRect->center = newPos;
		double diff = (destPos - this->rect->center).Length();
		this->rect->center += delta;

		ShiftPoint();

		for (Character* character : moveWith)
		{
			character->GetRect()->center += delta;
		}

		if (diff <= EPSILON && isLoop == true)
		{
			isGoback = true;
			time = 0.0;
		}
		else if (diff < EPSILON && isLoop == false)
		{
			startPos = destPos;
			isGoback = false;
			isMove = false;
			time = 0.0;
		}
	}
	else					//end -> start
	{
		time += DELTA;
		Vector2 newPos = Math::SineInterpolation(destPos, startPos, times, time);
		Vector2 delta = newPos - this->rect->center;
		this->renderRect->center = newPos;
		this->rect->center += delta;

		ShiftPoint();

		for (Character* character : moveWith)
		{
			character->GetRect()->center += delta;
		}

		double diff = (startPos - this->rect->center).Length();
		if (diff < EPSILON)
		{
			isGoback = false;
			time = 0.0;
		}
	}
}


void SpikeObstacle::SetObs(Vector2 center, Vector2 size, bool left, bool up, bool right, bool down)
{
	//매개변수로 받은 size = x,y축 각각 spike갯수
	//구조물 크기는 (사각박스 + spike범위) 포함
	//엄밀하게 히트박스에 해당됨.
	//일단 사면 전부 spike달려있다고 가정하고 히트박스 생성.
	//+ 이렇게 하면 한 면에만 spike달려있는 경우 2*SPIKE_HEIGHT때문에 비는 영역 생김.

	spikeSide.assign(4, false);

	spikeSide[Side::LEFT] = left;
	spikeSide[Side::UP] = up;
	spikeSide[Side::RIGHT] = right;
	spikeSide[Side::DOWN] = down;

	Vector2 boxSize;
	boxSize.x = (size.x * SPIKE_WIDTH);
	boxSize.y = (size.y * SPIKE_WIDTH);

	
	{//Spike있는 면에 따른 출력용 Rect(renderRect)의 center조절
		Vector2 renderBoxPos = center;
		Vector2 renderBoxSize = boxSize;
		Vector2 newCenter = center;
		int delta = 0.5 * SPIKE_HEIGHT;

		if (spikeSide[Side::LEFT] == true)
		{
			boxSize.x += SPIKE_HEIGHT;
			newCenter.x -= delta;
		}
		if (spikeSide[Side::RIGHT] == true)
		{
			boxSize.x += SPIKE_HEIGHT;
			newCenter.x += delta;
		
		}
		if (spikeSide[Side::UP] == true)
		{
			boxSize.y += SPIKE_HEIGHT;
			newCenter.y -= delta;
		
		}
		if (spikeSide[Side::DOWN] == true)
		{
			boxSize.y += SPIKE_HEIGHT;
			newCenter.y += delta;
		}

		rect = new Rect(newCenter, boxSize);
		renderRect = new Rect(renderBoxPos, renderBoxSize);
	}

	SetSpikePolygon(renderRect);
}

void SpikeObstacle::SetSpikePolygon(Rect* renderRect)
{
	spikes.assign(4, nullptr);
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

		spikes[LEFT] = new Polygon2(vertices);
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

		spikes[RIGHT] = new Polygon2(vertices);
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

		spikes[UP] = new Polygon2(vertices);
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

		spikes[DOWN] = new Polygon2(vertices);
		for (Vector2* vector : vertices)
			delete vector;
	}
}


void SpikeObstacle::ShiftPoint()
{
	int delta = SPIKE_WIDTH / 2;

	if (spikeSide[LEFT] == true)
	{
		vector<Vector2> vertices;

		//count : 해당 모서리의 spike갯수 , level : spike꼭지점들의 x혹은 y값
		int count = renderRect->size.y / SPIKE_WIDTH;
		int level = renderRect->LeftTopV().x - SPIKE_HEIGHT;
		vertices.assign((2 * count + 1), { 0,0 });
		
		Vector2 startPoint = renderRect->LeftTopV();
		vertices[0] = startPoint;
		for (int i = 0; i < count; i++)
		{
			vertices[i * 2 + 1] ={ (double)level,renderRect->LeftTopV().y + (delta * (2 * i + 1)) };		//가시끝부분
			vertices[i * 2 + 2]= { startPoint.x , startPoint.y + (delta * (2 * i + 2)) };		//모서리랑 붙어있는부분
		}

		spikes[LEFT]->Shift(vertices);
	}
	if (spikeSide[RIGHT] == true)
	{
		vector<Vector2> vertices;

		//count : 해당 모서리의 spike갯수 , level : spike꼭지점들의 x혹은 y값
		int count = renderRect->size.y / SPIKE_WIDTH;
		int level = renderRect->RightTop().x + SPIKE_HEIGHT;
		vertices.assign((2 * count + 1), { 0,0 });

		Vector2 startPoint = renderRect->RightTopV();
		vertices[0] = startPoint;
		for (int i = 0; i < count; i++)
		{
			vertices[i * 2 + 1] = { (double)level,renderRect->RightTopV().y + (delta * (2 * i + 1)) };		//가시끝부분
			vertices[i * 2 + 2] = { startPoint.x , startPoint.y + (delta * (2 * i + 2)) };		//모서리랑 붙어있는부분
		}

		spikes[RIGHT]->Shift(vertices);
	}

	if (spikeSide[UP] == true)
	{
		vector<Vector2> vertices;

		//count : 해당 모서리의 spike갯수 , level : spike꼭지점들의 x혹은 y값
		int count = renderRect->size.x / SPIKE_WIDTH;
		int level = renderRect->LeftTopV().y - SPIKE_HEIGHT;

		Vector2 startPoint = renderRect->LeftTopV();
		vertices.assign((2 * count + 1), { 0,0 });
		vertices[0] = startPoint;
		for (int i = 0; i < count; i++)
		{
			vertices[i * 2 + 1] = { renderRect->LeftTopV().x + (delta * (2 * i + 1)) , (double)level };	//가시끝부분
			vertices[i * 2 + 2] = { startPoint.x + (delta * (2 * i + 2)) , startPoint.y };		//모서리랑 붙어있는부분
		}

		spikes[UP]->Shift(vertices);
	}
	if (spikeSide[DOWN] == true)
	{
		vector<Vector2> vertices;

		//count : 해당 모서리의 spike갯수 , level : spike꼭지점들의 x혹은 y값
		int count = renderRect->size.x / SPIKE_WIDTH;
		int level = renderRect->LeftBottomV().y + SPIKE_HEIGHT;

		vertices.assign((2 * count + 1), { 0,0 });
		Vector2 startPoint = renderRect->LeftBottomV();
		vertices[0] = startPoint;
		for (int i = 0; i < count; i++)
		{
			vertices[i * 2 + 1] = { renderRect->LeftBottomV().x + (delta * (2 * i + 1)) , (double)level };	//가시끝부분
			vertices[i * 2 + 2] = { startPoint.x + (delta * (2 * i + 2)) , startPoint.y };			//모서리랑 붙어있는부분
		}

		spikes[DOWN]->Shift(vertices);
	}
}