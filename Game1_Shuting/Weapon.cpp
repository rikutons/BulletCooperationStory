#include "dxlib.h"
#include "Keybord.h"
#include "SceneMgr.h"
#include "Common.h"
#include "Weapon.h"
#include <cmath>


namespace {
	int image[2];
}

void WeaponInitialize() {
	image[0] = LoadGraph("../material/picture/Weapon01.png");
	image[1] = LoadGraph("../material/picture/Weapon02.png");
}


Weapon::Weapon(float X, float Y, int WeaponNum, float speed, double Angle) :
	Mover(X, Y, speed, Angle), m_weaponNum(WeaponNum) {}


void Weapon::Update() {
	m_x += (float)sin(m_angle)*m_speed;
	m_y += -(float)cos(m_angle)*m_speed;
	/*
	画面外に行った武器を削除するため、もし画面外に出たならalive=falseにする。
	尚、不自然に武器が消えてしまうことを防ぐため、
	ものが消える範囲を実際のウインドウサイズより多少大きくしてある。
	武器は上にしか動かないので、y座標のマイナス判定のみ行う。
	*/
	if (m_y < WINDOW_HEIGHT*-0.2) m_alive = false;
}

void Weapon::Draw() {
	DrawRotaGraphF(m_x, m_y, 0.1, m_angle, image[m_weaponNum], TRUE);
}
