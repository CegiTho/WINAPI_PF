// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
#include <windows.h>

#include <cassert>

#include <string>
#include <map>
#include <vector>
#include <time.h>
#include <cmath>
#include <functional>
#include <queue>

#include <Ole2.h>
#include <gdiplus.h>

#pragma comment(lib,"Gdiplus.lib")

#include "inc/fmod.hpp"
#pragma comment(lib,"lib/x64/fmod_vc.lib")

#pragma comment(lib,"Msimg32.lib")



using namespace std;

#define WIN_START_X 100
#define WIN_START_Y 100

#define WIN_WIDTH 2200
#define WIN_HEIGHT 1300

#define CENTER_X WIN_WIDTH * 0.5
#define CENTER_Y WIN_HEIGHT * 0.5

#define PI 3.141592



#define RADIAN 180/PI

#define RED RGB(255, 0, 0)
#define GREEN RGB(0, 255, 0)
#define BLUE RGB(0, 0, 255)
#define MAGENTA RGB(255, 0, 255)
#define YELLOW RGB(255, 255, 0)
#define CYAN RGB(0, 255, 255)
#define WHITE RGB(255, 255, 255)
#define BLACK RGB(0, 0, 0)
#define GRAY RGB(128,128,128)

#define LERP(s,e,t) s + (e - s) * t

#define KEYBOARD Keyboard::Get()
//#define KEYBOARD SyncKeyboard::Get()
#define TIMER Timer::Get()

#define KEYDOWN(k) Keyboard::Get()->Down(k)
#define KEYUP(k) Keyboard::Get()->Up(k)
#define KEYPRESS(k) Keyboard::Get()->Press(k)

#define DELTA TIMER->GetElapsedTime()

#define TEX TextureManager::Get()
#define SOUND SoundManager::Get()
#define CAM Camera::Get()
#define M_CAM MasterCamera::Get()
#define SCENE SceneManager::Get()


/*
SCAM이 실질적인 카메라이고 내가 원하는데로 동작하는 객체임.
게임중에는 캐릭터에 빙의(Possession)되어서 따라 움직이는데 겜 시작전에는 맵에서
골인지점 - 코너 - 코너 - 캐릭터 순으로 맵 전체를 한번 훑어주는 연출이 필요함. 
해당 경로는 SCAM의 prePath라는 멤버로 나타나며 각 joint지점 n개가 이루는 n+1차 베지어곡선으로 그릴 생각.

*/



//Framework Header
#include "Vector2.h"
#include "Object.h"
#include "Line.h"
#include "Rect.h"
#include "Circle.h"
#include "Polygon2.h"

#include "RectAnimation.h"

#include "Timer.h"
#include "Keyboard.h"
#include "SyncKeyboard.h"

#include "Xml.h"

#include "Math.h"

#include "Texture.h"
#include "Bitmap.h"
#include "Plusmap.h"
#include "Animation.h"
#include "TextureManager.h"

#include "SoundManager.h"
#include "SceneManager.h"

#include "MasterCamera.h"
#include "Camera.h"


//Object Header
#include "TextureRect.h"


//PF Object Header
#include "PreDefined.h"
#include "Enum.h"
#include "T_Object.h"


#include "Character.h"
#include "Thomas.h"
#include "Clare.h"
#include "Chris.h"
#include "James.h"
#include "John.h"
#include "Laura.h"
#include "Sarah.h"

#include "Goal.h"

#include "Shade.h"

#include "Obstacle.h"
#include "NormalObstacle.h"

#include "CharacterManager.h"
#include "ObstacleManager.h"
#include "GoalManager.h"
#include "ObjManager.h"
#include "ShadeManager.h"

//Scene Header
#include "Scene.h"
#include "Program.h"


extern Vector2 mousePos;
extern HWND hWnd;
extern HINSTANCE hInst;
