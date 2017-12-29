#include <vector>
#include "BulletMode.h"
#include "Bullet.h"
#include "Common.h"
#include "DxLib.h"
#include "GameTask.h"

#define BOSS1SPEED 2

using namespace std;

/*
Bullet(float X, float Y, int _ImageType, int Color, float Size, float Speed, float Speedrate, float Angle, float Carbdegree, float Anglerate);
Bullet(float X, float Y, float GoalX, float GoalY, int _ImageType, int Color, float Size, float Speed, float Speedrate, float Carbdegree, float Anglerate);
*/

void BulletAdd(eBulletMode mode, std::vector<Bullet*> &bullet, int time, float ex, float ey, float cx, float cy, double *angle) {
	switch (mode) {
	case eM1Spiral:
		if (time % 30 == 0) {
			for (int i = 0; i < 6; i++) {
				bullet.push_back(new Bullet(ex, ey, 0, 0, 0.2f, 2, 0, 0+i*60, 0.01, 1.001));
			}
		}
		break;
	case eBoss1_1:
		if (time % 40 == 0) {
			for (int i = 0; i < 6; i++) {
				bullet.push_back(new Bullet(ex, ey, 0, 0, 0.2f, BOSS1SPEED, 0, *angle+i*60, 0.001, 0.f));
			}
		}
		if (time % 10 == 0)
			bullet.push_back(new Bullet(ex, ey, cx, cy, 0 , 5, 0.1, 1, 0.1, 0, 0.f));
		*angle += 0.01;
		break;

	case eBoss1_2:
		if (time % 3 == 0)
			bullet.push_back(new Bullet(ex, ey, cx, cy, 0, 0, 0.3f, 1, 0, 1200.f, 0.f));
		break;


	}
};