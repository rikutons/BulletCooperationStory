#include <cmath>
#include "Mover.h"
#include "Common.h"
#include "dxlib.h"

//-----------------------------------------------------------------------------
//定数
#define PI 3.141592653589793238462643383279
//無限大
#define INF 100000000
//-----------------------------------------------------------------------------

//Mover

//60分法で得た角度をラジアンに変換
Mover::Mover(float X, float Y, float Speed, double Angle)
	:m_x(X), m_y(Y), m_speed(Speed),
	m_angle(Angle / 180 * PI), m_alive(true) {}

//-----------------------------------------------------------------------------
//AutoMover

//60分法で得た曲がり具合、角度加速度をラジアンに変換
AutoMover::AutoMover(float X, float Y, int ImageType, float Speed,
	float Speedrate, double Angle, double Carbdegree,
	double Anglerate, int StopFrame, double StopCarbAngle) :
	Mover(X, Y, Speed, Angle), m_imageType(ImageType), m_speedRate(Speedrate),
	m_carbDegree(Carbdegree / 180 * PI),
	m_angleRate(Anglerate / 180 * PI), m_anglePlus(0),
	m_stopFrame(StopFrame), m_stopFrameCount(0), m_stopCarbAngle(0) {
	if (StopCarbAngle != INF) {
		//m_stopCarbAngleが負の時は、Angleに依存してm_stopCarbAngleを変化させる。
		m_stopCarbAngle =
			(StopCarbAngle > 0 ?
				StopCarbAngle / 180 * PI :
				(StopCarbAngle + Angle) / 180 * PI);

		//0<m_stopCarbAngle<2*PIの範囲に収める
		m_stopCarbAngle -= 2 * PI*(int)(m_stopCarbAngle / (2 * PI));
		if (m_stopCarbAngle < 0) m_stopCarbAngle += 2 * PI;
	}
	else m_stopCarbAngle = INF;
}

//goalx,goalyからangleを計算する。
AutoMover::AutoMover(float X, float Y, float GoalX, float GoalY, int ImageType,
	float Speed, float Speedrate, double Angle, double Carbdegree,
	double Anglerate, int StopFrame, double StopCarbAngle) :
	Mover(X, Y, Speed, Angle), m_imageType(ImageType), m_speedRate(Speedrate),
	m_carbDegree(Carbdegree / 180 * PI),
	m_angleRate(Anglerate / 180 * PI), m_anglePlus(0),
	m_stopFrame(StopFrame), m_stopFrameCount(0), m_stopCarbAngle(0) {

	float diffx, diffy;
	diffx = GoalX - X;
	diffy = GoalY - Y;

	/*
	atan2...二点の座標から直角三角形を考え、
	その角の大きさを返してくれる関数。(ライブラリ:cmath)
	*/
	m_angle += atan2(diffy, diffx) + PI / 2;

	if (StopCarbAngle != INF) {
		//m_stopCarbAngleが負の時は、Angleに依存してm_stopCarbAngleを変化させる。
		m_stopCarbAngle =
			(StopCarbAngle > 0 ?
				StopCarbAngle / 180 * PI :
				(StopCarbAngle + Angle) / 180 * PI);

		//0<m_stopCarbAngle<2*PIの範囲に収める
		m_stopCarbAngle -= 2 * PI*(int)(m_stopCarbAngle / (2 * PI));
		if (m_stopCarbAngle < 0) m_stopCarbAngle += 2 * PI;
	}
	else m_stopCarbAngle = INF;
}

void AutoMover::Update() {
	if (m_speed <= 0) {
		m_speed = 0;
		if (m_stopFrameCount == m_stopFrame) {
			m_speedRate *= -1;
			m_speed += m_speedRate;
		}
		else m_stopFrameCount++;
	}
	//リミット値を設ける
	else if (m_speed <= 20)m_speed += m_speedRate;

	//0<m_angle<2*PIの範囲に収める
	m_angle -= 2 * PI*(int)(m_angle / (2 * PI));
	if (m_angle < 0) m_angle += 2 * PI;

	if (!(m_stopCarbAngle >= m_angle &&
		m_stopCarbAngle <= m_angle + (m_carbDegree + m_anglePlus)*m_speed ||
		m_stopCarbAngle <= m_angle &&
		m_stopCarbAngle >= m_angle + (m_carbDegree + m_anglePlus)*m_speed)) {
		m_angle += (m_carbDegree + m_anglePlus)*m_speed;
		m_anglePlus += m_angleRate * m_speed;
		
	}
	else m_angle = m_stopCarbAngle;
	//北方向を0度として計算したいので、yは-cos,xはsin,と入れ替えて使用する。
	m_x += (float)sin(m_angle)*m_speed;
	m_y += -(float)cos(m_angle)*m_speed;

	/*
	画面外に行ったものを削除するため、もし画面外に出たならalive=falseにする。
	尚、不自然にものが消えてしまうことを防ぐため、
	ものが消える範囲を実際のウインドウサイズより多少大きくしてある。
	*/
	if (m_x > WINDOW_WIDE * 2 || m_x < WINDOW_WIDE  *-1 ||
		m_y > WINDOW_HEIGHT * 2 || m_y < WINDOW_HEIGHT*-1) m_alive = false;
}