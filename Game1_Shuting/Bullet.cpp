#include <cmath>
#include "Bullet.h"
#include "Game.h"
#include "DxLib.h"
#include "Bullet.h"
#include "Mover.h"
#include "Common.h"


//-------------------------------------------------------------------------------------------------
//定数

//当たり判定の半径
#define P_HIT_RANGE 11 //プレイヤー
const int BHitRange[] = { 60,50,50,10 }; //弾配列 defineで配列は使えないので、constにしている。

//-------------------------------------------------------------------------------------------------


static int BulletImage[4][16];

void BulletInitialize() {
	LoadDivGraph("../material/picture/弾01円.png",
					16, 4, 4, 200, 200, BulletImage[0]);
	LoadDivGraph("../material/picture/弾02レーザー頭.png",
					16, 4, 4, 200, 200, BulletImage[1]);
	LoadDivGraph("../material/picture/弾03レーザー尾.png",
					16, 4, 4, 200, 200, BulletImage[2]);
	LoadDivGraph("../material/picture/弾04星.png",
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
void Bullet::IsHit(const float cx,const float cy) {
	if ((cx - x)*(cx - x) + (cy - y)*(cy - y) <=
		(P_HIT_RANGE + BHitRange[ImageType])*
		(P_HIT_RANGE + BHitRange[ImageType])*size) {
		SetGameover();
	}
}