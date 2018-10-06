#pragma once
#include "Mover.h"
#include "Common.h"

void BulletInitialize();

/*
ボスを含む敵全員のクラス。引数の順番を変えているので注意
引数(8+2=)10個。または、追尾(9+2=)11個。 12.弾の色 13.弾のサイズ
*/
class Bullet :public AutoMover {
	int m_color;
	float m_size;
public:
	Bullet(float, float, int, int, float, float, float,
		double, double, double,
		int StopFrame = 0, double StopCarbAngle = INF, int ReflectCount = 0);
	Bullet(float, float, float, float, int, int, float, float, float,
		double, double, double,
		int StopFrame = 0, double StopCarbAngle = INF, int ReflectCount = 0);
	void Update() { AutoMover::Update(); };
	void Draw();
	bool IsHit(const float, const float);
};