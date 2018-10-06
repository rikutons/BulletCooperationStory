#pragma once
#include <vector>
#include "Bullet.h"


/*
Spiral 渦巻き
Straight 一方向集中
Laser レーザー

最後の英語、数字の意味
R.ランダム
P.プレイヤー座標準拠
D.二層 T.三層
A.加速型
数字.一度に発車する球数

*/

enum eBulletMode {
	eT,

	eNoneMode,
	//Spiral
	eSpiral4,
	eSpiral6,
	eSpiral6P,
	eSpiral8,
	eSpiralRfP32,
	eSpiralSPD32,
	eSpiralRC,

	//Straight
	eStraightB1,
	eStraightMC1,
	eStraightP1,
	eStraightPB1,
	eStraightP3,
	eStraightSlashD9,
	eStraightPDA9,
	eStraightFallR,

	//ボス
	eMediumBoss1=100,
	eMediumBoss2,
	eMediumBoss3,
	eBoss1,
	eBoss1_1,
	eBoss1_1Object
};

void BulletAdd(eBulletMode, std::vector<Bullet>&,
	float, float,
	float, float, double*, int*);
