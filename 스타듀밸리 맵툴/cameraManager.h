#pragma once
#include "singletonBase.h"

class cameraManager : public singletonBase<cameraManager>
{
public:
	typedef struct tagCameraInfo
	{
		HDC		hMemDC;		//메모리 DC
		HBITMAP hBit;		//비트맵
		HBITMAP hOBit;		//올드 비트맵
		float	x;			//카메라 X좌표 (left)
		float	y;			//카메라 Y좌표 (top)
		int		width;		//가로 크기(카메라)
		int		height;		//세로 크기(카메라)

		int		groundWidth;	//배경 총 가로크기
		int		groundHeight;	//배경 총 세로크기
		bool	istrans;
		float	magnification;	
		COLORREF transColor;

		
		tagCameraInfo()
		{
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			x = 0;
			istrans = NULL;
			y = 0;
			width = 0;
			height = 0;
			groundWidth = 0;
			groundHeight = 0;
			magnification = 1;
			transColor = RGB(255, 0, 255);
		}
	}CAMERA_INFO, *LPCAMERA_INFO;

private:
	LPCAMERA_INFO	_cameraInfo;		//카메라 정보 구조체
	LPCAMERA_INFO   _tempInfo;
	BLENDFUNCTION   _blendfuntion;
public:
	cameraManager();
	~cameraManager();

	HRESULT init(int groundTotalWidth, int groundTotalHeight, int cameraWidth, int cameraHeight, float x = 0, float y = 0, float magnification = 1);
	void release();
	void cameraMove(int focusX, int focusY);
	void render(HDC hdc);
	void render(HDC hdc, int  destX, int destY, int sourX, int sourY);
	void strechRender(HDC hdc, int destX, int destY, int sizeX, int sizeY);

	inline HDC getMemDC() { return _cameraInfo->hMemDC; }
	inline float getX() { return _cameraInfo->x; }
	inline float getY() { return _cameraInfo->y; }
	inline void setMagnification(float mag) { _cameraInfo->magnification = mag; }
	inline float getGroundX() { return _cameraInfo->groundWidth; }
	inline float getGroundY() { return _cameraInfo->groundHeight; }
};