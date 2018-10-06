#pragma once
#include <vector>
#include "Enemy.h"

class Boss :public Enemy {
	int m_moveStartFrame;
	int m_moveFrame;
	int m_bulletPattern;
	int m_beforeBulletPattern;
	int m_specialShotLife;
	bool m_isSpecialShot;
	int m_specialShotCount;
	bool m_isPlayEffect;
	bool m_isMoveCenter;
	int m_faze;
	void MoveCenter();
	eBulletMode m_nowMode;
public:
	Boss(
		int, eBulletMode,
		int, int,
		int, int, int);
	void BulletPlus(std::vector<Bullet>&, float, float);
	bool IsHit(float, float, int);
};