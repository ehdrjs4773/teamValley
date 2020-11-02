#include "stdafx.h"
#include "towerScene.h"
#include "stdafx.h"
#include "shopScene.h"

HRESULT towerScene::init()
{
	CAMERAMANAGER->init(1600, 1600, 480, 240);
	CAMERAMANAGER->cameraMove(PLAYER->getCenterX(), PLAYER->getCenterY());

	_skillShop = new shop;
	_skillShop->init(SKILL_NPC);

	_isSkillClicked = false;

	_pos.x = 270;
	_pos.y = 310;

	_rc_player = RectMake(_pos.x, _pos.y, 16, 32);

	_skillNpc = new npc;
	_skillNpc->init(SKILL_NPC);
	_skillNpc->setPos(360, 143);

	//_itemNpc->setPos(310, 240);

	_npcPtr = _skillNpc;
	//_npcPtr[1] = _skillNpc;

	if (SOUNDMANAGER->isPlaySound("농장"))
	{
		SOUNDMANAGER->stop("농장");
	}
	_isTalk = false;
	tagScript temp[20];
	memset(&temp, 0, sizeof(temp));
	temp[0] = { IMAGEMANAGER->findImage("마법사기본"),"마법사","흠. 낯선이여. 내 연구실에는 무슨 용건으로\n 찾아온겐가."};
	temp[1] = { IMAGEMANAGER->findImage(""),"플레이어","특이해보이는 건물이 있길래 들어와봤는데 \n연구실이었군요."};
	temp[2] = { IMAGEMANAGER->findImage("마법사기본"),"마법사","그렇다네 이곳은 마법을 탐구하는 \n연구실이지." };
	temp[3] = { IMAGEMANAGER->findImage("마법사기본"),"마법사","이곳까지 찾아올 정도면 자네 많이 안 바쁜 \n모양이군." };
	temp[4] = { IMAGEMANAGER->findImage("마법사기본"),"마법사","먼 발걸음을 해줬으니 자네에게 특별히 \n선물을 주지." };
	temp[5] = { IMAGEMANAGER->findImage(""),"플레이어","마법사가 검을 줬다." };
	temp[6] = { IMAGEMANAGER->findImage("마법사기본"),"마법사","내 연구실을 빠져나와 이동하면 동굴이 \n하나 있을 걸세." };
	temp[7] = { IMAGEMANAGER->findImage("마법사기본"),"마법사","그 동굴 안에는 마법 생물체가 많아." };
	temp[8] = { IMAGEMANAGER->findImage("마법사웃음"),"마법사","생물체를 잡아 증거물을 가져오면 \n돈을 주겠네." };
	temp[9] = { IMAGEMANAGER->findImage("마법사웃음"),"마법사","자네가 잡기 쉽게 검에 마법도 걸어주지. \n어떤가?" };
	temp[10] = {  IMAGEMANAGER->findImage(""),"플레이어","이렇게까지 하시는 이유라도 있습니까? \n그 생물체는 혹시 마법 연구에 실패해서..." };
	temp[11] = {  IMAGEMANAGER->findImage(""),"플레이어","마법사가 갑자기 다급하게 곡괭이를 줬다." };
	temp[12] = { IMAGEMANAGER->findImage("마법사기본"),"마법사","...에헴. 동굴 안에 생물체만 있지 않을걸세.\n 돌도 있고 광석도 있지." };
	temp[13] = { IMAGEMANAGER->findImage("마법사기본"),"마법사","이 곡괭이를 사용하면 캘 수 있을걸세." };
	temp[14] = { IMAGEMANAGER->findImage("마법사기본"),"마법사","이야기는 끝. 나는 마저 연구를 해야하니\n 이만 나가주게." };
	temp[15] = { IMAGEMANAGER->findImage(""),"플레이어","결국 내가 궁금한건 해결이 안되었잖아?" };
	temp[16] = { IMAGEMANAGER->findImage("마법사기본"),"마법사","자네 무슨 볼 일로 왔는가?" };
	temp[17] = { IMAGEMANAGER->findImage("마법사기본"),"마법사","잘 가게나." };

	for (int i = 0; i < 18; i++)
	{
		script.push_back(temp[i]);
	}
	if (PLAYER->getIsMet())
	{
		script_count = 16;
	}
	this->update();
	return S_OK;
}

void towerScene::release()
{
	//_shop->release();
}

