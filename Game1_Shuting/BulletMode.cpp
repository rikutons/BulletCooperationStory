#include <vector>
#include "BulletMode.h"
#include "Bullet.h"
#include "Common.h"
#include "DxLib.h"

#define BOSS1SPEED 2

using namespace std;

/*
Bullet::Bullet(float X, float Y, int _ImageType, int Color,
	float Size, float Speed, float Speedrate,
	double Angle, double Carbdegree, double Anglerate) :

Bullet::Bullet(float X, float Y, float GoalX, float GoalY,
	int _ImageType, int Color, float Size, float Speed,
	float Speedrate, double Carbdegree, double Anglerate) :
*/

/*
eSpiral 渦巻き型
eLaser レーザー
最後の数字は方向,Rの場合はランダム また、その前にPがついていたらプレイヤー座標準拠
*/

void BulletAdd(eBulletMode mode, std::vector<Bullet> &bullet, 
	int time, float ex, float ey, float cx, float cy, double *angle,int *color) {
	switch (mode) {
	case eSpiral8:
		if (time % 15 == 0) {
			for (int i = 0; i < 8; i++) {
				bullet.push_back(Bullet(ex, ey, 0, 0, 0.15f, BOSS1SPEED, 0, i * 45, 30/60.f, -0.035/60.f));
			}
		}
		break;

	case eLaserBigR:
		if (time % 25 == 0) {
			int type;
			if (time %(25*12)== 0) {
				*angle = GetRand(360);
				type = 1;
			}
			else type = 2;
			bullet.push_back(Bullet(ex, ey, type, *color, 1.f, 5.f, 0, *angle, 0, -0.00));
			if (*color != 11)++*color;
			else *color = 0;
		}
		break;

	//Boss1
	case eBoss1_1:
		if (time % 40 == 0) {
			for (int i = 0; i < 6; i++) {
				bullet.push_back(Bullet(ex, ey, 0, 0, 0.2f, BOSS1SPEED, 0, *angle+i*60, 0.001, 0.f));
			}
		}
		if (time % 10 == 0)
			bullet.push_back(Bullet(ex, ey, cx, cy, 0 , 5, 0.1f, 1, 0.1f, 0, 0.f));
		*angle +=0.3;
		break;

	case eBoss1_2:
		if (time % 3 == 0)
			bullet.push_back(Bullet(ex, ey, cx, cy, 0, 0, 0.3f, 1, 0, 1200.f, 0.f));
		break;


	}
};