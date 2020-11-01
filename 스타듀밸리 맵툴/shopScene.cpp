#include "stdafx.h"
#include "shopScene.h"

HRESULT shopScene::init()
{
	CAMERAMANAGER->init(1600, 1600, 480, 240);
	CAMERAMANAGER->cameraMove(PLAYER->getCenterX(), PLAYER->getCenterY());

	_itemShop = new shop;
	_itemShop->init(ITEM_NPC);

	_isShopClicked = false;

	_pos.x = 270;
	_pos.y = 310;

	_rc_player = RectMake(_pos.x, _pos.y, 16, 32);

	_itemNpc = new npc;
	_itemNpc->init(ITEM_NPC);

	_itemNpc->setPos(270, 220);

	_npcPtr = _itemNpc;

	if (SOUNDMANAGER->isPlaySound("농장"))
	{
		SOUNDMANAGER->stop("농장");
	}
	//대화창 출력 기준
	_isTalk = false;
	//대화 저장
	memset(temp_script, 0, sizeof(temp_script));
	temp_script[0] = "환영합니다. 여러가지 팔고 있으니 둘러보세요.";
	temp_script[1] = "다음에 또 오세요 ~";
	
	for (int i = 0; i < 10; i++)
	{
		if (temp_script[i] == NULL) break;
		script.push_back(temp_script[i]);
	}

	script_count = 0;
	this->update();
	return S_OK;
}

void shopScene::release()
{
	//_shop->release();
}

void shopScene::update()
{
	if (!SOUNDMANAGER->isPlaySound("town"))
	{
		SOUNDMANAGER->play("town", 0.05f);
	}


	_itemNpc->update();
	if (_isTalk)
	{
		if (INPUT->GetKeyDown(VK_LBUTTON))
		{
			script_count++;
			if (script_count == 1)
			{
				_isTalk = false;
				_isShopClicked = true;
			}
			else if (script_count > 1)
			{
				script_count = 0;
				_isTalk = false;
			}
		}
	}
	else
	{
		//상점 나가기 포탈
		if (PLAYER->getCenterY() >= 338)
		{
			if (!SWITCHMANAGER->getFade())
			{
				SOUNDMANAGER->play("doorOpen", 0.2f);
				SWITCHMANAGER->changeScene("인게임화면");
				SWITCHMANAGER->startFade(640.0f, 224.0f);
			}
		}

		if (_isShopClicked)
		{
			_itemShop->update();
			_isShopClicked = !_itemShop->shopClose();
			PLAYER->getInventory()->isShopOpen(_isShopClicked);
			if (_itemShop->shopClose())
			{
				_isTalk = true;
			}
		}
		else
		{
			PLAYER->update();

			if (!PLAYER->getIsShowInventory())
			{
				playerMove();
			}

			_itemNpc->update();
			setCurrentSlotNumber(_mouseWheel);


			_rc_player = RectMake(_pos.x, _pos.y, 16, 32);

			temp.x = CAMERAMANAGER->getX() + (float)_ptMouse.x / (float)WINSIZEX * 480;
			temp.y = CAMERAMANAGER->getY() + (float)_ptMouse.y / (float)WINSIZEY * (float)230;

			if (PtInRect(&_itemNpc->getRC(), temp))
			{
				if (INPUT->GetKeyDown(VK_LBUTTON))
				{
					//_isShopClicked = true;
					_isTalk = true;
				}
			}
			CAMERAMANAGER->cameraMove(PLAYER->getCenterX(), PLAYER->getCenterY());
		}
	}

}

void shopScene::render()
{
	IMAGEMANAGER->render("상점실내", CAMERAMANAGER->getMemDC());
	bool isFront = true;

	if (_npcPtr->getPos().x <= PLAYER->getCenterX() + 8 && _npcPtr->getPos().x + 16 >= PLAYER->getCenterX() - 8)
	{
		if (_npcPtr->getPos().y <= PLAYER->getCenterY() - 16)
		{
			isFront = true;
		}
		else
		{
			isFront = false;
		}
	}

	if (isFront == false) PLAYER->render();
	
	_npcPtr->render();

	if (isFront == true) PLAYER->render();

	if (PLAYER->getCenterY() + 32 >= 238 && PLAYER->getCenterY() <= 270)
	{
		IMAGEMANAGER->render("상점테이블", CAMERAMANAGER->getMemDC(), 230, 235);
	}

	CAMERAMANAGER->render(getMemDC());

	if (_isShopClicked)
	{
		_itemShop->render();
	}
	else
	{
		PLAYER->playerStatusRender(getMemDC());
	}
	if (_isTalk)
	{
		IMAGEMANAGER->render("대화창", getMemDC(), 80, 275);
		IMAGEMANAGER->render("상점기본", getMemDC(), 735, 310);
		textOut(getMemDC(), 120, 320, script[script_count], RGB(0, 0, 0));
	}
}

