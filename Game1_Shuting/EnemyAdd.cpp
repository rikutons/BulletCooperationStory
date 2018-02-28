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

int faze;
int addCount;

void EnemyAddInitialize() {
	faze = 0;
	addCount = 0;
}

/*
Enemy(float X, float Y, int ImageType, eBulletMode Mode,
	int Score, int Life, float Speed, float Speedrate, double Angle,
	double Carbdegree, double Anglerate, double BulletAngle, int BulletColor) :

Enemy(float X, float Y, float GoalX, float GoalY,
	int ImageType, eBulletMode Mode, int Score, int Life,
	float Speed, float Speedrate, double Carbdegree,
	double Anglerate, double BulletAngle, int BulletColor) :
*/

void EnemyAdd(std::vector<Enemy> &enemy) {
	addCount++;
	switch (faze) {
	case 0:
		if (addCount == 10) {
			enemy.push_back(Enemy(
				BOSS_X, BOSS_Y, 0, eMulti1,
				50000, 30, 0, 0, 0.0,
				0, 0.0, 0, 0)
			);
		}
		break;
	}
}