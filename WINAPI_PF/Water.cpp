#include "Framework.h"

//��������
//������ó���� �׸���,���� ����� ��ҵ� ����Ǿ���ϴµ�
//DC�� ���� ���� Program::backBuffer ���� backBuffer,water�� �� �� �ݿ��� memDC�� 
//GdiAlphaBlend�� ������� ������ ���ϴ� ������ �ȳ��ðŰ���.
//������ water�ϳ������� m_Obj���� ���� DC�� ���� ����� ���� 

#define ALPHA_WATER 50
#define ALPHA_SURFACE 150

#define HEIGHT 5
#define WAVENUMBER 0.1
#define PI 3.1
#define ANTINODE PI/WAVENUMBER			//31
#define WAVE_LENGTH ANTINODE * 6		//186
#define SLICE_DELTA 3


Water::Water( Vector2 pos, Vector2 size)
{
	Set(pos, size);
}

Water::~Water()
{
	delete rect;
	
	delete[] areaPoints;	//POINT* points�� polygon2���� ����

	for (Polygon2* pol : surface)
		delete pol;
	
	DeleteObject(color);
	DeleteObject(edge);
	DeleteObject(surfaceColor);
	DeleteObject(surfaceEdge);

	DeleteObject(rectDC);
	DeleteObject(memDC);
	DeleteObject(transparentDC);
	DeleteObject(surfaceDC);

	DeleteObject(bitmap);
	DeleteObject(rectBitmap);
	DeleteObject(transparentBitmap);
	DeleteObject(surfaceBitmap);
}

void Water::Set( Vector2 pos, Vector2 size)
{
	rect = new Rect(pos, size);

	color = CreateSolidBrush(RGB(180, 180, 180));
	edge = CreatePen(PS_SOLID, 1, RGB(180, 180, 180));

	surfaceColor = CreateSolidBrush(RGB(200, 200, 200));
	surfaceEdge = CreatePen(PS_SOLID, 1, RGB(200, 200, 200));

	SurfaceEffect();

	HDC hdc = GetDC(hWnd);
	memDC = CreateCompatibleDC(hdc);
	rectDC = CreateCompatibleDC(hdc);
	transparentDC = CreateCompatibleDC(hdc);
	surfaceDC = CreateCompatibleDC(hdc);

	bitmap = CreateCompatibleBitmap					(hdc, rect->size.x,rect->size.y + HEIGHT);				//memDC
	rectBitmap = CreateCompatibleBitmap				(hdc, rect->size.x,rect->size.y);						//rectDC
	transparentBitmap = CreateCompatibleBitmap		(hdc, rect->size.x, 2 * HEIGHT);						//transparentDC
	surfaceBitmap = CreateCompatibleBitmap			(hdc, rect->size.x, 2 * HEIGHT);						//surfaceDC
	
	SelectObject(memDC, bitmap);
	SelectObject(rectDC, rectBitmap);
	SelectObject(transparentDC, transparentBitmap);
	SelectObject(surfaceDC, surfaceBitmap);

	ReleaseDC(hWnd,hdc);
};

void Water::SurfaceEffect()
{
	elem.time = 2;
	elem.height = 5;
	elem.pi = PI;
	elem.length = WAVE_LENGTH;
	elem.sliceCount = (WAVE_LENGTH / 2) / SLICE_DELTA;
	elem.delta = SLICE_DELTA;		//x���� �̼Һ���
	elem.damp = 0.005;				//������
	elem.k = WAVENUMBER;			//������� ���
	elem.angular = 0.2;				//���ӵ�
	elem.h_Angular = PI / elem.time;;	//���� �ð����

	int count = this->rect->size.x / elem.length;
	int odd = (int)this->rect->size.x % elem.length;
	centerPoints = new POINT[count];
	areaPoints = new POINT * [count];
	
	for (int i = 0; i < count; i++)
	{
		centerPoints[i].x = (elem.length * i) + (elem.length * 0.5) - 60;
		centerPoints[i].y = elem.height;
	}

	for (int i = 0; i < count; i++)
	{
		areaPoints[i] = new POINT[elem.sliceCount * 4];
	}

	for (int i = 0; i < count; i++)
	{
		vector<Vector2*> vec;
		surfaceArea.emplace_back(vec);
		surfaceArea[i].assign(elem.sliceCount * 4, new Vector2(0,0));
	}

	SurfaceUpdate();
	for (int i = 0 ; i < count ; i++)
	{
		surface.emplace_back(new Polygon2(areaPoints[i],elem.sliceCount*4));
	}

	
}

