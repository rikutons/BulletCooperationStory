#pragma once
#include "Mover.h"
#include "Weapon.h"
#include "vector"

void PlayerInitialize();

/*
プレイヤーとファンネルのクラス。
引数は(4+0)つ。
*/
class Player :public Mover {
	double m_funnelAngle;
	int m_playerNum;
	int m_invincibleTime;
	bool m_isDraw; //描画するかどうか 点滅用
public:
	Player();
	Player(float, float, int);
	void Update();
	void Draw();
	void WeaponPlus(std::vector<Weapon>&);
	void InvTimePlus();
	int GetInvTime() { return m_invincibleTime; }
	float GetX() { return m_x; }
	float GetY() { return m_y; }
};