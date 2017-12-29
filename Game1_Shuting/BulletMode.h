#pragma once
#include <vector>
#include "Bullet.h"

using namespace std;

enum eBulletMode {
	eM1Spiral = 1,
	eBoss1 = 100,
	eBoss1_1,
	eBoss1_2,
	eBoss1_3,
};

void BulletAdd(eBulletMode mode, vector<Bullet*> &bullet, int time, float ex, float ey, float cx, float cy, double *angle);
