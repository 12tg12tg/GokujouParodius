// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <string>

using namespace std;

//=======================//
//			STL			//
//=====================//
#include<map>
#include<vector>


//=======================//
//	내가만든 헤더파일		//
//=====================//
#include"commonMacroFunction.h"
#include"Input.h"
#include"imageManager.h"
#include"timeManager.h"
#include"randomFunction.h"
#include"utils.h"
#include"txtData.h"

//=======================//
//		Manager			//
//=====================//
#define InputManager	Input::getSingleton()
#define RND				RandomFunction::getSingleton()
#define IMAGE			imageManager::getSingleton()
#define TIME			timeManager::getSingleton()
#define TXT				txtData::getSingleton()

//===================//
//	매크로 설정부분	//
//=================//

#define WINNAME			(LPTSTR)(TEXT("극상 파로디우스"))
#define WINSTARTX		100//시작점
#define WINSTARTY		100
#define WINSIZEX		1024
#define WINSIZEY		768
#define WINSTYLE		WS_CAPTION | WS_SYSMENU


//===========================//
//	메인게임 릴리즈에서 사용	//
//=========================//

#define SAFE_DELETE(p) {if(p) {delete p; (p) = nullptr;}}


//===============================================//
//	전역변수 (인스턴스, 윈도우 핸들, 마우스 좌표)	//
//=============================================//

extern HINSTANCE m_hInstance;
extern HWND m_hWnd;
extern POINT m_ptMouse;