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
	int score;
	int time;
	eBulletMode mode;
	//発射する弾の色を保管する
	double Brotation;
	int Bcolor;
public:
	Enemy(float X, float Y, int _ImageType, eBulletMode Mode,
		int Score, float Speed, float Speedrate, double Angle,
		double Carbdegree, double Anglerate, double BRotation,int BColor);
	Enemy(float X, float Y, float GoalX, float GoalY,
		int _ImageType, eBulletMode Mode, int Score,
		float Speed, float Speedrate, double Carbdegree,
		double Anglerate, double BRotation, int BColor);
	void Update() { AutoMover::Update(); };
	void Draw();
	void BulletPlus(std::vector<Bullet*> &bullet,float cx, float cy);
};

