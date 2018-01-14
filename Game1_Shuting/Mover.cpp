#include <cmath>
#include "Mover.h"
#include "Common.h"

//-------------------------------------------------------------------------------------------------
//Mover

//60分法で得た角度をラジアンに変換
Mover::Mover(float X, float Y, float Speed, double Angle)
	:x(X), y(Y), speed(Speed), angle(Angle / 180 * PI), alive(true) {}

//-------------------------------------------------------------------------------------------------Z
//AutoMover

//60分法で得た曲がり具合、角度加速度をラジアンに変換
AutoMover::AutoMover(float X, float Y, int _ImageType, float Speed,
	float Speedrate, double Angle, double Carbdegree, double Anglerate) :
	Mover(X, Y, Speed, Angle), ImageType(_ImageType), speedrate(Speedrate),
	carbdegree(Carbdegree / 180 * PI), anglerate(Anglerate / 180 * PI), angleplus(0) {}

//goalx,goalyからangleを計算する。初期化時は仮に0を入れておく。
AutoMover::AutoMover(float X, float Y, float GoalX, float GoalY, int _ImageType,
	float Speed, float Speedrate, double Carbdegree, double Anglerate) :
	Mover(X, Y, Speed, 0), ImageType(_ImageType), speedrate(Speedrate),
	carbdegree(Carbdegree / 180 * PI), anglerate(Anglerate / 180 * PI), angleplus(0) {

	float diffx, diffy;
	diffx = GoalX - X;
	diffy = GoalY - Y;

	/*
	atan2...二点の座標から直角三角形を考え、
	その角の大きさを返してくれる関数。(ライブラリ:cmath)
	*/
	angle = atan2(diffy, diffx);
}

void AutoMover::Update() {
	speed += speedrate;
	angleplus += anglerate*speed;
	angle += (carbdegree + angleplus)*speed;
	//angle += carbdegree+angleplus;
	//北方向を0度として計算したいので、yは-cos,xはsin,と入れ替えて使用する。
	x += (float)sin(angle)*speed;
	y += -(float)cos(angle)*speed;

	/*
	画面外に行ったものを削除するため、もし画面外に出たならalive=falseにする。
	尚、不自然にものが消えてしまうことを防ぐため、
	ものが消える範囲を実際のウインドウサイズより多少大きくしてある。
	*/
	if (x > WINDOW_WIDE  *1.2 || x < WINDOW_WIDE  *-0.2 ||
		y > WINDOW_HEIGHT*1.2 || y < WINDOW_HEIGHT*-0.2) alive = false;
}