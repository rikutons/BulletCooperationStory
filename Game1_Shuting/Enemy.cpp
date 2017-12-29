#include <vector>
#include "dxlib.h"
#include "Common.h"
#include "Enemy.h"
#include "Bullet.h"
#include "BulletMode.h"

static int Image[1]; //0 ボス

void EnemyInitialize() {
	Image[0] = LoadGraph("../material/picture/ボス01.png");
}

Enemy::Enemy(float X, float Y, int _ImageType, eBulletMode Mode, int Score, float Speed, float Speedrate, double Angle, double Carbdegree, double Anglerate) :
	AutoMover(X, Y, _ImageType, Speed, Speedrate, Angle, Carbdegree, Anglerate), score(Score), mode(Mode), time(0), rotation(0) {}

Enemy::Enemy(float X, float Y, float GoalX, float GoalY, int _ImageType, eBulletMode Mode, int Score, float Speed, float Speedrate, double Carbdegree, double Anglerate) :
	AutoMover(X, Y, GoalX, GoalY, _ImageType, Speed, Speedrate, Carbdegree, Anglerate), score(Score), mode(Mode), time(0), rotation(0) {}

void Enemy::Draw() {
	DrawRotaGraphF(x, y, 0.8, 3.14, Image[ImageType], TRUE);
	DrawFormatString(0, 0, GetColor(255, 255, 255), "x:%f,y:%f", x, y);

}

void Enemy::BulletPlus(std::vector<Bullet*> &bullet, float cx, float cy) {
	if ((int)mode < 100) {
		BulletAdd(mode, bullet, time, x, y, cx, cy, &rotation);
	}

	//ここから 特殊な個体
	else {
		eBulletMode NowMode;
		switch (mode) {
		case eBoss1:
			if (time % 1200 < 600) NowMode = eBoss1_1;
			else NowMode = eBoss1_2;
			BulletAdd(NowMode, bullet, time, x, y, cx, cy, &rotation);

		}
	}
	time++;
}