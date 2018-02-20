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
	double FunnelAngle;
	int playerNum;
public:
	Player();
	Player(float X, float Y, int PlayerNum);
	void Update();
	void Draw();
	void WeaponPlus(std::vector<Weapon*> *Weapon);

	float GetX() { return x; }
	float GetY() { return y; }
};