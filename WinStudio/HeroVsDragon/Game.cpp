#include "Game.h"
#include "TextureManager.h"
#include "Player.h"
#include "Monster.h"
#include "Button.h"
#include "Skill.h"

Game::Game()
	:m_pPlayer(nullptr),m_pBoss(nullptr)
{
}
Game::~Game()
{
	delete m_pPlayer;
	delete m_pBoss;
}
BOOL Game::gameInit(HWND hWnd)
{
	//��ʼ��
	TextureManager::getInstance()->init(hWnd);
	//������Դ
	TextureManager::getInstance()->load(L"bg.bmp",L"bg.bmp");
	TextureManager::getInstance()->setBkMode(TRANSPARENT);
	//TextureManager::getInstance()->load(L"hero.bmp",L"hero.bmp");
	//��ʼ������
	m_pPlayer = new Player();
	m_pPlayer->load(450,50,360,360,L"hero.bmp");
	//���ý�ɫ����
	m_pPlayer->setMaxHp(1000);
	m_pPlayer->setNowHp(1000);
	m_pPlayer->setLevel(6);
	m_pPlayer->setNowMp(60);
	m_pPlayer->setMaxMp(60);
	m_pPlayer->setStrength(10);
	m_pPlayer->setAgility(20);
	m_pPlayer->setIntelligence(10);

	m_pBoss = new Monster();
	m_pBoss->load(0,50,400,400,L"monster.bmp");
	//����boss����
	m_pBoss->setMaxHp(2000);
	m_pBoss->setNowHp(2000);
	m_pBoss->setLevel(10);
	m_pBoss->setNowMp(1000);
	m_pBoss->setMaxMp(1000);
	m_pBoss->setStrength(10);
	m_pBoss->setAgility(10);
	m_pBoss->setIntelligence(10);
	//���ü��ܰ���
	//�޵�ն
	m_pNormalSkill = new Skill();
	m_pNormalSkill->load(L"�޵�ն",L"ǿ������ͨ������ż������ֱ���");

	Button*btn1 = new Button();
	btn1->load(450,50 + 360,64,64,L"skillbutton1.bmp");
	btn1->bindSkill(m_pNormalSkill);
	m_skillBtns.push_back(btn1);
	return TRUE;
}
void Game::gamePaint(HWND hWnd)
{
	RECT r;
	GetClientRect(hWnd,&r);

	HDC hdc = GetDC(hWnd);

	int w = r.right - r.left;
	int h = r.bottom - r.top;
	//���뱳��
	TextureManager::getInstance()->bitBlt(L"bg.bmp",0,0,800,599,0,0,SRCCOPY);
	m_pPlayer->draw(hdc);
	m_pBoss->draw(hdc);
	//���ư�ť
	for(auto btn:m_skillBtns)
	{
		btn->draw(hdc);
	}
	TextureManager::getInstance()->draw(hdc);

	ReleaseDC(hWnd,hdc);
}
BOOL Game::gameCleanup(HWND hWnd)
{
	TextureManager::getInstance()->purge();
	m_pPlayer->clean();
	m_pBoss->clean();

	return TRUE;
}
void Game::gameMouseMotion(WORD x,WORD y)
{
	for(auto btn:m_skillBtns)
		btn->mouseMove(x,y);
}
void Game::gameMouseBtn(WORD x,WORD y)
{
}