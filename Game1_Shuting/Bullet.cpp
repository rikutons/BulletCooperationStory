#include <cmath>
#include "Bullet.h"
#include "DxLib.h"
#include "Bullet.h"
#include "Mover.h"
#include "Common.h"
#include "GameSystem.h"


//-------------------------------------------------------------------------------------------------
//定数

//当たり判定の半径
#define P_HIT_RANGE 11 //プレイヤー
const int BHitRange[] = { 30,50,50,10 }; //弾配列 defineで配列は使えないので、constにしている。

//-------------------------------------------------------------------------------------------------


static int BulletImage[4][16];

void BulletInitialize() {
	LoadDivGraph("../material/picture/Bullet01_sphere.png",
		16, 4, 4, 200, 200, BulletImage[0]);
	LoadDivGraph("../material/picture/Bullet02_laser_head.png",
		16, 4, 4, 200, 200, BulletImage[1]);
	LoadDivGraph("../material/picture/Bullet03_laser_body.png",
		16, 4, 4, 200, 200, BulletImage[2]);
	LoadDivGraph("../material/picture/Bullet04_star.png",
		16, 4, 4, 200, 200, BulletImage[3]);
}

Bullet::Bullet(float X, float Y, int _ImageType, int Color,
	float Size, float Speed, float Speedrate,
	double Angle, double Carbdegree, double Anglerate) :
	AutoMover(X, Y, _ImageType, Speed,
		Speedrate, Angle, Carbdegree, Anglerate),
	color(Color), size(Size) {}

Bullet::Bullet(float X, float Y, float GoalX, float GoalY,
	int _ImageType, int Color, float Size, float Speed,
	float Speedrate, double Carbdegree, double Anglerate) :
	AutoMover(X, Y, GoalX, GoalY, _ImageType,
		Speed, Speedrate, Carbdegree, Anglerate),
	color(Color), size(Size) {}

void Bullet::Draw() {
	DrawRotaGraphF(x, y, size, angle, BulletImage[ImageType][color], TRUE);
}

//プレイヤーとの当たり判定計算,種類、サイズに応じて判定を調節する。
void Bullet::IsHit(const float cx, const float cy, const int playerNum) {
	if ((cx - x)*(cx - x) + (cy - y)*(cy - y) <=
		(P_HIT_RANGE + BHitRange[ImageType])*
		(P_HIT_RANGE + BHitRange[ImageType])*size) {
		LifeDown(playerNum);
	}
}