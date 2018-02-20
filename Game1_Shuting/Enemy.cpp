#include <vector>
#include "dxlib.h"
#include "Enemy.h"
#include "Bullet.h"
#include "BulletMode.h"

static int Image[1]; //0.É{ÉX

void EnemyInitialize() {
	Image[0] = LoadGraph("../material/picture/Enemy01.png");
}

Enemy::Enemy(float X, float Y, int _ImageType, eBulletMode Mode,
	int Score, float Speed, float Speedrate, double Angle,
	double Carbdegree, double Anglerate, double BRotation, int BColor) :
	AutoMover(X, Y, _ImageType, Speed, Speedrate,
		Angle, Carbdegree, Anglerate),
	score(Score), mode(Mode), time(0), Brotation(BRotation), Bcolor(BColor) {}

Enemy::Enemy(float X, float Y, float GoalX, float GoalY,
	int _ImageType, eBulletMode Mode, int Score, float Speed,
	float Speedrate, double Carbdegree, double Anglerate, double BRotation, int BColor) :
	AutoMover(X, Y, GoalX, GoalY, _ImageType,
		Speed, Speedrate, Carbdegree, Anglerate),
	score(Score), mode(Mode), time(0), Brotation(BRotation), Bcolor(BColor) {}

void Enemy::Draw() {
	DrawRotaGraphF(x, y, 0.8, 3.14, Image[ImageType], TRUE);

}

void Enemy::BulletPlus(std::vector<Bullet*> &bullet, float cx, float cy) {
	if ((int)mode < 100) {
		BulletAdd(mode, bullet, time, x, y, cx, cy, &Brotation,&Bcolor);
	}

	//Ç±Ç±Ç©ÇÁ ì¡éÍÇ»å¬ëÃ
	else {
		eBulletMode NowMode;
		switch (mode) {
		case eBoss1:
			if (time % 1200 < 600) NowMode = eBoss1_1;
			else NowMode = eBoss1_2;
			BulletAdd(NowMode, bullet, time, x, y, cx, cy, &Brotation, &Bcolor);
			break;
		case eMulti1:
			BulletAdd(eSpiral8, bullet, time, x, y, cx, cy, &Brotation, &Bcolor);
			break;
		}
	}
	time++;
}