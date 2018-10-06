#include <cmath>
#include "Bullet.h"
#include "DxLib.h"
#include "Bullet.h"
#include "Mover.h"
#include "GameSystem.h"


//-----------------------------------------------------------------------------
//定数

//当たり判定の半径
#define P_HIT_RANGE 5 //プレイヤー
//弾の配列 defineで配列は使えないので、constにしている。
const int BHitRange[] = { 74,36,20,50,50 };

//-----------------------------------------------------------------------------

namespace {
	int image[5][16];
}

//分割して読み込む
void BulletInitialize() {
	LoadDivGraph("../material/picture/Bullet01_sphere.png",
		16, 4, 4, 200, 200, image[0]);
	LoadDivGraph("../material/picture/Bullet02_star.png",
		16, 4, 4, 200, 200, image[1]);
	LoadDivGraph("../material/picture/Bullet03_shell.png",
		16, 4, 4, 200, 200, image[2]);
	LoadDivGraph("../material/picture/Bullet04_laser_head.png",
		16, 4, 4, 200, 200, image[3]);
	LoadDivGraph("../material/picture/Bullet05_laser_body.png",
		16, 4, 4, 200, 200, image[4]);
}

Bullet::Bullet(
	float X, float Y,
	int ImageType, int Color, float Size,
	float Speed, float Speedrate,
	double Angle, double Carbdegree, double Anglerate,
	//ここからデフォルト引数
	int StopFrame, double StopCarbAngle, int ReflectCount) :
	AutoMover(X, Y, ImageType, Speed,
		Speedrate, Angle, Carbdegree,
		Anglerate, StopFrame, StopCarbAngle, ReflectCount),
	m_color(Color), m_size(Size) {}

Bullet::Bullet(
	float X, float Y, float GoalX, float GoalY,
	int ImageType, int Color, float Size,
	float Speed, float Speedrate,
	double Angle, double Carbdegree, double Anglerate,
	//ここからデフォルト引数
	int StopFrame, double StopCarbAngle, int ReflectCount) :
	AutoMover(X, Y, GoalX, GoalY, ImageType,
		Speed, Speedrate, Angle, Carbdegree,
		Anglerate, StopFrame, StopCarbAngle, ReflectCount),
	m_color(Color), m_size(Size) {}

void Bullet::Draw() {
	DrawRotaGraphF(m_x, m_y, m_size, m_angle, image[m_imageType][m_color], TRUE);
	//DrawFormatString(0, 30, GetColor(255, 255, 255),
	//	"angle:%f,refcnt:%d,int: %d ", m_angle, m_reflectCount, m_beforeReflectDir);
}

//プレイヤーとの当たり判定計算,種類、サイズに応じて判定を調節する。
bool Bullet::IsHit(const float cx, const float cy) {
	if ((cx - m_x)*(cx - m_x) + (cy - m_y)*(cy - m_y) <=
		(P_HIT_RANGE + BHitRange[m_imageType] * m_size)*
		(P_HIT_RANGE + BHitRange[m_imageType] * m_size)) {
		return true;
	}
	return false;
}