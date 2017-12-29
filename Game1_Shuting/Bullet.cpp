#include <cmath>
#include "Bullet.h"
#include "Game.h"
#include "DxLib.h"
#include "Common.h"
#include "Bullet.h"
#include "Mover.h"

static int BulletImage[1][16];

void BulletInitialize() {
	LoadDivGraph("../material/picture/複数円形弾01.png", 16, 4, 4, 200, 200, BulletImage[0]);
}

Bullet::Bullet(float X, float Y, int _ImageType, int Color, float Size, float Speed, float Speedrate, double Angle, double Carbdegree, double Anglerate) :
	AutoMover(X, Y, _ImageType, Speed, Speedrate, Angle, Carbdegree, Anglerate), color(Color), size(Size) {}

Bullet::Bullet(float X, float Y, float GoalX, float GoalY, int _ImageType, int Color, float Size, float Speed, float Speedrate, double Carbdegree, double Anglerate) :
	AutoMover(X, Y, GoalX, GoalY, _ImageType, Speed, Speedrate, Carbdegree, Anglerate), color(Color), size(Size) {}

void Bullet::Draw() {
	DrawRotaGraphF(x, y, size, 0, BulletImage[ImageType][color], TRUE);
}

//プレイヤーとの当たり判定計算,種類、サイズに応じて判定を調節する。
void Bullet::IsHit(const float cx,const float cy) {
	if ((cx - x)*(cx - x) + (cy - y)*(cy - y) <=
		(PHitRange - BHitRange[ImageType])*(PHitRange - BHitRange[ImageType])*size) {
		SetGameover();
	}
}