﻿// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <SDKDDKVer.h>

//디버깅용 (주석치면 콘솔창이 사라진다)
//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:

#include <Windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>
// C++ 런타임 헤더 파일입니다.
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
//csv 읽기용 헤더
#include <iostream>
#include <fstream>
#include <sstream>
#include <istream>
using namespace std;

// 자주사용하는 STL
#include <string>
#include <vector>
#include <map>
#include <list>

//=============================================================
//	## 내가 만든 헤더파일을 이곳에 추가한다 ##
//=============================================================
#include "commonMacroFunction.h"
#include "input.h"
#include "random.h"
#include "imageManager.h"
#include "util.h"
using namespace MY_UTIL;
#include "playerData.h"
#include "sceneManager.h"
#include "iniData.h"
#include "soundManager.h"
#include "timeManager.h"
#include "resource.h"
#include "cameraManager.h"
#include "player.h"
#include "itemManager.h"
#include "switchSceneManager.h"
#include "effectManager.h"
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")


//=============================================================
//	## 싱글톤을 추가한다 ##
//=============================================================
#define INPUT input::getSingleton() //세미콜론 찍으면 작동안함
#define RANDOM random::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()
#define PLAYERDATA playerData::getSingleton()
#define SCENEMANAGER sceneManager::getSingleton()
#define INIDATA iniData::getSingleton()
#define SOUNDMANAGER soundManager::getSingleton()
#define TIME timeManager::getSingleton()
#define CAMERAMANAGER cameraManager::getSingleton()
#define PLAYER player::getSingleton()
#define ITEMMANAGER itemManager::getSingleton()
#define SWITCHMANAGER switchSceneManager::getSingleton()
#define EFFECTMANAGER effectManager::getSingleton()

//=============================================================
//	## 디파인문 ## (윈도우창 초기화)
//=============================================================
#define WINNAME (LPTSTR)(TEXT("스타듀밸리 - 김현정, 최동건, 김재현, 김의겸 "))
#define WINSTARTX	100
#define WINSTARTY	0
#define WINSIZEX		1200
#define WINSIZEY		600
#define WINSTYLE		WS_CAPTION | WS_SYSMENU

//=============================================================
//	## 매크로함수 ## (클래스에서 동적할당된 부분 해제)
//=============================================================
#define SAFE_DELETE(p)		{if(p) {delete (p); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = NULL;}}

//=============================================================
//	## 전역변수 ##
//=============================================================
extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern POINT		_ptMouse;
extern INT			_mouseWheel;
