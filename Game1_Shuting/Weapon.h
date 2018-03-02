#pragma once
#include "Mover.h"

void WeaponInitialize();

/*
プレイヤーとファンネルのクラス。
引数は(2+1)つ。
*/
class Weapon :public Mover {
	int m_weaponNum;
public:
	Weapon(float, float, int);
	void Update();
	void Draw();

	float GetX() { return m_x; }
	float GetY() { return m_y; }
	int GetWeaponNum() { return m_weaponNum; }
	void SetAlive(bool Alive) { m_alive = Alive; }
};