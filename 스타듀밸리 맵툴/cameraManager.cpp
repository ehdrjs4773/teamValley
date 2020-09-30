#include "stdafx.h"
#include "cameraManager.h"



cameraManager::cameraManager()
	: _cameraInfo(NULL)
{
}

cameraManager::~cameraManager()
{
}

HRESULT cameraManager::init(int groundTotalWidth, int groundTotalHeight, int cameraWidth, int cameraHeight, float x, float y, float magnification)
{
	if (_cameraInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);
	_cameraInfo = new CAMERA_INFO;
	_cameraInfo->hMemDC = CreateCompatibleDC(hdc);
	_cameraInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, groundTotalWidth, groundTotalHeight);
	_cameraInfo->hOBit = (HBITMAP)SelectObject(_cameraInfo->hMemDC, _cameraInfo->hBit);
	_cameraInfo->width = cameraWidth / magnification;
	_cameraInfo->height = cameraHeight / magnification;
	_cameraInfo->groundWidth = groundTotalWidth;
	_cameraInfo->groundHeight = groundTotalHeight;
	_cameraInfo->magnification = magnification;

	if (_cameraInfo->hBit == NULL)
	{
		release();
		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

void cameraManager::release()
{
	//이미지정보가 있다면
	if (_cameraInfo)
	{
		SelectObject(_cameraInfo->hMemDC, _cameraInfo->hOBit);
		DeleteObject(_cameraInfo->hBit);
		DeleteDC(_cameraInfo->hMemDC);

		SAFE_DELETE(_cameraInfo);
	}
}

void cameraManager::cameraMove(int focusX, int focusY)
{
	_cameraInfo->x = focusX - _cameraInfo->width / 2;
	_cameraInfo->y = focusY - _cameraInfo->height / 2;

	if (_cameraInfo->x < 0)
		_cameraInfo->x = 0;
	if (_cameraInfo->x + _cameraInfo->width > _cameraInfo->groundWidth)
		_cameraInfo->x = _cameraInfo->groundWidth - _cameraInfo->width;
	if (_cameraInfo->y < 0)
		_cameraInfo->y = 0;
	if (_cameraInfo->y + _cameraInfo->height > _cameraInfo->groundHeight)
		_cameraInfo->y = _cameraInfo->groundHeight - _cameraInfo->height;
}

void cameraManager::render(HDC hdc)
{
	GdiTransparentBlt(
		hdc,               //복사될 영역의 DC
		0,                  //복사될 좌표 X
		0,                  //복사될 좌표 Y
		WINSIZEX,            //복사될 크기(가로)
		WINSIZEY,            //복사될 크기(세로)
		_cameraInfo->hMemDC,            //복사해올 DC
		_cameraInfo->x, _cameraInfo->y,      //복사해올 좌표X,Y
		_cameraInfo->width,               //복사해올 크기
		_cameraInfo->height,            //복사해올 크기
		RGB(255,0,255));      //복사해올때 어떤 컬러를 빼고 가져올꺼냐
}

void cameraManager::render(HDC hdc, int  destX, int destY, int sourX, int sourY)
{
	GdiTransparentBlt(
		hdc,               //복사될 영역의 DC
		destX,                  //복사될 좌표 X
		destY,                  //복사될 좌표 Y
		_cameraInfo->width,            //복사될 크기(가로)
		_cameraInfo->height,            //복사될 크기(세로)
		_cameraInfo->hMemDC,            //복사해올 DC
		sourX, sourY,      //복사해올 좌표X,Y
		_cameraInfo->width,               //복사해올 크기
		_cameraInfo->height,            //복사해올 크기
		RGB(255, 0, 255));      //복사해올때 어떤 컬러를 빼고 가져올꺼냐
}

void cameraManager::strechRender(HDC hdc, int destX, int destY, int sizeX, int sizeY)
{

	if (!_tempInfo) CAMERA_INFO();
	SetStretchBltMode(hdc, COLORONCOLOR);

	if (_cameraInfo->istrans)
	{
		BitBlt(_tempInfo->hMemDC, 0, 0,
			sizeX,
			sizeY,
			hdc, 0, 0, SRCCOPY);

		StretchBlt(
			_tempInfo->hMemDC,
			0, 0,
			sizeX, sizeY,
			_cameraInfo->hMemDC,
			0, 0,
			_cameraInfo->width,
			_cameraInfo->height,
			SRCCOPY
		);

		GdiTransparentBlt(
			hdc, destX, destY,
			sizeX,
			sizeY,
			_tempInfo->hMemDC,
			0, 0,
			sizeX,
			sizeY,
			_cameraInfo->transColor
		);
	}
	else
	{
		StretchBlt(
			hdc,
			destX,
			destY,
			sizeX,
			sizeY,
			_cameraInfo->hMemDC,
			0,
			0,
			_cameraInfo->groundWidth,
			_cameraInfo->groundHeight,
			SRCCOPY
		);
	}
}