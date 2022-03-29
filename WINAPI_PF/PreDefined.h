#pragma once

//=======Character=============
#define PickTriangle 12

#define THOMAS_SIZE {30,45}
#define THOMAS_COLOR RGB(178,69,54)
#define THOMAS_THRUST 500
#define THOMAS_START {300,300}

#define CHRIS_SIZE {25,25}
#define CHRIS_COLOR RGB(178,116,60)
#define CHRIS_THRUST 550
#define CHRIS_START {500,300}

#define CLARE_SIZE {100,100}
#define CLARE_COLOR RGB(36,62,96)
#define CLARE_THRUST 350
#define CLARE_START {700,300}

#define JAMES_SIZE {30,45}
#define JAMES_COLOR RGB(45,134,61)
#define JAMES_THRUST 500
#define JAMES_START {900,300}

#define JOHN_SIZE {22,100}
#define JOHN_COLOR RGB(176,158,60)
#define JOHN_THRUST 700
#define JOHN_START {1100,300}

#define LAURA_SIZE {100,22}
#define LAURA_COLOR RGB(165,55,83)
#define LAURA_THRUST 400
#define LAURA_START {1300,300}
#define LAURA_ADD_THRUST 300

#define SARAH_SIZE {20,30}
#define SARAH_COLOR RGB(64,33,99)
#define SARAH_THRUST 490
#define SARAH_START {1500,300}

//==========Moving=============
#define SPEED 400
#define GRAVITY 980

//==========Obstacle===========
#define SPIKE_WIDTH 18
#define SPIKE_HEIGHT 24


//==========Shade=============
#define ShadeLength 5000
#define ALPHA 90

#define BG_COLOR_1 RGB(39,25,24)
#define BG_COLOR_2 RGB(33,51,54)
#define BG_COLOR_3 RGB(36,37,25)
//#define BG_COLOR_4 RGB(21,25,47)   //4-6
#define BG_COLOR_4 RGB(60,60,35)
#define BG_COLOR_5 RGB(34,42,45)

#define SYMBOL_INTERVAL 70
#define SYMBOL_SIZE 12

#define EPSILON 1
//menuCellSize 는 고정, x값 위치도 고정임. y값은 menuCell갯수에 따라 다르게,
//boxSize는 (menuCell위치,여백,화면 오른쪽 끝까지 닿도록) x값 정한거고 y값도 위아래 여백 고려한거임.
#define MENUCELL_SIZE_X 700
#define MENUCELL_SIZE_Y 35

#define MENUCELL_POS_X 1300

#define SELECTED_BOX_SIZE {700,70}

struct WaveElem
{
	int time;		

	int	height;				//5
	int length;				//60 정도
	int sliceCount;			//length / sliceDelta		
	double pixelPerSec;		//1초에 몇 픽셀씩 이동하는지
	double lifespan;		//3초정도	//수명. 진폭 0 에서 height까지 sine형으로 증가했다가 다시 0으로 sine형으로 감소
	double pi;				//3.1 or 3.14
	double delta;			//1~3 사이 적절한 값	x방향 미소변위
	double damp;			//	감쇠상수
	double k;				//pi/length		파장관련 상수
	double angular;			//		각속도
	double h_Angular;		//pi / time		진폭 시간상수
};