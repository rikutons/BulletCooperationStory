#include <vector>
#include "Enemy.h"
#include "EnemyAdd.h"
#include "GameSystem.h"
#include "Common.h"
#include "BulletMode.h"
#include "DxLib.h"

int Faze;
int ETime;

void EnemyAddInitialize() {
	Faze = 0;
	ETime = 0;
}

//Enemy(float X, float Y, int _ImageType, eBulletMode Mode, int Score, float Speed, float Speedrate, double Angle, double Carbdegree, double Anglerate) :
//Enemy(float X, float Y, float GoalX, float GoalY, int _ImageType, eBulletMode Mode, int Score, float Speed, float Speedrate, double Carbdegree, double Anglerate) :
void EnemyAdd(std::vector<Enemy*> *enemy) {
	ETime++;
	switch (Faze) {
	case 0:
		if (ETime == 10) {
			//enemy->push_back(new Enemy(BossX, BossY, 0, eBoss1, 50000, 1, 0, 0.0, 0.005, 0.0));
			enemy->push_back(new Enemy(BossX,BossY,0,eM1Spiral,50000,0,0,0.0,0,0.0));
		}
		break;
	}
}