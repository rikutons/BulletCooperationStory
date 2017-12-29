#include <cmath>
#include "Mover.h"
#include "Common.h"

//----------------------------------------------------------------------------------------------------------------------
//Mover
Mover::Mover(float X, float Y, float Speed, double Angle):x(X),y(Y),speed(Speed),angle(Angle/180*PI),alive(true)
{}

bool Mover::GetAlive() {
	return alive;
}

//----------------------------------------------------------------------------------------------------------------------
//AutoMover
AutoMover::AutoMover(float X, float Y, int _ImageType, float Speed, float Speedrate, double Angle, double Carbdegree, double Anglerate) :
	Mover(X, Y, Speed, Angle), ImageType(_ImageType) ,speedrate(Speedrate), carbdegree(Carbdegree), anglerate(Anglerate) {}

//goalx,goalyからangleを計算する。初期化時は仮に0を入れておく。
AutoMover::AutoMover(float X, float Y, float GoalX, float GoalY,int _ImageType, float Speed, float Speedrate, double Carbdegree, double Anglerate) :
	Mover(X, Y, Speed, 0), ImageType(_ImageType), speedrate(Speedrate), carbdegree(Carbdegree), anglerate(Anglerate) {
	
	float diffx, diffy;
	diffx = GoalX - X;
	diffy = GoalY - Y;

	angle = atan2(diffy, diffx);	//atan2...二点の座標から直角三角形を考え、その角の大きさを返してくれる関数。(ライブラリ:cmath)
}

void AutoMover::Update() {
	speed += speedrate;
	if (anglerate != 0)
		angle += carbdegree + (PI / anglerate)*speed;
	else
		angle += carbdegree;
	x += (float)cos(angle)*speed;
	y += (float)sin(angle)*speed;

	//画面外に行ったものを削除するため、もし画面外に出たならalive=falseにする。
	//尚、不自然にものが消えてしまうことを防ぐため、
	//ものが消える範囲を実際のウインドウサイズより多少大きくしてある。
	if (x > WindowWide  *1.2 || x < WindowWide  *-0.2||
		y > WindowHeight*1.2 || y < WindowHeight*-0.2) alive = false;
}