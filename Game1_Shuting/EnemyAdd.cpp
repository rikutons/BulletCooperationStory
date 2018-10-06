#include <vector>
#include "Enemy.h"
#include "Boss.h"
#include "BulletMode.h"
#include "DxLib.h"
#include "Common.h"
#include "SoundMgr.h"

namespace {
	int faze;
	int addCnt;
	int specialAdd;
	double g_angle;
}

void EnemyAddInitialize() {
	addCnt = 0;
	specialAdd = 0;
	g_angle = 0;
}

void SetFaze(int nextFaze) {
	faze = nextFaze;
	addCnt = 0;
	if (faze != 0) ChangeBGM(faze);
}

void EnemyAdd(std::vector<Enemy*> &enemy) {
	addCnt++;
	switch (faze) {
		/*for copy

		enemy.push_back(new Enemy(
		0, 0,
		0, e,
		0.f, 0.f,
		180, 0, 0.0,
		 ,0.0, ,
		));

		//BOSS ƒeƒ“ƒvƒŒ
		enemy.push_back(new Enemy(
		400, -200,
		0, e, true,
		1.f, 0.f,
		180, 0, 0.0,
		0, 1, 0
		));
		*/

		//debug faze
	case 0:
		if (addCnt == 10) {
			enemy.push_back(new Enemy(
				200, 50,
				7, eMediumBoss1,
				0, 0,
				240, 0, 0.0,
				0, 0.0, 150, 0
			));
		}
		break;
	case 1:
		if (addCnt >= 100 && addCnt <= 200) {
			if (addCnt % 10 == 0) {
				enemy.push_back(new Enemy(
					400.f + (addCnt - 100) * 3.4f, -200,
					0, eStraightP3,
					10, -0.1f,
					180, 45 / 200.0, 0.0,
					0, 0.0, 1, 1,
					120, 160, INF,
					270
				));
				enemy.push_back(new Enemy(
					400.f + (addCnt - 100) * -3.4f, -200,
					0, eStraightP3,
					10, -0.1f,
					180, -45 / 200.0, 0.0,
					0, 0.0, 1, 0,
					120, 160, INF,
					90
				));
			}
		}

		else if (addCnt >= 400 && addCnt <= 500) {
			if (addCnt % 12 == 6) {
				enemy.push_back(new Enemy(
					400.f + (addCnt - 400) * 3.4f, -200,
					0, eStraightP3,
					10, -0.1f,
					180, 45 / 200.0, 0.0,
					0, 0.0, 1, 1,
					120, 160, INF,
					270
				));
				enemy.push_back(new Enemy(
					400.f + (addCnt - 400) * -3.4f, -200,
					0, eStraightP3,
					10, -0.1f,
					180, -45 / 200.0, 0.0,
					0, 0.0, 1, 0,
					120, 160, INF,
					90
				));
			}
			if (addCnt % 12 == 0) {
				enemy.push_back(new Enemy(
					400.f + (addCnt - 400) * 3.4f, -100,
					0, eStraightP3,
					10, -0.1f,
					180, 45 / 200.0, 0.0,
					4, 0.0, 1, 0,
					120, 160, INF,
					270
				));
				enemy.push_back(new Enemy(
					400.f + (addCnt - 400) * -3.4f, -100,
					0, eStraightP3,
					10, -0.1f,
					180, -45 / 200.0, 0.0,
					4, 0.0, 1, 1,
					120, 160, INF,
					90
				));
			}
		}

		else if (addCnt >= 700 && addCnt <= 1000) {
			if (addCnt % 35 == 0) {
				//1 true,0 false
				int isStartRight = GetRand(1);
				float x;
				float y = (float)GetRand(200) - 30;
				//sign •„†
				int angleSign;
				int carbDegreeSign;
				if (isStartRight == 1)
					x = -100, carbDegreeSign = -1, angleSign = 1;
				else
					x = 900, carbDegreeSign = 1, angleSign = -1;
				enemy.push_back(new Enemy(
					x, y,
					1, eSpiral4,
					2.f, 0,
					angleSign*120.0, carbDegreeSign*3.4 / 60.0, 0.0,
					GetRand(11), 0.0, 3, 0,
					0, 90, 420
				));
			}
		}

		else if (addCnt == 1300) {
			enemy.push_back(new Boss(
				4, eMediumBoss1,
				10, 30,
				90, 90, 70
			));
		}
		break;
	case 2:
		if (addCnt >= 100 && addCnt <= 400) {
			if (addCnt % 30 == 0) {
				int isStartRight = GetRand(1);
				float x;
				float y = (float)GetRand(200) + 400;
				int angleSign;
				int aimNum;
				if (isStartRight == 1)
					x = -100, angleSign = 1, aimNum = 1;
				else
					x = 900, angleSign = -1, aimNum = 0;
				enemy.push_back(new Enemy(
					x, y,
					1, eStraightPDA9,
					17.5f, -0.1f,
					angleSign*60.0, angleSign * 10 / 60.0,
					-1 * angleSign * 1 / 2400.0,
					0, 0.0, 1, aimNum,
					120, 160, INF,
					180
				));
			}
		}
		if (addCnt == 300 || addCnt == 800) {
			enemy.push_back(new Enemy(
				-20, -20,
				2, eStraightB1,
				2.f, -0.025f,
				90 + 36.87, 0, 0,
				6, 90 + 36.87, 300, 0,
				200, 100, 260
			));
			enemy.push_back(new Enemy(
				820, -20,
				2, eStraightB1,
				2.f, -0.025f,
				-90 - 36.87, 0, 0,
				6, -90 - 36.87, 300, 0,
				200, 100, 260
			));
		}
		if (addCnt >= 600 && addCnt <= 1200) {
			if (addCnt % 8 == 0) {
				float x = GetRand(1000) - 100.f;
				double angle = GetRand(180) + 90.0;
				int aimNum = GetRand(1);
				enemy.push_back(new Enemy(
					x, -100,
					0, eStraightP1,
					3.f, 0,
					angle, 0, 0,
					11, 0, 5, aimNum
				));
			}
		}
		else if (addCnt == 1500) {
			enemy.push_back(new Boss(
				5, eMediumBoss2,
				5, 150,
				90, 120, 100
			));
		}
		break;
	case 3:
		if (addCnt == 100) {
			enemy.push_back(new Boss(
				7, eBoss1,
				15, 180,
				60, 160, 350
			));
		}
		if (specialAdd == 1) {
			for (int i = 0; i < 5; i++) {
				double lo_angle = i * 72 + g_angle;
				double bulletAngle = lo_angle + 180;
				enemy.push_back(new Enemy(
					400, 100,
					8, eBoss1_1Object,
					10.f, 0,
					lo_angle, 0, 0,
					11, bulletAngle, 150, 0
				));
			}
			specialAdd--;
		}
	}
}

void SetSpecialAdd(int s, double angle) {
	specialAdd = s;
	g_angle = angle;
}