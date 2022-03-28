#include "Framework.h"

//구현포기
//반투명처리에 그림자,배경색 등등의 요소도 고려되어야하는데
//DC를 따로 만들어서 Program::backBuffer 위에 backBuffer,water가 둘 다 반영된 memDC를 
//GdiAlphaBlend를 사용하지 않으면 원하는 느낌이 안나올거같다.
//더구나 water하나때문에 m_Obj만을 위한 DC를 따로 만들어 내고 

#define ALPHA_WATER 50
#define ALPHA_SURFACE 150

#define HEIGHT 4
#define PI 3.1
#define SLICE_DELTA 5

#define MAX_DISTB 3.6
#define MIN_DISTB 2.2


Water::Water( Vector2 pos, Vector2 size)
{
	Set(pos, size);
}

Water::~Water()
{
	delete rect;
	delete renderRect;
		
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

	delete[] centerPoints;

	for (int i = 0; i < right.size(); i++)
	{
		delete right[i];
		delete left[i];
	}

}

void Water::Set( Vector2 pos, Vector2 size)
{
	rect = new Rect(pos, size);
	renderRect = new Rect({ size.x / 2,size.y / 2 }, size);
	
	type = Type::WATER;

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
	elem.height = HEIGHT;
	elem.pi = PI;
	elem.length = 60;
	elem.delta = SLICE_DELTA;						//x방향 미소변위
	elem.sliceCount = (elem.length) / SLICE_DELTA;
	elem.damp = 0.005;								//감쇠상수
	elem.k = elem.pi / elem.length;					//파장관련 상수
	elem.angular = 0.2;								//각속도
	elem.lifespan = 1.4;							//파동의 수명
	elem.h_Angular = PI / elem.lifespan;;			//진폭 시간상수
	elem.pixelPerSec = 30;

	int count = this->rect->size.x / elem.length;
	int odd = (int)this->rect->size.x % elem.length;
	
	mt19937_64 mt(rd());
	
	centerPoints = new POINT[count];
	
	for (int i = 0; i < count; i++)
	{
		uniform_int_distribution<int> dist(0.0, odd);
		int delta = dist(mt);
		centerPoints[i].x = (elem.length * i) + (elem.length * 0.5) + ((odd >= 0) ? delta : 0);
		centerPoints[i].y = elem.height;

		odd -= delta;
	}

	//centerPoint 한개당 풀링용 Wave 좌우 각각 5개씩
	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			right.push_back(new Wave(elem, true));
			left.push_back(new Wave(elem, false));
		}
		
		rotSecRight.assign(count, 0.0);
		rotSecLeft.assign(count, 0.0);
		uniform_real_distribution<double> dist(MIN_DISTB, MAX_DISTB);
		randRotPerRight.emplace_back(dist(mt));
		randRotPerLeft.emplace_back(dist(mt));
	}

}

void Water::Update()
{
	SurfaceRot();

	RectDamp();

	for (int i = 0; i < right.size(); i++)
	{
		right[i]->Update();
	}

	for (int i = 0; i < left.size(); i++)
	{
		left[i]->Update();
	}
}

