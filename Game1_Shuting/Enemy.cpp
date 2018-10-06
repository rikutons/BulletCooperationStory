#include <vector>
#include "dxlib.h"
#include "Enemy.h"
#include "Bullet.h"
#include "BulletMode.h"
#include "SoundMgr.h"
#include "SceneMgr.h"
#include "Common.h"
#include "EnemyAdd.h"
#include "Keybord.h"
#include "GameSystem.h"

//-----------------------------------------------------------------------------
//定数

//武器の当たり判定の半径
#define W_HIT_RANGE 5

//敵の配列 defineで配列は使えないので、constにしている。
//当たり判定の半径
const int EHitRange[] = { 30,30,30,30 };
const int ELife[] = { 3,5,7,9,160,200,200,550,INF };

#define ENEMY_SIZE 0.5f
//-----------------------------------------------------------------------------


namespace {
	int image[8];
}

void EnemyInitialize() {
	//UFO型 赤、青、黄、緑
	image[0] = LoadGraph("../material/picture/Enemy01.png");
	image[1] = LoadGraph("../material/picture/Enemy02.png");
	image[2] = LoadGraph("../material/picture/Enemy03.png");
	image[3] = LoadGraph("../material/picture/Enemy04.png");
	//中ボス格
	image[4] = LoadGraph("../material/picture/Enemy05.png");
	image[5] = LoadGraph("../material/picture/Enemy06.png");
	image[6] = LoadGraph("../material/picture/Enemy07.png");
	//ボス(三角形)
	image[7] = LoadGraph("../material/picture/Enemy08.png");
}

Enemy::Enemy(
	float X, float Y,
	int ImageType, eBulletMode Mode,
	float Speed, float Speedrate,
	double Angle, double Carbdegree, double Anglerate,
	int BulletColor, double BulletAngle, int ShotSpeed, int AimPlayerNum,
	//ここからデフォルト引数
	int StopFrame, int StartShotFrame, int EndShotFrame,
	double StopCarbAngle) :
	AutoMover(X, Y, ImageType, Speed, Speedrate,
		Angle, Carbdegree, Anglerate, StopFrame, StopCarbAngle, 0),
	m_life(ELife[ImageType]), m_mode(Mode),
	m_frameCount(-1),
	m_bulletAngle(BulletAngle), m_bulletColor(BulletColor),
	m_shotSpeed(ShotSpeed), m_aimPlayerNum(AimPlayerNum),
	m_startShotFrame(StartShotFrame), m_endShotFrame(EndShotFrame) {}

Enemy::Enemy(
	float X, float Y, float GoalX, float GoalY,
	int ImageType, eBulletMode Mode,
	float Speed, float Speedrate,
	double Angle, double Carbdegree, double Anglerate,
	int BulletColor, double BulletAngle, int ShotSpeed, int AimPlayerNum,
	//ここからデフォルト引数
	int StopFrame, int StartShotFrame, int EndShotFrame,
	double StopCarbAngle) :
	AutoMover(X, Y, GoalX, GoalY, ImageType,
		Speed, Speedrate, Angle, Carbdegree,
		Anglerate, StopFrame, StopCarbAngle, 0),
	m_life(ELife[ImageType]), m_mode(Mode),
	m_frameCount(-1),
	m_bulletAngle(BulletAngle), m_bulletColor(BulletColor),
	m_shotSpeed(ShotSpeed), m_aimPlayerNum(AimPlayerNum),
	m_startShotFrame(StartShotFrame), m_endShotFrame(EndShotFrame) {}

void Enemy::Draw() {
	if (m_imageType == 8) {
		DrawRotaGraphF(m_x, m_y, 0.1, PI, image[7], TRUE);
		return;
	}
	double size = 2;
	if (m_imageType >= 0 && m_imageType <= 3) {
		size = 1;
	}
	DrawRotaGraphF(m_x, m_y, ENEMY_SIZE*size, PI, image[m_imageType], TRUE);

	//DrawFormatString((int)m_x, (int)m_y, GetColor(255, 255, 255),
	//	"life:%d", m_life);
}

void Enemy::BulletPlus(std::vector<Bullet> &bullet, float cx, float cy) {
	m_frameCount++;
	//画面外にいる場合弾を打たない
	if (m_x<-WINDOW_WIDE*0.2 || m_x>WINDOW_WIDE*1.2 ||
		m_y<-WINDOW_HEIGHT*0.2 || m_y>WINDOW_HEIGHT*1.2) return;
	//ボスでなければ300カウントに一回発射
	else if ((m_frameCount - m_startShotFrame)*m_shotSpeed % 300 == 0 &&
		m_frameCount >= m_startShotFrame && m_frameCount <= m_endShotFrame) {
		float y = m_y;

		//UFO型の場合、発射口は少し下にあるので、y値を上げる。
		if (m_imageType >= 0 && m_imageType <= 3) {
			y += 40 * ENEMY_SIZE;
		}
		BulletAdd(m_mode, bullet, m_x, y,
			cx, cy, &m_bulletAngle, &m_bulletColor);
	}
}

bool Enemy::IsHit(float wx, float wy, int wnum) {
	if (m_imageType == 8) return false;
	if ((wx - m_x)*(wx - m_x) + (wy - m_y)*(wy - m_y) <=
		(W_HIT_RANGE + EHitRange[m_imageType])*
		(W_HIT_RANGE + EHitRange[m_imageType])) {
		m_life--;
		PlaySE(2);  //被弾ついでにHit音
		if (m_life == 0) {
			m_alive = false;
			AddScore(wnum, m_imageType);
		}
		return true;
	}
	return false;
}