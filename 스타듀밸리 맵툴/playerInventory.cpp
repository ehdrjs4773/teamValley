#include "stdafx.h"
#include "playerInventory.h"





HRESULT playerInventory:: init()
{



	_player = new player;
	_player->init();

	 _playerInventory = RectMakeCenter( 100, 100, 208, 32);

	 for (int i = 0; i < 12; i++)
	 {
		 _playerTool[i] = RectMakeCenter(CAMERAMANAGER->getX()+200+(i*16), CAMERAMANAGER->getY()+550,16,16);
	 }








	return S_OK;
};


void playerInventory::release()
{






};


void playerInventory::update()
{


	for (int i = 0; i < 12; i++)
	{
		_playerTool[i] = RectMakeCenter(CAMERAMANAGER->getX() + 200 + (i * 16), CAMERAMANAGER->getY() + 550, 16, 16);
	}


	std::cout << _playerTool[0].top<<"  "<< _playerTool[0].left << endl;





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


		IMAGEMANAGER->render("playerInventory", CAMERAMANAGER->getMemDC(),_playerInventory.left, _playerInventory.top);


		for (int i = 0; i < 12; i++)
		{
			Rectangle(CAMERAMANAGER->getMemDC(), _playerTool[i]);

			/*if (PtInRect(&_playerTool[i], _ptMouse))
			{
				RECT temp{ _playerTool[i].left,_playerTool[i].top,_playerTool[i].right,_playerTool[i].bottom };
				FrameRect(CAMERAMANAGER->getMemDC(), temp, RGB(255, 0, 0));
			}*/
		}

};