void Water::SurfaceUpdate()
{
	int count = this->rect->size.x / elem.length;
	int odd = (int)this->rect->size.x % elem.length;
	
	for (int i = 0 ; i < count ; i++)
	{
		//north point
		areaPoints[i][0].x = centerPoints[i].x;
		areaPoints[i][0].y = centerPoints[i].y - elem.height;
		
		//west point
		areaPoints[i][elem.sliceCount].x = centerPoints[i].x - (elem.length * 0.5);
		areaPoints[i][elem.sliceCount].y = elem.height;

		//south point
		areaPoints[i][elem.sliceCount * 2].x = centerPoints[i].x;
		areaPoints[i][elem.sliceCount * 2].y = elem.height * 2;

		//east point
		areaPoints[i][elem.sliceCount * 3].x = centerPoints[i].x + (elem.length * 0.5);
		areaPoints[i][elem.sliceCount * 3].y = elem.height;

		int k = 1;
		for (int j = -elem.sliceCount + 1 ; j < elem.sliceCount; j++)
		{
			
			if (j == 0)
			{
				k = 1;
				continue;
			}

			if (j < 0)
			{
				DampingWave(centerPoints[i], j, TIMER->GetRunTime(), 
					areaPoints[i][-j], areaPoints[i][elem.sliceCount + k]);
				k++;
				continue;
			}
			else
			{
				DampingWave(centerPoints[i], j, TIMER->GetRunTime(), 
					areaPoints[i][elem.sliceCount * 4 - k], areaPoints[i][elem.sliceCount * 2 + k]);
				k++;
			}
		}
	}

	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < elem.sliceCount * 4; j++)
		{
			surfaceArea[i][j]->x = areaPoints[i][j].x;
			surfaceArea[i][j]->y = areaPoints[i][j].y;
		}
	}

	
}

void Water::Update()
{
	SurfaceUpdate();

	surface[0]->SetNewVertices(areaPoints[0]);

}

void Water::Render(HDC hdc)
{
	//memDC
	BitBlt(memDC, 0, 0, rect->size.x, rect->size.y + HEIGHT,
		hdc, rect->LeftTopV().x, rect->LeftTopV().y - 10,
		SRCCOPY);

	//rectDC
	SelectObject(rectDC, color);
	SelectObject(rectDC, edge);

	rect->Render(rectDC, rect->center, rect->size);

	//transparentDC
	PatBlt(transparentDC, 0, 0, rect->size.x, 2 * HEIGHT, WHITENESS);

	SelectObject(transparentDC, surfaceColor);
	SelectObject(transparentDC, surfaceEdge);

	for (Polygon2* pol : surface)
		pol->Render(transparentDC);

	//==========post process============
	//transparentDC�� WHITENESS�� patblt ���ϸ� ���ϴµ��� ����� �ȳ���.
	// 1.bitmap�� ����Ʈ���°� ��� or������ ���� �ϳ����� �˾Ҵµ� �װ� �ƴѰŰ���.
	// 2.surfaceDC���� transparentDC�� alphaBlend�ϴ� �������� transparentDC�� ����ȭ�� WHITENESS ����� �Ѿ�°Ű���.
	// 2-2.���� �˾Ҵµ� surfaceAlpha���� �۾����� whiteness�� ���� �״�� �ȳѾ�� ��������. 
	// surfaceDC,transparentDC �� �� whiteness�� patblt�������
	//transparentDC,memDC,rectDC,surfaceDC  <- �̰� ������ ����� ���� ����.
	PatBlt(surfaceDC, 0, 0, rect->size.x, 2 * HEIGHT, WHITENESS);

	blendFunc.SourceConstantAlpha = ALPHA_SURFACE;
	GdiAlphaBlend(surfaceDC, 0, 0, rect->size.x, 2 * HEIGHT, transparentDC, 0, 0, rect->size.x, 2 * HEIGHT, blendFunc);

	blendFunc.SourceConstantAlpha = ALPHA_WATER;
	GdiAlphaBlend(memDC, 0, HEIGHT, rect->size.x, rect->size.y, rectDC, 0, 0, rect->size.x,rect->size.y,blendFunc);

	blendFunc.SourceConstantAlpha = ALPHA_SURFACE;
	GdiTransparentBlt(memDC, 0, 0, rect->size.x, 2 * HEIGHT, surfaceDC, 0, 0, rect->size.x, 2 * HEIGHT, WHITE);
	BitBlt(hdc, rect->LeftTopV().x, rect->LeftTopV().y - HEIGHT, rect->size.x, rect->size.y + HEIGHT,memDC, 0, 0, SRCCOPY);
	

	//BitBlt(hdc, rect->LeftTopV().x, rect->LeftTopV().y - HEIGHT, rect->size.x, 2 * HEIGHT, transparentDC, 0, 0, SRCCOPY);
	//BitBlt(hdc, rect->LeftTopV().x, rect->LeftTopV().y - HEIGHT, rect->size.x, 2 * HEIGHT, surfaceDC, 0, 0, SRCCOPY);
	//BitBlt(hdc, rect->LeftTopV().x, rect->LeftTopV().y - HEIGHT, rect->size.x, rect->size.y + HEIGHT,tempDC, 0, 0, SRCCOPY);
	//BitBlt(hdc, rect->LeftTopV().x, rect->LeftTopV().y + HEIGHT, rect->size.x, rect->size.y + HEIGHT,tempDC, 0, 0, SRCCOPY);
	//BitBlt(hdc, rect->LeftTopV().x, rect->LeftTopV().y + HEIGHT, rect->size.x, rect->size.y + HEIGHT,tempDC, 0, 0, SRCCOPY);
	//BitBlt(hdc, rect->LeftTopV().x, rect->LeftTopV().y, rect->size.x, rect->size.y + HEIGHT, secTransparentDC, 0, 0, SRCCOPY);
}

