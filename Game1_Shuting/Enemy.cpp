#include <vector>
#include "dxlib.h"
#include "Enemy.h"
#include "Bullet.h"
#include "BulletMode.h"
#include "GameSystem.h"

//-----------------------------------------------------------------------------
//定数

//当たり判定の半径
#define W_HIT_RANGE 5 //武器
//敵の配列 defineで配列は使えないので、constにしている。
const int EHitRange[] = { 100 };

//-----------------------------------------------------------------------------


namespace {
	int image[1]; //0.ボス
}

void EnemyInitialize() {
	image[0] = LoadGraph("../material/picture/Enemy01.png");
}

Enemy::Enemy(float X, float Y, int ImageType, eBulletMode Mode,
	int Score, int Life, float Speed, float Speedrate, double Angle,
	double Carbdegree, double Anglerate, double BulletAngle, int BulletColor) :
	AutoMover(X, Y, ImageType, Speed, Speedrate,
		Angle, Carbdegree, Anglerate),
	m_score(Score), m_life(Life), m_mode(Mode), m_frameCount(0),
	m_bulletAngle(BulletAngle), m_bulletColor(BulletColor) {}

Enemy::Enemy(float X, float Y, float GoalX, float GoalY,
	int ImageType, eBulletMode Mode, int Score, int Life,
	float Speed, float Speedrate, double Carbdegree,
	double Anglerate, double BulletAngle, int BulletColor) :
	AutoMover(X, Y, GoalX, GoalY, ImageType,
		Speed, Speedrate, Carbdegree, Anglerate),
	m_score(Score), m_life(Life), m_mode(Mode), m_frameCount(0),
	m_bulletAngle(BulletAngle), m_bulletColor(BulletColor) {}

void Enemy::Draw() {
	DrawRotaGraphF(m_x, m_y, 1, 3.14, image[m_imageType], TRUE);
}

void Enemy::BulletPlus(std::vector<Bullet> &bullet, float cx, float cy) {
	if ((int)m_mode < 100) {
		BulletAdd(m_mode, bullet, m_frameCount, m_x, m_y,
			cx, cy, &m_bulletAngle, &m_bulletColor);
	}

	//ここから 特殊な個体
	else {
		eBulletMode NowMode;
		switch (m_mode) {
		case eBoss1:
			if (m_frameCount % 1200 < 600) NowMode = eBoss1_1;
			else NowMode = eBoss1_2;
			BulletAdd(NowMode, bullet, m_frameCount, m_x, m_y,
				cx, cy, &m_bulletAngle, &m_bulletColor);
			break;
		case eMulti1:
			BulletAdd(eSpiral8, bullet, m_frameCount, m_x, m_y,
				cx, cy, &m_bulletAngle, &m_bulletColor);
			break;
		}
	}
	m_frameCount++;
}

bool Enemy::IsHit(float wx, float wy, int wnum) {
	if ((wx - m_x)*(wx - m_x) + (wy - m_y)*(wy - m_y) <=
		(W_HIT_RANGE + EHitRange[m_imageType])*
		(W_HIT_RANGE + EHitRange[m_imageType])) {
		m_life--;
		if (m_life == 0) {
			m_alive = false;
			AddScore(wnum, m_score);
		}
		return true;
	}
	return false;
}