void Water::Render(HDC hdc)
{
	//memDC
	BitBlt(memDC, 0, 0, rect->size.x, rect->size.y + HEIGHT,
		hdc, rect->LeftTopV().x, rect->LeftTopV().y - HEIGHT,
		SRCCOPY);

	//rectDC
	SelectObject(rectDC, color);
	SelectObject(rectDC, edge);

	BitBlt(rectDC, 0, 0, rect->size.x, rect->size.y,
		hdc, rect->LeftTopV().x, rect->LeftTopV().y ,SRCCOPY);

	//****************************************************
	//까먹은게 있는데 renderRect 표면 오르락내리락 만들고 나서 wave들 위치도 맞춰서 바꿔야됨.
	//기준점 중심으로 위아래 오르락내리락 하게 만들어서 wave.move함수랑 같이 사용해야할듯.
	//*****************************************************
	renderRect->Render(rectDC);
	//transparentDC
	PatBlt(transparentDC, 0, 0, rect->size.x, 2 * HEIGHT, WHITENESS);

	SelectObject(transparentDC, surfaceColor);
	SelectObject(transparentDC, surfaceEdge);

	for (int i = 0; i < right.size(); i++)
	{
		right[i]->Render(transparentDC);
	}
	
	for (int i = 0; i < left.size(); i++)
	{
		left[i]->Render(transparentDC);
	}

	//==========post process============
	//transparentDC는 WHITENESS로 patblt 안하면 원하는데로 출력이 안나옴.
	// 1.bitmap의 디폴트상태가 흰색 or검은색 둘중 하나일줄 알았는데 그게 아닌거같음.
	// 2.surfaceDC위에 transparentDC를 alphaBlend하는 과정에서 transparentDC의 패턴화된 WHITENESS 배경이 넘어가는거같음.
	// 2-2.인줄 알았는데 surfaceAlpha값이 작아지면 whiteness된 색이 그대로 안넘어가서 안지워짐. 
	// surfaceDC,transparentDC 둘 다 whiteness로 patblt해줘야함
	//transparentDC,memDC,rectDC,surfaceDC  <- 이거 세개만 남기고 전부 제거.
	PatBlt(surfaceDC, 0, 0, rect->size.x, 2 * HEIGHT, WHITENESS);

	blendFunc.SourceConstantAlpha = ALPHA_SURFACE;
	GdiAlphaBlend(surfaceDC, 0, 0, rect->size.x, 2 * HEIGHT, transparentDC, 0, 0, rect->size.x, 2 * HEIGHT, blendFunc);

	blendFunc.SourceConstantAlpha = ALPHA_WATER;
	GdiAlphaBlend(memDC, 0, HEIGHT, rect->size.x, rect->size.y, rectDC, 0, 0, rect->size.x,rect->size.y,blendFunc);

	blendFunc.SourceConstantAlpha = ALPHA_SURFACE;
	GdiTransparentBlt(memDC, 0, renderRect->Top() , rect->size.x, 2 * HEIGHT, surfaceDC, 0, 0, rect->size.x, 2 * HEIGHT, WHITE);
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
	return this->renderRect;
}

void Water::SurfaceRot()
{
	for (int i = 0; i < rotSecRight.size(); i++)
	{
		rotSecRight[i] += TIMER->GetElapsedTime();

		if (rotSecRight[i] >= randRotPerRight[i])
		{
			mt19937_64 gen(rd());
			uniform_real_distribution<double> dist(MIN_DISTB, MAX_DISTB);

			for (int j = 0; j < right.size(); j++)
			{
				if (right[j]->GetActive() == false)
				{
					right[j]->SetActive(true);
					right[j]->SetCenter(centerPoints[i]);
					break;
				}
			}

			rotSecRight[i] = 0;
			randRotPerRight[i] = dist(gen);
		}
	}

	for (int i = 0; i < rotSecLeft.size(); i++)
	{
		rotSecLeft[i] += TIMER->GetElapsedTime();

		if (rotSecLeft[i] >= randRotPerLeft[i])
		{
			mt19937_64 gen(rd());
			uniform_real_distribution<double> dist(MIN_DISTB, MAX_DISTB);

			for (int j = 0; j < left.size(); j++)
			{
				if (left[j]->GetActive() == false)
				{
					left[j]->SetActive(true);
					left[j]->SetCenter(centerPoints[i]);
					break;
				}
			}

			rotSecLeft[i] = 0;
			randRotPerLeft[i] = dist(gen);
		}
	}
}

void Water::RectDamp()
{
	double runTime = TIMER->GetRunTime();
	double del = sin(PI * runTime) ;
	del = 12.0 * del * del;				//파고 = 12.0 ,별 생각없음 그냥 이게 적당해보여서

	renderRect->SetRect(0.0, del, rect->size.x, rect->size.y);
}


