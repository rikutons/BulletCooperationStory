#pragma once
#include <vector>
#include "Bullet.h"

enum eBulletMode {
	eSpiral8 = 1,
	eLaserBigR = 11,
	eBoss1 = 100,
	eBoss1_1,
	eBoss1_2,
	eBoss1_3,
	eMulti1
};

void BulletAdd(eBulletMode, std::vector<Bullet>&,
	int, float, float,
	float, float, double*, int*);
