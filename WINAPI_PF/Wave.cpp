#include "Framework.h"
#include "Wave.h"

Wave::Wave(WaveElem elem,POINT center)
	:elem(elem),isActive(false),center(center),runTime(0.0)
{
	wave = new POINT[elem.sliceCount * 2];

	wave[0].x = center.x;
	wave[0].y = elem.height;

	wave[elem.sliceCount].x = center.x;
	wave[elem.sliceCount].y = elem.height;

	for (int i = 1; i <= elem.sliceCount * 0.5; i++)
	{
		wave[i].x = center.x - elem.delta * i;
		wave[i].y = center.y;

		wave[elem.sliceCount - i].x = center.x - elem.delta * i;
		wave[elem.sliceCount - i].y = center.y;

		wave[2 * elem.sliceCount - i].x = center.x + elem.delta * i;
		wave[2 * elem.sliceCount - i].y = center.y;

		wave[elem.sliceCount + i].x = center.x + elem.delta * i;
		wave[elem.sliceCount + i].y = center.y;
	}
}

Wave::~Wave()
{
	delete[] wave;
}

void Wave::Update()
{
	if (isActive == false)
		return;

	runTime += TIMER->GetElapsedTime();

	Move(isRight == true ? runTime : -runTime);
	Damping();

	if (runTime >= elem.lifespan)
	{
		runTime = 0;
		isActive = false;
	}
}

void Wave::Render(HDC hdc)
{
	if (isActive == false)
		return;

	Polygon(hdc, wave, elem.sliceCount * 2);
}

void Wave::Damping()
{
	double h = elem.height;
	double h_Sine = sin(elem.h_Angular * runTime);
	double k_Sine = sin(elem.k * wave[0].x);

	wave[0].y = h * h_Sine * k_Sine;
	wave[elem.sliceCount].y = -h * h_Sine * k_Sine;

	for (int i = 1; i <= elem.sliceCount * 0.5; i++)
	{
		h = elem.height;
		h_Sine = sin(elem.h_Angular * runTime);
		k_Sine = sin(elem.k * wave[i].x);

		h = h * h_Sine * k_Sine;
		wave[i].y = h;
		wave[elem.sliceCount - i].y = -h;

		wave[2 * elem.sliceCount - i].y = h;
		wave[elem.sliceCount + i].y = -h;
	}

}

void Wave::Move(int deltaX, int deltaY)
{
	wave[0].x += deltaX;
	wave[0].y += deltaY;
	wave[elem.sliceCount].x += deltaX;
	wave[elem.sliceCount].y += deltaY;


	for (int i = 1; i <= elem.sliceCount * 0.5; i++)
	{
		wave[i].x += deltaX;
		wave[i].y += deltaY;

		wave[elem.sliceCount * 2 - i].x += deltaX;
		wave[elem.sliceCount * 2 - i].y += deltaY;

		wave[(int)(elem.sliceCount * 0.5) + i].x += deltaX;
		wave[(int)(elem.sliceCount * 0.5) + i].y += deltaY;

		wave[elem.sliceCount + i].x += deltaX;
		wave[elem.sliceCount + i].y += deltaY;
	}
}
