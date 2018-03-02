#include <vector>
#include "Enemy.h"
#include "EnemyAdd.h"
#include "GameSystem.h"
#include "BulletMode.h"
#include "DxLib.h"

//-----------------------------------------------------
//定数
//ボスの座標の初期値
#define BOSS_X 200.f
#define BOSS_Y 100.f

//----------------------------------------------------
namespace {
	int faze;
	int addCnt;
}

void EnemyAddInitialize() {
	faze = 0;
	addCnt = 0;
}

/*
	Enemy(
	float X, float Y, int ImageType, eBulletMode Mode,
	int Score, int Life, float Speed, float Speedrate,
	double Angle,double Carbdegree, double Anglerate,
	double BulletAngle,int BulletColor, int ShotSpeed )

	Enemy(
	float X, float Y, float GoalX, float GoalY,
	int ImageType, eBulletMode Mode, int Score, int Life,
	float Speed, float Speedrate, double Carbdegree,
	double Anglerate, double BulletAngle,
	int BulletColor, int ShotSpeed )
*/

void EnemyAdd(std::vector<Enemy> &enemy) {
	addCnt++;
	switch (faze) {
	//debug faze
	case 0:
		if (addCnt % 10 == 0 && addCnt <= 10) {
			enemy.push_back(Enemy(
				600, 100,
				0, eTest, 50000, 30,
				0, 0,
				240, 0, 0.0,
				0, 30, 0
			));
		}
		break;
	case 1:
		if (addCnt % 10 == 0 && addCnt <= 100) {
			enemy.push_back(Enemy(
				900, -100,
				0, eStraightPDA9, 50000, 30,
				5 + addCnt / 20.f, -0.05f,
				240, 0, 0.0,
				0, 1, 0,
				60, 200 + addCnt
			));
		}

		break;
	}
}