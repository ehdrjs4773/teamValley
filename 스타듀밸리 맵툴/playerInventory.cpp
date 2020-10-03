#include "stdafx.h"
#include "playerInventory.h"

HRESULT playerInventory:: init()
{

	for (int i = 0; i < 12; i++)
	{
		_playerTool[i] = RectMake(333 + i * 45, 535, 40, 40);
	}

	return S_OK;
};


void playerInventory::release()
{

};


void playerInventory::update()
{
	cout << _ptMouse.x << "\t" << _ptMouse.y << endl;

	for (int i = 0; i < 12; i++)
	{
		if (PtInRect(&_playerTool[i], _ptMouse))
		{
			if(INPUT->GetKeyDown(VK_LBUTTON))
			{
				//if (_playerTool[i] == //µµ³¢)
				//{
				//	
				//}

				//else if (_playerTool[i] == //°î±ªÀÌ)
				//{

				//}

				//else if (_playerTool[i] == //»ð)
				//{

				//}

				//else if (_playerTool[i] == //ÁÖÀüÀÚ)
				//{

				//}

				//else if (_playerTool[i] == //³´)
				//{

				//}
			}
		}
	}
};

void playerInventory::render()
{
		IMAGEMANAGER->render("playerInventory", getMemDC(),WINSIZEX/2 - 282, 520);

		for (int i = 0; i < 12; i++)
		{
			Rectangle(getMemDC(), _playerTool[i]);
			if (PtInRect(&_playerTool[i], _ptMouse))
			{
				RECT temp{ _playerTool[i].left,_playerTool[i].top,_playerTool[i].right,_playerTool[i].bottom };
				FrameRect(getMemDC(), temp, RGB(255, 0, 0));
			}
		}

};