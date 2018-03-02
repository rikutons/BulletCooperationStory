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
	eTest,
	eSpiral4,
	eSpiral8,	
	eStraightPB1,
	eStraightP3,
	eStraightPDA9,
	eStraightFallR,
	eBoss1 = 100,
	eBoss1_1,
	eBoss1_2,
	eBoss1_3,
	eMulti1
};

void BulletAdd(eBulletMode, std::vector<Bullet>&,
	float, float,
	float, float, double*, int*);
