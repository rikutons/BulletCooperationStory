#include "BulletMode.h"
#include "Bullet.h"
#include "BulletMgr.h"
#include "Constant.h"

using namespace std;
void ModeBoss1::newbullet(vector<BaseBullet*> *bullet) {
	BulletModeFlag++;
	if (BulletModeFlag%30==0) {
		m_angle ++;
		bullet->push_back(new B1rotation(BossX, BossY, 5, 0.2, 0+m_angle, 1400, -0.07, 3.f, 0));
		bullet->push_back(new B1rotation(BossX, BossY, 5, 0.2, 60 + m_angle, 1400, -0.07, 3.f, 0));
		bullet->push_back(new B1rotation(BossX, BossY, 5, 0.2, 120 + m_angle, 1400, -0.07, 3.f, 0));
		bullet->push_back(new B1rotation(BossX, BossY, 5, 0.2, 180 + m_angle, 1400, -0.07, 3.f, 0));
		bullet->push_back(new B1rotation(BossX, BossY, 5, 0.2, 240 + m_angle, 1400, -0.07, 3.f, 0));
		bullet->push_back(new B1rotation(BossX, BossY, 5, 0.2, 300 + m_angle, 1400, -0.07, 3.f, 0));
	}
	if (BulletModeFlag == 600) {
		SetBulletMode(eBoss2,true);
	}
};

void ModeBoss2::newbullet(vector<BaseBullet*> *bullet) {
	BulletModeFlag++;
	if (BulletModeFlag % 10 == 0)
		bullet->push_back(new B1rotation(BossX, BossY, GetRand(15), 0.05, 0, 1000, 0.005, 1.f, 0.01f));

	if (BulletModeFlag % 60 == 0)
		bullet->push_back(new B1rotation(BossX, BossY, GetRand(15), 0.3, 120, 120, 0, 1.f, 0.01f));


	if (BulletModeFlag == 600) {
		SetBulletMode(eBoss1,false);
	}
};