void shopScene::playerMove()
{
		if (INPUT->GetKey('W'))
		{
			if (GetPixel(IMAGEMANAGER->findImage("상점실내뒷배경")->getMemDC(), PLAYER->getCenterX(), PLAYER->getCenterY()) != RGB(255, 0, 0))
			{
				RECT temp;
				bool iscoli = false;
				for (int i = 0; i < 2; i++)
				{
					if (IntersectRect(&temp, &_npcPtr->getRC(), &RectMake(PLAYER->getCenterX()-8, PLAYER->getCenterY(), 16, 1)))
					{
						iscoli = true;
					}
				}
				if (!iscoli)
				{
					if (!SOUNDMANAGER->isPlaySound("movewood"))
					{
						SOUNDMANAGER->play("movewood", 0.2f);
					}
					PLAYER->setDirection(UP);
					PLAYER->setState(RUN);
					PLAYER->setCenterY(PLAYER->getCenterY() - PLAYER->getSpeed());
				}
			}
		}
		if (INPUT->GetKey('S'))
		{
			if (GetPixel(IMAGEMANAGER->findImage("상점실내뒷배경")->getMemDC(), PLAYER->getCenterX(), PLAYER->getCenterY() + 16) != RGB(255, 0, 0))
			{
				RECT temp;
				bool iscoli = false;
				for (int i = 0; i < 2; i++)
				{
					if (IntersectRect(&temp, &_npcPtr->getRC(), &RectMake(PLAYER->getCenterX() - 8, PLAYER->getCenterY() + 16, 16, 1)))
					{
						iscoli = true;
					}
				}
				if (!iscoli)
				{
					if (!SOUNDMANAGER->isPlaySound("movewood"))
					{
						SOUNDMANAGER->play("movewood", 0.2f);
					}
					PLAYER->setDirection(DOWN);
					PLAYER->setState(RUN);
					PLAYER->setCenterY(PLAYER->getCenterY() + PLAYER->getSpeed());
				}
			}
			
		}
		if (INPUT->GetKey('A'))
		{
			if (GetPixel(IMAGEMANAGER->findImage("상점실내뒷배경")->getMemDC(), PLAYER->getCenterX() - 8, PLAYER->getCenterY() + 8) != RGB(255, 0, 0))
			{
				RECT temp;
				bool iscoli = false;
				for (int i = 0; i < 2; i++)
				{
					if (IntersectRect(&temp, &_npcPtr->getRC(), &RectMake(PLAYER->getCenterX() - 8, PLAYER->getCenterY(), 1, 16)))
					{
						iscoli = true;
					}
				}
				if (!iscoli)
				{
					if (!SOUNDMANAGER->isPlaySound("movewood"))
					{
						SOUNDMANAGER->play("movewood", 0.2f);
					}
					PLAYER->setDirection(LEFT);
					PLAYER->setState(RUN);
					PLAYER->setCenterX(PLAYER->getCenterX() - PLAYER->getSpeed());
				}
			}
		}
		if (INPUT->GetKey('D'))
		{
			if (GetPixel(IMAGEMANAGER->findImage("상점실내뒷배경")->getMemDC(), PLAYER->getCenterX() + 8, PLAYER->getCenterY() + 8) != RGB(255, 0, 0))
			{
				RECT temp;
				bool iscoli = false;
				for (int i = 0; i < 2; i++)
				{
					if (IntersectRect(&temp, &_npcPtr->getRC(), &RectMake(PLAYER->getCenterX() + 8, PLAYER->getCenterY(), 1, 16)))
					{
						iscoli = true;
					}
				}
				if (!iscoli)
				{
					if (!SOUNDMANAGER->isPlaySound("movewood"))
					{
						SOUNDMANAGER->play("movewood", 0.2f);
					}
					PLAYER->setDirection(RIGHT);
					PLAYER->setState(RUN);
					PLAYER->setCenterX(PLAYER->getCenterX() + PLAYER->getSpeed());
				}
			}
		}
		if (!(INPUT->GetKey('W')) && !(INPUT->GetKey('S')) && !(INPUT->GetKey('A')) && !(INPUT->GetKey('D')))
		{
			if (SOUNDMANAGER->isPlaySound("movewood"))
			{
				SOUNDMANAGER->stop("movewood");
			}
			PLAYER->setState(STAND);
		}
}

void shopScene::setCurrentSlotNumber(int mouseWheel)
{
	if (mouseWheel > 0)
	{
		SOUNDMANAGER->play("toolSwap", 0.2f);
		PLAYER->setCurrentSlotNumber(PLAYER->getCurrentSlotNumber() - 1);
		_mouseWheel = 0;
	}
	else if (mouseWheel < 0)
	{
		SOUNDMANAGER->play("toolSwap", 0.2f);
		PLAYER->setCurrentSlotNumber(PLAYER->getCurrentSlotNumber() + 1);
		_mouseWheel = 0;
	}
}
