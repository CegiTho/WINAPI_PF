#include "Framework.h"
#include "Wave.h"

Wave::Wave(WaveElem elem, bool isRight)
	:elem(elem), isActive(false), center{ 0,0 }, runTime(0.0), isRight(isRight), oneSec(0.0)
{
	wave = new POINT[elem.sliceCount * 2];
	origin = new POINT[elem.sliceCount * 2];

	wave[0].x = center.x;
	wave[0].y = elem.height;
	wave[elem.sliceCount].x = center.x;
	wave[elem.sliceCount].y = elem.height;

	for (int i = 1; i <= elem.sliceCount * 0.5; i++)
	{
		wave[i].x = center.x - elem.delta * i;
		wave[i].y = elem.height;

		wave[elem.sliceCount - i].x = center.x - elem.delta * i;
		wave[elem.sliceCount - i].y = elem.height;

		wave[elem.sliceCount + i].x = center.x + elem.delta * i;
		wave[elem.sliceCount + i].y = elem.height;

		wave[2 * elem.sliceCount - i].x = center.x + elem.delta * i;
		wave[2 * elem.sliceCount - i].y = elem.height;

	}


	origin[0].x = elem.length * 0.5;
	origin[0].y = -elem.height;

	origin[(int)(elem.sliceCount * 0.5)].x = 0;
	origin[(int)(elem.sliceCount * 0.5)].y = 0;

	origin[elem.sliceCount].x = elem.length * 0.5;
	origin[elem.sliceCount].y = elem.height;

	origin[(int)(elem.sliceCount * 1.5)].x = elem.length;
	origin[(int)(elem.sliceCount * 1.5)].y = 0;

	for (int i = 1; i < elem.sliceCount * 0.5; i++)
	{
		double h = elem.height * cos(elem.k * (elem.delta * i));

		origin[i].x = elem.length * 0.5 - elem.delta * i;
		origin[i].y = -h;

		origin[elem.sliceCount - i].x = elem.length * 0.5 - elem.delta * i;
		origin[elem.sliceCount - i].y = +h;

		origin[elem.sliceCount * 2 - i].x = elem.length * 0.5 + elem.delta * i;
		origin[elem.sliceCount * 2 - i].y = -h;

		origin[elem.sliceCount + i].x = elem.length * 0.5 + elem.delta * i;
		origin[elem.sliceCount + i].y = +h;
	}
}

Wave::Wave(WaveElem elem, POINT center, bool isRight)
	:elem(elem), isActive(false), center(center), runTime(0.0), isRight(isRight), oneSec(0.0)
{
	wave = new POINT[elem.sliceCount * 2];
	origin = new POINT[elem.sliceCount * 2];

	wave[0].x = center.x;
	wave[0].y = elem.height;
	wave[elem.sliceCount].x = center.x;
	wave[elem.sliceCount].y = elem.height;

	for (int i = 1; i <= elem.sliceCount * 0.5; i++)
	{
		wave[i].x = center.x - elem.delta * i;
		wave[i].y = elem.height;

		wave[elem.sliceCount - i].x = center.x - elem.delta * i;
		wave[elem.sliceCount - i].y = elem.height;

		wave[elem.sliceCount + i].x = center.x + elem.delta * i;
		wave[elem.sliceCount + i].y = elem.height;

		wave[2*elem.sliceCount - i].x = center.x + elem.delta * i;
		wave[2 * elem.sliceCount - i].y = elem.height;

	}

	origin[0].x = elem.length * 0.5;
	origin[0].y = -elem.height;

	origin[(int)(elem.sliceCount * 0.5)].x = 0;
	origin[(int)(elem.sliceCount * 0.5)].y = 0;

	origin[elem.sliceCount].x = elem.length * 0.5;
	origin[elem.sliceCount].y = elem.height;

	origin[(int)(elem.sliceCount * 1.5)].x = elem.length;
	origin[(int)(elem.sliceCount * 1.5)].y = 0;

	for (int i = 1; i < elem.sliceCount * 0.5; i++)
	{
		double h = elem.height * cos(elem.k * (elem.delta * i));

		origin[i].x = elem.length * 0.5 - elem.delta * i;
		origin[i].y =  - h;

		origin[elem.sliceCount - i].x = elem.length * 0.5 - elem.delta * i;
		origin[elem.sliceCount - i].y =  + h;

		origin[elem.sliceCount * 2 - i].x = elem.length * 0.5 + elem.delta * i;
		origin[elem.sliceCount * 2 - i].y =  - h;

		origin[elem.sliceCount + i].x = elem.length * 0.5 + elem.delta * i;
		origin[elem.sliceCount + i].y =  + h;
	}
}

Wave::~Wave()
{
	delete[] wave;
	delete[] origin;
}

void Wave::Update()
{
	if (isActive == false)
		return;

	runTime += TIMER->GetElapsedTime();
	oneSec += TIMER->GetElapsedTime();

	double sec = (double)(1 / elem.pixelPerSec);
	if (oneSec >= sec)
	{
		Move(isRight == true ? 1 : -1);
		oneSec -= sec;
	}
	Damping();

	if (runTime >= elem.lifespan)
	{
		runTime = 0.0;
		isActive = false;

		//Move(isRight == true ? -center.x : center.x);
	}

}

void Wave::Damping()
{
	double h_Sine = sin(elem.h_Angular * runTime);
	h_Sine *= h_Sine;
	wave[0].y = h_Sine * origin[0].y + elem.height;
	wave[(int)(elem.sliceCount * 0.5)].y = elem.height;
	wave[elem.sliceCount].y = h_Sine * origin[elem.sliceCount].y + elem.height;
	wave[(int)(elem.sliceCount * 1.5)].y = elem.height;

	for (int i = 1; i < elem.sliceCount * 0.5; i++)
	{
		wave[i].y = origin[i].y * h_Sine + elem.height;
		wave[elem.sliceCount * 2 - i].y = origin[elem.sliceCount * 2 - i].y * h_Sine + elem.height;
		wave[elem.sliceCount - i].y = origin[elem.sliceCount - i].y * h_Sine + elem.height;
		wave[elem.sliceCount + i].y = origin[elem.sliceCount + i].y * h_Sine + elem.height;
	}
}

void Wave::Render(HDC hdc)
{
	if (isActive == false)
		return;

	Polygon(hdc, wave, elem.sliceCount * 2);
}

void Wave::Move(int deltaX, int deltaY)
{
	for(int i = 0 ; i < elem.sliceCount * 2 ; i++)
	{
		wave[i].x += deltaX;
		wave[i].y += deltaY;
	}
}

void Wave::SetCenter(POINT center)
{
	wave[0].x = center.x;
	wave[0].y = elem.height;
	wave[elem.sliceCount].x = center.x;
	wave[elem.sliceCount].y = elem.height;

	for (int i = 1; i <= elem.sliceCount * 0.5; i++)
	{
		wave[i].x = center.x - elem.delta * i;
		wave[i].y = elem.height;

		wave[elem.sliceCount - i].x = center.x - elem.delta * i;
		wave[elem.sliceCount - i].y = elem.height;

		wave[elem.sliceCount + i].x = center.x + elem.delta * i;
		wave[elem.sliceCount + i].y = elem.height;

		wave[2 * elem.sliceCount - i].x = center.x + elem.delta * i;
		wave[2 * elem.sliceCount - i].y = elem.height;
	}
}