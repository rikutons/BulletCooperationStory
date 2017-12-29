#pragma once
#include "Mover.h"

void PlayerInitialize();

/*
プレイヤーとファンネルのクラス。
引数は(4+0)つ。
*/
class Player:public Mover {
	double FunnelAngle;
public:
	Player(float X, float Y, float Speed, double Angle);
	void Update();
	void Draw();

	float GetX(){ return x; }
	float GetY(){ return y; }
};