#include "Bullet.h"
#include "Game.h"
#include "DxLib.h"
#include <math.h>
#include <cmath>
#include "Common.h"

static int BulletImage[16];

void BulletInitialize() {
	LoadDivGraph("../material/picture/複数円形弾01.png", 16, 4, 4, 200, 200, BulletImage);
}

//弾の基底クラス
BaseBullet::BaseBullet(float a, float b, int c, double d) :x(a), y(b), color(c), size(d) {};

float BaseBullet::GetBulletx() { return x; }

float BaseBullet::GetBullety() { return y; }

void BaseBullet::Draw() {
	DrawRotaGraphF(x, y, size, 0, BulletImage[color], TRUE);
}

//弾1
void B1rotation::Update() {
	speed += speedaccel;
	anglespeed += angleaccel;
	angle += (PI / anglespeed)*speed;
	x += (float)cos(angle)*speed;
	y += (float)sin(angle)*speed;
}

//弾2
B2straight::B2straight(float _x, float _y, int _c, double _s, float a, float b, float e,float f)
	:BaseBullet(_x, _y, _c, _s), speed(a), speedaccel(b), goalx(e), goaly(f) {

	float diffx, diffy;
	diffx = goalx - x;
	diffy = goaly - y;

	player_angle = atan2(diffy, diffx);	//atan2...二点の座標から直角三角形を考え、その角の大きさを返してくれる関数。(ライブラリ:cmath)
}

void B2straight::Update() {
	speed += speedaccel;
	x += (float)cos(player_angle)*speed;
	y += (float)sin(player_angle)*speed;
}