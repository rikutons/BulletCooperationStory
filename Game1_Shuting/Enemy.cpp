#include <vector>
#include "dxlib.h"
#include "Enemy.h"
#include "Bullet.h"
#include "BulletMode.h"
#include "GameSystem.h"
#include "SoundMgr.h"
#include "SceneMgr.h"

//-----------------------------------------------------------------------------
//定数

//当たり判定の半径
#define W_HIT_RANGE 5 //武器
//敵の配列 defineで配列は使えないので、constにしている。
const int EHitRange[] = { 30,30,30,30,100 };
//ボス敵のID
#define BOSSID 1
//無限大
#define INF 100000000
//-----------------------------------------------------------------------------


namespace {
	int image[2];
}

void EnemyInitialize() {
	//UFO型 赤、青、黄、緑
	image[0] = LoadGraph("../material/picture/Enemy01.png");
	image[1] = LoadGraph("../material/picture/Enemy02.png");
	image[2] = LoadGraph("../material/picture/Enemy03.png");
	image[3] = LoadGraph("../material/picture/Enemy04.png");
	//ボス(三角形)
	image[4] = LoadGraph("../material/picture/Enemy05.png");
}

Enemy::Enemy(
	float X, float Y,
	int ImageType, eBulletMode Mode, int Score, int Life,
	float Speed, float Speedrate,
	double Angle, double Carbdegree, double Anglerate,
	int BulletColor, int ShotSpeed, int AimPlayerNum,
	//ここからデフォルト引数
	int StopFrame, int StartShotFrame, int EndShotFrame,
	double StopCarbAngle) :
	AutoMover(X, Y, ImageType, Speed, Speedrate,
		Angle, Carbdegree, Anglerate, StopFrame, StopCarbAngle),
	m_score(Score), m_life(Life), m_mode(Mode),
	m_frameCount(-StartShotFrame * ShotSpeed),
	m_bulletAngle(0), m_bulletColor(BulletColor),
	m_shotSpeed(ShotSpeed), m_aimPlayerNum(AimPlayerNum),
	m_endShotFrame(0) {
	m_endShotFrame = (EndShotFrame != INF ?
		((EndShotFrame - StartShotFrame)*ShotSpeed) : INF);
}

Enemy::Enemy(
	float X, float Y, float GoalX, float GoalY,
	int ImageType, eBulletMode Mode, int Score, int Life,
	float Speed, float Speedrate,
	double Angle, double Carbdegree, double Anglerate,
	int BulletColor, int ShotSpeed, int AimPlayerNum,
	//ここからデフォルト引数
	int StopFrame, int StartShotFrame, int EndShotFrame,
	double StopCarbAngle) :
	AutoMover(X, Y, GoalX, GoalY, ImageType,
		Speed, Speedrate, Angle, Carbdegree,
		Anglerate, StopFrame, StopCarbAngle),
	m_score(Score), m_life(Life), m_mode(Mode),
	m_frameCount(-StartShotFrame * ShotSpeed),
	m_bulletAngle(0), m_bulletColor(BulletColor),
	m_shotSpeed(ShotSpeed), m_aimPlayerNum(AimPlayerNum),
	m_endShotFrame(0) {
	m_endShotFrame = (EndShotFrame != INF ?
		((EndShotFrame - StartShotFrame)*ShotSpeed) : INF);
}

void Enemy::Draw() {
	DrawRotaGraphF(m_x, m_y, 1, 3.14, image[m_imageType], TRUE);
}

void Enemy::BulletPlus(std::vector<Bullet> &bullet, float cx, float cy) {
	m_frameCount += m_shotSpeed;
	if (m_frameCount % 300 != 0) return; //300カウントに一回発射
	if (m_frameCount >= 0 && m_frameCount <= m_endShotFrame) {
		float y = m_y;
		//UFO型の場合、発射口は少し下にあるので、y値を上げる。
		if (m_imageType >= 0 && m_imageType <= 3) {
			y += 40;
		}

		if ((int)m_mode < 100) {
			BulletAdd(m_mode, bullet, m_x, y,
				cx, cy, &m_bulletAngle, &m_bulletColor);
		}

		//ここから 特殊な個体
		else {
			eBulletMode NowMode;
			switch (m_mode) {
			case eBoss1:
				if (m_frameCount % 1200 < 600) NowMode = eBoss1_1;
				else NowMode = eBoss1_2;
				BulletAdd(NowMode, bullet, m_x, y,
					cx, cy, &m_bulletAngle, &m_bulletColor);
				break;
			case eMulti1:
				BulletAdd(eSpiral8, bullet, m_x, y,
					cx, cy, &m_bulletAngle, &m_bulletColor);
				break;
			}
		}
	}
}

bool Enemy::IsHit(float wx, float wy, int wnum) {
	if ((wx - m_x)*(wx - m_x) + (wy - m_y)*(wy - m_y) <=
		(W_HIT_RANGE + EHitRange[m_imageType])*
		(W_HIT_RANGE + EHitRange[m_imageType])) {
		m_life--;
		PlaySE(2);  //被弾ついでにHit音
		if (m_life == 0) {
			m_alive = false;
			AddScore(wnum, m_score);
			if (m_imageType == BOSSID) {
				SetScene(eGameClear);
			}
		}
		return true;
	}
	return false;
}