void towerScene::update()
{
	//if (!SOUNDMANAGER->isPlaySound("town"))
	//{
	//	SOUNDMANAGER->play("town", 0.05f);
	//}
	
	cout << PLAYER->getIsMet();
	_skillNpc->update();
	//cout << "x : " << PLAYER->getCenterX() << "\t" << "y : " << PLAYER->getCenterY() << endl;
	if (!PLAYER->getIsMet())
	{
		if (_isTalk)
		{
			if (INPUT->GetKeyDown(VK_LBUTTON))
			{
				script_count++;
				//if (script_count <= 15)
				//{
				//	_isTalk = false;
				//	_isSkillClicked = true;
				//}
				if (script_count == 5)
				{
					for (int i = 0; i < INVENMAX; i++)
					{
						if ((*PLAYER->getInven())[i].item_image == NULL)
						{
							PLAYER->setInvenItem(i, ITEMMANAGER->findItem("폭발_검"));
							break;
						}
					}
				}
				else if (script_count == 11)
				{
					for (int i = 0; i < INVENMAX; i++)
					{
						if ((*PLAYER->getInven())[i].item_image == NULL)
						{
							//PLAYER->setInvenItem(i, ITEMMANAGER->findItem("곡괭이"));
							break;
						}
					}
				}
				else if (script_count > 15)
				{
					_isTalk = false;
					//_isSkillClicked = true;
					//PLAYER->getInventory()->getvInven().push_back(ITEMMANAGER->findItem("폭발_검"));
					//PLAYER->getInventory()->getvInven().push_back(ITEMMANAGER->findItem("곡괭이"));
					PLAYER->setIsMet(true);
				}
			}
		}
	}
	else if(_isTalk)
	{
		if (INPUT->GetKeyDown(VK_LBUTTON))
		{
			cout << script_count << endl;
			script_count++;
			if (script_count == 17)
			{
				_isTalk = false;
				_isSkillClicked = true;	
			}
			else if(script_count > 17)
			{
				_isTalk = false;
				script_count = 16;
			}
		}
	}

	//상점 나가기 포탈
	if (PLAYER->getCenterY() >= 270)
	{
		if (!SWITCHMANAGER->getFade())
		{
			SOUNDMANAGER->play("doorOpen", 0.2f);
			SWITCHMANAGER->changeScene("인게임화면");
			SWITCHMANAGER->startFade(176.0f, 224.0f);
		}
	}

	if (_isSkillClicked)
	{
		_skillShop->update();
		_isSkillClicked = !_skillShop->shopClose();
		PLAYER->getInventory()->isShopOpen(_isSkillClicked);
		if (_skillShop->shopClose())
		{
			_isTalk = true;
		}
	}
	else
	{
		setCurrentSlotNumber(_mouseWheel);

		PLAYER->update();

		if (!PLAYER->getIsShowInventory())
		{
			playerMove();
		}

		_skillNpc->update();

		_rc_player = RectMake(_pos.x, _pos.y, 16, 32);

		temp.x = CAMERAMANAGER->getX() + (float)_ptMouse.x / (float)WINSIZEX * 480;
		temp.y = CAMERAMANAGER->getY() + (float)_ptMouse.y / (float)WINSIZEY * (float)230;

		if (PtInRect(&_skillNpc->getRC(), temp))
		{
			if (INPUT->GetKeyDown(VK_LBUTTON))
			{
				//_isSkillClicked = true;
				_isTalk = true;
			}
		}
		CAMERAMANAGER->cameraMove(PLAYER->getCenterX(), PLAYER->getCenterY());
	}
}

void towerScene::render()
{
	IMAGEMANAGER->render("마법사성내부", CAMERAMANAGER->getMemDC());

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

	CAMERAMANAGER->render(getMemDC());

	 if (_isSkillClicked)
	{
		_skillShop->render();
	}
	else
	{
		PLAYER->playerStatusRender(getMemDC());
	}
	 if (_isTalk)
	 {
		 IMAGEMANAGER->render("대화창", getMemDC(), 80, 275);
		 RECT tempRC = RectMake(120,320,800,300);
		 if(script[script_count].name == "마법사") script[script_count].image->render(getMemDC(), 735, 310);
		 DrawText(getMemDC(), script[script_count].script, strlen(script[script_count].script), &tempRC, NULL);
		 //textOut(getMemDC(), 120, 320, script[script_count].script, RGB(0, 0, 0));
	 }
}

void towerScene::playerMove()
{
	if (INPUT->GetKey('W'))
	{
		if (GetPixel(IMAGEMANAGER->findImage("마법사성내부충돌")->getMemDC(), PLAYER->getCenterX(), PLAYER->getCenterY()) != RGB(255, 0, 0))
		{
			RECT temp;
			bool iscoli = false;
			for (int i = 0; i < 2; i++)
			{
				if (IntersectRect(&temp, &_npcPtr->getRC(), &RectMake(PLAYER->getCenterX() - 8, PLAYER->getCenterY(), 16, 1)))
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
		if (GetPixel(IMAGEMANAGER->findImage("마법사성내부충돌")->getMemDC(), PLAYER->getCenterX(), PLAYER->getCenterY() + 16) != RGB(255, 0, 0))
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
		if (GetPixel(IMAGEMANAGER->findImage("마법사성내부충돌")->getMemDC(), PLAYER->getCenterX() - 8, PLAYER->getCenterY() + 8) != RGB(255, 0, 0))
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
		if (GetPixel(IMAGEMANAGER->findImage("마법사성내부충돌")->getMemDC(), PLAYER->getCenterX() + 8, PLAYER->getCenterY() + 8) != RGB(255, 0, 0))
		{
			RECT temp;
			bool iscoli = false;

			if (IntersectRect(&temp, &_npcPtr->getRC(), &RectMake(PLAYER->getCenterX() + 8, PLAYER->getCenterY(), 1, 16)))	iscoli = true;
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

void towerScene::setCurrentSlotNumber(int mouseWheel)
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