Rect* Water::GetRenderRect()
{
	return nullptr;
}

void Water::DampingWave(POINT center,int x, double time, POINT& upper, POINT& lower)
{
	int posX, posY;
	posX = center.x + (x * elem.delta);
	upper.x = posX;
	lower.x = posX;
	
	{//upper
		double dampConst = x > 0 ? -elem.damp : elem.damp;
		double h = elem.height;
		double sine = sin(elem.h_Angular * time);
		double expo = exp(dampConst * posX);
		h = elem.height * sine * expo;
		double cosine = cos(elem.k * posX - elem.angular * time);
		posY = h * cosine;
		upper.y = posY;
	}

	{//lower
		double dampConst = x > 0 ? -elem.damp : elem.damp;
		double h = -elem.height;
		double sine = sin(elem.h_Angular * time);
		double expo = exp(dampConst * posX);
		h = elem.height * sine * expo;
		double cosine = cos(elem.k * posX - elem.angular * time);
		posY = h * cosine;
		lower.y = posY;
	}
}


/*

	int waveCount = rect->size.x / 200;
	int oddLength = (int)rect->size.x % 200;
	int oddSlice = oddLength / waveCount;
	int centerOffset = LENGTH / 2;

	POINT* startPos = new POINT[waveCount];

	for (int i = 0; i < waveCount; i++)
	{
		mt19937_64 gen(rd());
		uniform_int_distribution<int> dist(0, oddSlice);

		int odd = dist(gen);
		startPos[i].x = (i * LENGTH) + odd + centerOffset;
		startPos[i].y = HEIGHT;
	}
	//============������ ���� 200���� �����Ű�. �Ʒ� k,antiNode,delta������ �� #define���� ���� ������ ����.
	//�������� ���� ������.

	//alpha�� Ŀ������ �������� �پ��.
	int k = 0.1;
	int pi = 3.15;
	int antiNode = pi / k;
	int delta = antiNode / SLICE_COUNT;
	int alpha = 0.3;
	int time = 3;










	Vector2 start = { 0,HEIGHT };
	Vector2 end = { rect->size.x,HEIGHT };

	double height = HEIGHT;	//����
	double length = (double)(end.x - start.x);

	//sin(kx) : x=x��ǥ,k=������ ���̻��.   ���� ���� : pi/k
	//100pixel������ �������� �� ������ ����.
	double k = 0.1;				//�ӽð�
	double pi = 3.15;			//3.14�� ����� �ָ��ؼ�
	double antiNode = pi / k;	//'��'�� ����� antiNode��
	double delta = antiNode / SLICE_COUNT;

	for (int x = 0; x < (int)(length / antiNode); x++)
	{
		vector<Vector2> upperAnt;
		vector<Vector2> lowerAnt;

		upperAnt.assign(SLICE_COUNT * 2, { 0,0 });
		upperAnt[0] = start;
		upperAnt[SLICE_COUNT] = { start.x + antiNode , start.y };
		for (int i = 1; i < SLICE_COUNT; i++)
		{
			upperAnt[i] = { start.x + (i * delta),start.y + (height *sin(pi * i / SLICE_COUNT)) };
			upperAnt[SLICE_COUNT + i] = { start.x + antiNode - (i * delta),start.y - (height * sin(pi * i / SLICE_COUNT)) };
		}

		if (start.x + antiNode > end.x)
			break;

		start.x = start.x + antiNode;

		surfaceArea.emplace_back(upperAnt);
	}

	for (vector<Vector2> area : surfaceArea)
	{
		surface.emplace_back(new Polygon2(area));
	}

	*/