#pragma once
#include "Mover.h"

void BulletInitialize();

/*
ボスを含む敵全員のクラス。引数の順番を変えているので注意
引数(8+2=)10個。または、追尾(9+2=)11個。 12.弾の色 13.弾のサイズ
*/
class Bullet :public AutoMover {
	int color;
	float size;
public:
	Bullet(float X, float Y, int _ImageType, int Color, float Size, float Speed, float Speedrate, double Angle, double Carbdegree, double Anglerate);
	Bullet(float X, float Y, float GoalX, float GoalY, int _ImageType, int Color, float Size, float Speed, float Speedrate, double Carbdegree, double Anglerate);
	void Update() { AutoMover::Update(); };
	void Draw();
	void IsHit(const float cx, const float cy, const int playerNum);
};