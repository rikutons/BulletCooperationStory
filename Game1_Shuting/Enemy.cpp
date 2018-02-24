#include <vector>
#include "dxlib.h"
#include "Enemy.h"
#include "Bullet.h"
#include "BulletMode.h"

namespace {
	int image[1]; //0.É{ÉX
}

void EnemyInitialize() {
	image[0] = LoadGraph("../material/picture/Enemy01.png");
}

Enemy::Enemy(float X, float Y, int ImageType, eBulletMode Mode,
	int Score, float Speed, float Speedrate, double Angle,
	double Carbdegree, double Anglerate, double BulletAngle, int BulletColor) :
	AutoMover(X, Y, ImageType, Speed, Speedrate,
		Angle, Carbdegree, Anglerate),
	m_score(Score), mode(Mode), m_time(0), m_bulletAngle(BulletAngle), m_bulletColor(BulletColor) {}

Enemy::Enemy(float X, float Y, float GoalX, float GoalY,
	int ImageType, eBulletMode Mode, int Score, float Speed,
	float Speedrate, double Carbdegree, double Anglerate, double BulletAngle, int BulletColor) :
	AutoMover(X, Y, GoalX, GoalY, ImageType,
		Speed, Speedrate, Carbdegree, Anglerate),
	m_score(Score), mode(Mode), m_time(0), m_bulletAngle(BulletAngle), m_bulletColor(BulletColor) {}

void Enemy::Draw() {
	DrawRotaGraphF(m_x, m_y, 0.8, 3.14, image[m_imageType], TRUE);

}

void Enemy::BulletPlus(std::vector<Bullet> &bullet, float cx, float cy) {
	if ((int)mode < 100) {
		BulletAdd(mode, bullet, m_time, m_x, m_y, cx, cy, &m_bulletAngle,&m_bulletColor);
	}

	//Ç±Ç±Ç©ÇÁ ì¡éÍÇ»å¬ëÃ
	else {
		eBulletMode NowMode;
		switch (mode) {
		case eBoss1:
			if (m_time % 1200 < 600) NowMode = eBoss1_1;
			else NowMode = eBoss1_2;
			BulletAdd(NowMode, bullet, m_time, m_x, m_y, cx, cy, &m_bulletAngle, &m_bulletColor);
			break;
		case eMulti1:
			BulletAdd(eSpiral8, bullet, m_time, m_x, m_y, cx, cy, &m_bulletAngle, &m_bulletColor);
			break;
		}
	}
	m_time++;
}