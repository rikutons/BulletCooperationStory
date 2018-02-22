#include <vector>
#include "Enemy.h"
#include "EnemyAdd.h"
#include "GameSystem.h"
#include "BulletMode.h"
#include "DxLib.h"

//-----------------------------------------------------
//定数
//ボスの座標の初期値
#define BOSS_X 400.f
#define BOSS_Y 100.f

//----------------------------------------------------

int Faze;
int ETime;

void EnemyAddInitialize() {
	Faze = 0;
	ETime = 0;
}

/*
Enemy(float X, float Y, int _ImageType, eBulletMode Mode,
	int Score, float Speed, float Speedrate, double Angle,
	double Carbdegree, double Anglerate, double BRotation, int BColor);

Enemy(float X, float Y, float GoalX, float GoalY,
	int _ImageType, eBulletMode Mode, int Score,
	float Speed, float Speedrate, double Carbdegree,
	double Anglerate, double BRotation, int BColor);
*/

void EnemyAdd(std::vector<Enemy> &enemy) {
	ETime++;
	switch (Faze) {
	case 0:
		if (ETime == 10) {
			enemy.push_back(Enemy(BOSS_X,BOSS_Y,0,eMulti1,50000,0,0,0.0,0,0.0,0,0));
		}
		break;
	}
}