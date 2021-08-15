#include "Framework.h"

Camera::Camera()
	:speed(10),target(nullptr),offset(CENTER_X,CENTER_Y)
{
	rect = new Rect(Vector2(0, 0), { WIN_WIDTH,WIN_HEIGHT });

}

Camera::~Camera()
{
	delete rect;
}

void Camera::Update()
{
	if (target != nullptr)
	{
		//offset�� target�� ��¹����� �߾ӿ� ��ġ�ϵ��� ����.
		//destPos�� ��ǻ� ī�޶� ȭ�� ��� ���������� ������.
		Vector2 destPos = { target->center.x - offset.x,target->center.y - offset.y };
	
		//		ī�޶� ���� ������ ������ ��Ȳ ����ó��
		if (destPos.x < left)
			destPos.x = left;
		else if (destPos.x > right - rect->size.x)
			destPos.x = right - rect->size.x;
		
		if (destPos.y < top)
			destPos.y = top;
		else if (destPos.y > bottom - rect->size.y)
			destPos.y = bottom - rect->size.y;
		//====================================================
		
		Vector2 pos = LERP(rect->center, destPos, DELTA * speed);

		rect->center = pos;
	}
	else	//free camera
	{
		if (KEYPRESS('A'))
		{
			rect->center.x -= speed * DELTA;

			if (rect->center.x < left)
				rect->center.x = left;
		}
		if (KEYPRESS('D'))
		{
			rect->center.x += speed * DELTA;
			
			if (rect->center.x > right - rect->size.x)
				rect->center.x = right - rect->size.x;
		}
		if (KEYPRESS('S'))
		{
			rect->center.y += speed * DELTA;

			if (rect->center.y > bottom - rect->size.y)
				rect->center.y = right - rect->size.y;
		}
		if (KEYPRESS('W'))
		{
			rect->center.y -= speed * DELTA;

			if (rect->center.y < top)
				rect->center.y = top;
		}
	}

}

void Camera::SetMapSize(double left, double right, double top, double bottom)
{
	this->left = left;
	this->right = right;
	this->top = top;
	this->bottom = bottom;
}
