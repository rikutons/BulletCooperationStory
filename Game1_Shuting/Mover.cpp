#include <cmath>
#include "Mover.h"
#include "Common.h"

//-------------------------------------------------------------------------------------------------
//Mover

//60分法で得た角度をラジアンに変換
Mover::Mover(float X, float Y, float Speed, double Angle)
	:m_x(X), m_y(Y), m_speed(Speed), m_angle(Angle / 180 * PI), m_alive(true) {}

//-------------------------------------------------------------------------------------------------Z
//AutoMover

//60分法で得た曲がり具合、角度加速度をラジアンに変換
AutoMover::AutoMover(float X, float Y, int ImageType, float Speed,
	float Speedrate, double Angle, double Carbdegree, double Anglerate) :
	Mover(X, Y, Speed, Angle), m_imageType(ImageType), m_speedRate(Speedrate),
	m_carbDegree(Carbdegree / 180 * PI), m_angleRate(Anglerate / 180 * PI), m_anglePlus(0) {}

//goalx,goalyからangleを計算する。初期化時は仮に0を入れておく。
AutoMover::AutoMover(float X, float Y, float GoalX, float GoalY, int ImageType,
	float Speed, float Speedrate, double Carbdegree, double Anglerate) :
	Mover(X, Y, Speed, 0), m_imageType(ImageType), m_speedRate(Speedrate),
	m_carbDegree(Carbdegree / 180 * PI), m_angleRate(Anglerate / 180 * PI), m_anglePlus(0) {

	float diffx, diffy;
	diffx = GoalX - X;
	diffy = GoalY - Y;

	/*
	atan2...二点の座標から直角三角形を考え、
	その角の大きさを返してくれる関数。(ライブラリ:cmath)
	*/
	m_angle = atan2(diffy, diffx);
}

void AutoMover::Update() {
	m_speed += m_speedRate;
	m_anglePlus += m_angleRate*m_speed;
	m_angle += (m_carbDegree + m_anglePlus)*m_speed;
	//angle += carbdegree+angleplus;
	//北方向を0度として計算したいので、yは-cos,xはsin,と入れ替えて使用する。
	m_x += (float)sin(m_angle)*m_speed;
	m_y += -(float)cos(m_angle)*m_speed;

	/*
	画面外に行ったものを削除するため、もし画面外に出たならalive=falseにする。
	尚、不自然にものが消えてしまうことを防ぐため、
	ものが消える範囲を実際のウインドウサイズより多少大きくしてある。
	*/
	if (m_x > WINDOW_WIDE  *1.2 || m_x < WINDOW_WIDE  *-0.2 ||
		m_y > WINDOW_HEIGHT*1.2 || m_y < WINDOW_HEIGHT*-0.2) m_alive = false;
}