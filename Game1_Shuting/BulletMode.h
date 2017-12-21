#pragma once
#include <vector>
#include "Bullet.h"
using namespace std;

class BaseBulletMode {
protected:
	int BulletModeFlag;
public:
	BaseBulletMode() { BulletModeFlag = 0; };
	virtual void newbullet(vector<BaseBullet*> *bullet) = 0;
};

//この場合はボスの弾幕"モード1"であることを表す
class ModeBoss1:public BaseBulletMode {
	int m_angle;
public:
	void newbullet(vector<BaseBullet*> *bullet);
};

class ModeBoss2 :public BaseBulletMode {
public:
	void newbullet(vector<BaseBullet*> *bullet);
};