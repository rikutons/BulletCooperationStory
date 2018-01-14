#pragma once
#include "Mover.h"

void WeaponInitialize();

/*
プレイヤーとファンネルのクラス。
引数は(4+0)つ。
*/
class Weapon :public Mover {
public:
	Weapon(float X, float Y);
	void Update();
	void Draw();

	float GetX() { return x; }
	float GetY() { return y; }
};