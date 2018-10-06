#include <vector>
#include "BulletMode.h"
#include "Bullet.h"
#include "GameSystem.h"
#include "DxLib.h"

using namespace std;
//-----------------------------------------------------------------------------
//定数
#define SPEED_SLOW 3.f
#define SPEED_FAST 10.f
#define SPEED_LASER 7.5f
#define SPEED_LASER_BIG 10.f
#define SPEED_LASER_MEGA 20.f
#define B0MINI_SIZE 0.05f
#define B0SIZE 0.1f
#define B0BIG_SIZE 0.3f
#define B0MEGA_SIZE 1.f
#define B2SIZE 0.15f
//-----------------------------------------------------------------------------

/*
Spiral 全方向
Straight 一方向集中

最後の英語、数字の意味
R.ランダム
P.プレイヤー座標準拠
D.二層 T.三層
A.超加速型
B.ビッグサイズ
M.メガサイズ
C.色変更有
S.一度止まって加速
Rf.反射
数字.一度に発車する球数

*/

void BulletAdd(eBulletMode mode, std::vector<Bullet> &bullet,
	float ex, float ey,
	float cx, float cy, double *angle, int *color) {
	switch (mode) {
		//途中の中括弧は折り畳み用
	case eT: {
		bullet.push_back(Bullet(
			ex, ey,
			0, *color, B0BIG_SIZE,
			SPEED_LASER, 0.f,
			*angle, 1 / 6.0, 0.0,
			0, INF, 10
		));
		break;
	}
			 /* for copy

			 case: {
				 break;
			 }

			 */

	case eNoneMode:
		break;
	case eSpiral4: {
		for (int i = 0; i < 4; i++) {
			bullet.push_back(Bullet(
				ex, ey,
				0, *color, B0SIZE,
				SPEED_SLOW, 0.f,
				i * 90 + *angle, 1 / 6.0, 0.0,
				0, -330
			));
		}
		*angle += 5;
		break;
	}
	case eSpiral6: {
		for (int i = 0; i < 6; i++) {
			bullet.push_back(Bullet(
				ex, ey,
				0, *color, B0SIZE,
				SPEED_SLOW, 0.f,
				i * 60 + *angle, 1 / 6.0, 0.0,
				0, -330
			));
		}
		*angle += 5;
		break;
	}
	case eSpiral6P: {
		for (int i = 0; i < 6; i++) {
			bullet.push_back(Bullet(
				ex, ey, cx, cy,
				0, *color, B0SIZE,
				SPEED_FAST, 0.f,
				i * 60 + *angle, 0.0, 0.0
			));
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
				0, -330
			));
		}
		*angle += 5;
		break;
	}
	case eSpiralRfP32: {
		for (int i = 0; i < 32; i++) {
			bullet.push_back(Bullet(
				ex, ey, cx, cy,
				2, *color, B2SIZE,
				2.f, 0.001f,
				i * 11.25 + *angle, 0.0, 0.0,
				0, INF, 114514
			));
		}
		break;
	}
	case eSpiralSPD32: {
		for (int i = 0; i < 32; i++) {
			bullet.push_back(Bullet(
				ex, ey, cx, cy,
				0, *color, B0SIZE,
				3.4f, -0.085f,
				i * 11.25 + *angle, 1 / 12.0, 0.0,
				60, -90
			));
			bullet.push_back(Bullet(
				ex, ey, cx, cy,
				0, (*color + 3) % 12, B0SIZE,
				2.f, -0.05f,
				i * 11.25 + *angle, 1 / 12.0, 0.0,
				60, -90
			));
		}
		break;
	}
	case eSpiralRC: {
		bullet.push_back(Bullet(
			ex, ey,
			1, GetRand(11), 0.2f,
			1.2f, GetRand(10)*-0.01f,
			0.01*GetRand(360000) + *angle, 1 / 6.0, 0.0,
			0, -330
		));
		break;
	}
	case eStraightB1: {
		bullet.push_back(Bullet(
			ex, ey,
			0, *color, B0BIG_SIZE,
			SPEED_LASER, 0.f,
			*angle, 0.0, 0.0
		));
		break;
	}
	case eStraightMC1: {
		bullet.push_back(Bullet(
			ex, ey,
			0, *color, B0MEGA_SIZE,
			SPEED_LASER_MEGA, 0.f,
			*angle, 0.0, 0.0
		));
		if (GetGameTime() % 4 == 0)++*color;
		if (*color == 12) *color = 0;
		break;
	}
	case eStraightP1: {
		bullet.push_back(Bullet(
			ex, ey, cx, cy,
			0, *color, B0SIZE,
			SPEED_SLOW, 0.f,
			*angle, 0.0, 0.0
		));
		break;
	}
	case eStraightPB1: {
		bullet.push_back(Bullet(
			ex, ey, cx, cy,
			0, *color, B0BIG_SIZE,
			SPEED_FAST, 0.f,
			*angle, 0.0, 0.0
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
				(i - 1) * 30 + *angle, 0.0, 0.0
			));
		}
		break;
	}
	case eStraightSlashD9: {
		//angleを使って制御
		*angle += 10;
		if (*angle <= 90) {
			bullet.push_back(Bullet(
				ex, ey,
				0, *color, B0SIZE,
				3.f, 0.2f,
				220 - *angle, 0.0, 0.0
			));
			bullet.push_back(Bullet(
				ex, ey,
				0, *color, B0SIZE,
				3.f, 0.2f,
				*angle - 220, 0.0, 0.0
			));
		}
		if (*angle == 180) *angle = 0;
		break;
	}
	case eStraightPDA9: {
		for (int i = 0; i < 9; i++)
		{
			bullet.push_back(Bullet(
				ex, ey, cx, cy,
				0, *color, B0SIZE,
				1.0f, 0.16f,
				(i - 4) * 20 + *angle, 0.0, 0.0
			));
			bullet.push_back(Bullet(
				ex, ey, cx, cy,
				0, *color, B0SIZE,
				0.5f, 0.1f,
				(i - 4) * 20 + *angle, 0.0, 0.0
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
				2, GetRand(11), B2SIZE,
				0.4f, 0.16f,
				lo_angle, carbDegree, angleRate,
				0, 180
			));
		}
		break;
	}
	case eMediumBoss1: {
		int roop = (int)(*angle / 120) + 1;  //一度に生成する弾数
		for (int i = 0; i < roop; i++)
		{
			int lo_angle = GetRand(360);
			int bulletType = GetRand(3);
			float size = GetRand(15)*0.01f + 0.1f;
			float speed = GetRand(100)*0.1f + 3.f;
			float speedRate = 0.3f / speed;
			bullet.push_back(Bullet(
				ex, ey,
				bulletType, GetRand(11), size,
				speed, speedRate,
				lo_angle, 0.0, 0
			));
		}
		if (*angle < 360) *angle += 1;
		break;
	}
	case eMediumBoss2: {
		for (int i = 0; i < 4; i++) {
			bullet.push_back(Bullet(
				ex, ey,
				0, *color, B0SIZE,
				SPEED_SLOW - 1.f, 0.f,
				sin(*angle / 180 * PI) * 90 + 180 + i * 25 - 50, 0.0, 0.0
			));
		}
		*angle += 5;
		break;
	}
	case eBoss1_1: {
		for (int i = 0; i < 5; i++) {
			bullet.push_back(Bullet(
				ex, ey,
				1, *color, 0.3f,
				SPEED_FAST, 0.f,
				i * 72 + *angle, 0.0, 0.0
			));
		}
		*angle += 36;
		break;
	}
	case eBoss1_1Object: {
		//int roop = (int)(GetRand(5)/5);//一度に生成する弾数
		int roop = 1;
		for (int i = 0; i < roop; i++)
		{
			int lo_angle = GetRand(360);
			bullet.push_back(Bullet(
				ex, ey,
				2, GetRand(11), B0SIZE,
				0.f, -0.001f,
				lo_angle + *angle, 0.0, 0.0,
				60
			));
		}
		*angle -= 8;
		break;
	}
	}
}