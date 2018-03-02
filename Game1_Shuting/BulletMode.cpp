#include <vector>
#include "BulletMode.h"
#include "Bullet.h"
#include "DxLib.h"

using namespace std;
//-----------------------------------------------------------------------------
//定数
#define B0SIZE 0.1f
#define B0BIGSIZE 0.2f
//-----------------------------------------------------------------------------

/*
Spiral 渦巻き
Straight 一方向集中
Laser レーザー

最後の英語、数字の意味
R.ランダム
P.プレイヤー座標準拠
D.二層 T.三層
A.加速型
B.ビッグサイズ
数字.一度に発車する球数

*/

void BulletAdd(eBulletMode mode, std::vector<Bullet> &bullet,
	float ex, float ey,
	float cx, float cy, double *angle, int *color) {
	switch (mode) {
		//途中の中括弧は折り畳み用
	case eTest: {
		bullet.push_back(Bullet(
			ex, ey,
			0, *color, B0SIZE,
			2.f, 0.f,
			*angle, 1 / 6.0, 0.0,
			0, -360
		));
		*angle += 5;
	}
	case eSpiral4: {
		for (int i = 0; i < 4; i++) {
			bullet.push_back(Bullet(
				ex, ey,
				0, *color, B0SIZE,
				2.f, 0.f,
				i * 90 + *angle, 1 / 6.0, 0.0,
				0, -30
			));
			*angle += 5;
		}
		break;
	}
	case eSpiral8: {
		for (int i = 0; i < 8; i++) {
			bullet.push_back(Bullet(
				ex, ey,
				0, *color, B0SIZE,
				2.f, 0.f,
				i * 45 + *angle, 1 / 6.0, 0.0,
				0, -360
			));
			*angle += 5;
		}
		break;
	}
	case eStraightPB1: {
		bullet.push_back(Bullet(
			ex, ey, cx, cy,
			0, *color, B0BIGSIZE,
			20.f, 0.f,
			0, 0.0, 0.0
		));
		break;
	}
	case eStraightP3: {
		for (int i = 0; i < 3; i++)
		{
			bullet.push_back(Bullet(
				ex, ey, cx, cy,
				0, *color, B0SIZE,
				1.0f, 0.025f,
				(i - 1) * 30, 0.0, 0.0
			));
		}
		break;
	}
	case eStraightPDA9: {
		for (int i = 0; i < 9; i++)
		{
			bullet.push_back(Bullet(
				ex, ey, cx, cy,
				0, *color, B0SIZE,
				1.0f, 0.16f,
				(i - 4) * 20, 0.0, 0.0
			));
			bullet.push_back(Bullet(
				ex, ey, cx, cy,
				0, *color, B0SIZE,
				0.5f, 0.1f,
				(i - 4) * 20, 0.0, 0.0
			));
		}
		break;
	}
	case eStraightFallR: {
		int roop = GetRand(3);//一度に生成する弾数
		for (int i = 0; i < roop; i++)
		{
			int lo_angle = GetRand(360);
			double carbDegree = (180 - lo_angle) / 540.0;
			double angleRate = carbDegree / -900;
			bullet.push_back(Bullet(
				ex, ey,
				0, GetRand(11), B0SIZE,
				0.4f, 0.16f,
				lo_angle, carbDegree, angleRate,
				0, 180
			));
		}
		break;
	}
						 //Boss1
	case eBoss1_1:
		break;
	}
};