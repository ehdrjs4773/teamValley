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

	if (SOUNDMANAGER->isPlaySound("����"))
	{
		SOUNDMANAGER->stop("����");
	}
	_isTalk = false;
	tagScript temp[20];
	memset(&temp, 0, sizeof(temp));
	temp[0] = { IMAGEMANAGER->findImage("������⺻"),"������","��. �����̿�. �� �����ǿ��� ���� �������\n ã�ƿ°հ�."};
	temp[1] = { IMAGEMANAGER->findImage(""),"�÷��̾�","Ư���غ��̴� �ǹ��� �ֱ淡 ���ͺôµ� \n�������̾�����."};
	temp[2] = { IMAGEMANAGER->findImage("������⺻"),"������","�׷��ٳ� �̰��� ������ Ž���ϴ� \n����������." };
	temp[3] = { IMAGEMANAGER->findImage("������⺻"),"������","�̰����� ã�ƿ� ������ �ڳ� ���� �� �ٻ� \n����̱�." };
	temp[4] = { IMAGEMANAGER->findImage("������⺻"),"������","�� �߰����� �������� �ڳ׿��� Ư���� \n������ ����." };
	temp[5] = { IMAGEMANAGER->findImage(""),"�÷��̾�","�����簡 ���� ���." };
	temp[6] = { IMAGEMANAGER->findImage("������⺻"),"������","�� �������� �������� �̵��ϸ� ������ \n�ϳ� ���� �ɼ�." };
	temp[7] = { IMAGEMANAGER->findImage("������⺻"),"������","�� ���� �ȿ��� ���� ����ü�� ����." };
	temp[8] = { IMAGEMANAGER->findImage("���������"),"������","����ü�� ��� ���Ź��� �������� \n���� �ְڳ�." };
	temp[9] = { IMAGEMANAGER->findImage("���������"),"������","�ڳװ� ��� ���� �˿� ������ �ɾ�����. \n���?" };
	temp[10] = {  IMAGEMANAGER->findImage(""),"�÷��̾�","�̷��Ա��� �Ͻô� ������ �ֽ��ϱ�? \n�� ����ü�� Ȥ�� ���� ������ �����ؼ�..." };
	temp[11] = {  IMAGEMANAGER->findImage(""),"�÷��̾�","�����簡 ���ڱ� �ٱ��ϰ� ��̸� ���." };
	temp[12] = { IMAGEMANAGER->findImage("������⺻"),"������","...����. ���� �ȿ� ����ü�� ���� �����ɼ�.\n ���� �ְ� ������ ����." };
	temp[13] = { IMAGEMANAGER->findImage("������⺻"),"������","�� ��̸� ����ϸ� Ķ �� �����ɼ�." };
	temp[14] = { IMAGEMANAGER->findImage("������⺻"),"������","�̾߱�� ��. ���� ���� ������ �ؾ��ϴ�\n �̸� �����ְ�." };
	temp[15] = { IMAGEMANAGER->findImage(""),"�÷��̾�","�ᱹ ���� �ñ��Ѱ� �ذ��� �ȵǾ��ݾ�?" };
	temp[16] = { IMAGEMANAGER->findImage("������⺻"),"������","�ڳ� ���� �� �Ϸ� �Դ°�?" };
	temp[17] = { IMAGEMANAGER->findImage("������⺻"),"������","�� ���Գ�." };

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
							PLAYER->setInvenItem(i, ITEMMANAGER->findItem("����_��"));
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
							//PLAYER->setInvenItem(i, ITEMMANAGER->findItem("���"));
							break;
						}
					}
				}
				else if (script_count > 15)
				{
					_isTalk = false;
					//_isSkillClicked = true;
					//PLAYER->getInventory()->getvInven().push_back(ITEMMANAGER->findItem("����_��"));
					//PLAYER->getInventory()->getvInven().push_back(ITEMMANAGER->findItem("���"));
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

	//���� ������ ��Ż
	if (PLAYER->getCenterY() >= 270)
	{
		if (!SWITCHMANAGER->getFade())
		{
			SOUNDMANAGER->play("doorOpen", 0.2f);
			SWITCHMANAGER->changeScene("�ΰ���ȭ��");
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
	IMAGEMANAGER->render("�����缺����", CAMERAMANAGER->getMemDC());

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
		 IMAGEMANAGER->render("��ȭâ", getMemDC(), 80, 275);
		 RECT tempRC = RectMake(120,320,800,300);
		 if(script[script_count].name == "������") script[script_count].image->render(getMemDC(), 735, 310);
		 DrawText(getMemDC(), script[script_count].script, strlen(script[script_count].script), &tempRC, NULL);
		 //textOut(getMemDC(), 120, 320, script[script_count].script, RGB(0, 0, 0));
	 }
}

void towerScene::playerMove()
{
	if (INPUT->GetKey('W'))
	{
		if (GetPixel(IMAGEMANAGER->findImage("�����缺�����浹")->getMemDC(), PLAYER->getCenterX(), PLAYER->getCenterY()) != RGB(255, 0, 0))
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
		if (GetPixel(IMAGEMANAGER->findImage("�����缺�����浹")->getMemDC(), PLAYER->getCenterX(), PLAYER->getCenterY() + 16) != RGB(255, 0, 0))
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
		if (GetPixel(IMAGEMANAGER->findImage("�����缺�����浹")->getMemDC(), PLAYER->getCenterX() - 8, PLAYER->getCenterY() + 8) != RGB(255, 0, 0))
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
		if (GetPixel(IMAGEMANAGER->findImage("�����缺�����浹")->getMemDC(), PLAYER->getCenterX() + 8, PLAYER->getCenterY() + 8) != RGB(255, 0, 0))
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