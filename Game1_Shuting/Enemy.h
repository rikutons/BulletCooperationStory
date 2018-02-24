#pragma once
#include <vector>
#include "Mover.h"
#include "Bullet.h"
#include "BulletMode.h"

void EnemyInitialize();

/*
ボスを含む敵全員のクラス。引数の順番を変えているので注意
引数(8+4=)12個。または、追尾(9+4=)13個。 12.倒した時のスコア
13.弾を出すパターン 99以下 n番目のパターンを永続的に出す 100以上 複数パターンの融合
14.発射する弾の色(変動する場合は最初の色) 15.発射する弾の発射角(60分法)
*/
class Enemy :public AutoMover {
	int m_score;
	int m_time;
	eBulletMode mode;
	//発射する弾の色を保管する
	double m_bulletAngle;
	int m_bulletColor;
public:
	Enemy(float, float, int, eBulletMode,
		int, float, float, double,
		double, double, double, int);
	Enemy(float, float, float, float,
		int, eBulletMode, int,
		float, float, double,
		double, double, int);
	void Update() { AutoMover::Update(); };
	void Draw();
	void BulletPlus(std::vector<Bullet>&, float, float);
};

