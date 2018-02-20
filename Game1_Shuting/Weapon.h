#pragma once
#include "Mover.h"

void WeaponInitialize();

/*
プレイヤーとファンネルのクラス。
引数は(2+1)つ。
*/
class Weapon :public Mover {
	int weaponNum;
public:
	Weapon(float X, float Y,int WeaponNum);
	void Update();
	void Draw();

	float GetX() { return x; }
	float GetY() { return y; }
};