#include "BulletMode.h"
#include "Bullet.h"
#include "BulletMgr.h"
#include "Common.h"

#define CARB 500
#define ACCSEL1 1
#define ACCSEL2 0

extern float cx, cy;

using namespace std;
void ModeBoss1::newbullet(vector<BaseBullet*> *bullet) {
	BulletModeFlag++;
	/*if (BulletModeFlag%30==0) {
		m_angle ++;
		bullet->push_back(new B1rotation(BossX, BossY, 5, 0.2, 0+m_angle, 1400, -0.07, 3.f, 0));
		bullet->push_back(new B1rotation(BossX, BossY, 5, 0.2, 60 + m_angle, 1400, -0.07, 3.f, 0));
		bullet->push_back(new B1rotation(BossX, BossY, 5, 0.2, 120 + m_angle, 1400, -0.07, 3.f, 0));
		bullet->push_back(new B1rotation(BossX, BossY, 5, 0.2, 180 + m_angle, 1400, -0.07, 3.f, 0));
		bullet->push_back(new B1rotation(BossX, BossY, 5, 0.2, 240 + m_angle, 1400, -0.07, 3.f, 0));
		bullet->push_back(new B1rotation(BossX, BossY, 5, 0.2, 300 + m_angle, 1400, -0.07, 3.f, 0));
	}*/
	if (BulletModeFlag % 20 == 0) {
		bullet->push_back(new B1rotation(BossX, BossY, 7, 0.1, 0 + m_angle, CARB, ACCSEL1, 3.f, 0)); //double 5.00 float 5.00f
		bullet->push_back(new B1rotation(BossX, BossY, 7, 0.1, 60 + m_angle, CARB, ACCSEL1, 3.f, 0));
		bullet->push_back(new B1rotation(BossX, BossY, 7, 0.1, 120 + m_angle, CARB, ACCSEL1, 3.f, 0));
		bullet->push_back(new B1rotation(BossX, BossY, 7, 0.1, 180 + m_angle, CARB, ACCSEL1, 3.f, 0));
		bullet->push_back(new B1rotation(BossX, BossY, 7, 0.1, 240 + m_angle, CARB, ACCSEL1, 3.f, 0));
		bullet->push_back(new B1rotation(BossX, BossY, 7, 0.1, 300 + m_angle, CARB, ACCSEL1, 3.f, 0));

	}
	if (BulletModeFlag % 20 == 0) {
		bullet->push_back(new B1rotation(BossX, BossY, 7, 0.2, 0 + m_angle, CARB, ACCSEL2, 5.f, 0));
		bullet->push_back(new B1rotation(BossX, BossY, 7, 0.2, 60 + m_angle, CARB, ACCSEL2, 5.f, 0));
		bullet->push_back(new B1rotation(BossX, BossY, 7, 0.2, 120 + m_angle, CARB, ACCSEL2, 5.f, 0));
		bullet->push_back(new B1rotation(BossX, BossY, 7, 0.2, 180 + m_angle, CARB, ACCSEL2, 5.f, 0));
		bullet->push_back(new B1rotation(BossX, BossY, 7, 0.2, 240 + m_angle, CARB, ACCSEL2, 5.f, 0));
		bullet->push_back(new B1rotation(BossX, BossY, 7, 0.2, 300 + m_angle, CARB, ACCSEL2, 5.f, 0));

	}

	if (BulletModeFlag == 10) {
		SetBulletMode(eBoss2,true);
	}
};

void ModeBoss2::newbullet(vector<BaseBullet*> *bullet) {
	BulletModeFlag++;
	if (BulletModeFlag % 3 == 0)
		bullet->push_back(new B2straight(GetRand(WindowWide), BossY, GetRand(15), GetRand(100)/500.0 , 1 ,0.1 , cx , cy));



	if (BulletModeFlag == 600) {
		SetBulletMode(eBoss1,false);
	}
};