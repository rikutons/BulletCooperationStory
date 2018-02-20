#include <vector>
#include "GameTask.h"
#include "Common.h"
#include "Player.h"
#include "Weapon.h"
#include "Enemy.h"
#include "Bullet.h"
#include "BulletMode.h"
#include "GameSystem.h"
#include "EnemyAdd.h"

#include "DxLib.h"//debug

using namespace std;

//-------------------------------------------------------------------------------------------------
//定数

//プレイヤーの座標の初期値
#define PLAYER1_X 200.f
#define PLAYER1_Y 400.f

#define PLAYER2_X 500.f
#define PLAYER2_Y 400.f
//-------------------------------------------------------------------------------------------------

//PlayerTaskを簡略化した名称。よく使う、また二つしかないため簡略化した
Player P[PLAYER_NUM];

//ポインタ型にしたのは、deleteしたかったから
vector<Weapon*> WeaponTask;
vector<Enemy*> EnemyTask;
vector<Bullet*> BulletTask;

void InitializeTask() {
	Player p1(PLAYER1_X, PLAYER1_Y, 0);
	Player p2(PLAYER2_X, PLAYER2_Y, 1);
	P[0] = p1;
	P[1] = p2;
	PlayerInitialize();
	WeaponInitialize();
	EnemyInitialize();
	EnemyAddInitialize();
	BulletInitialize();
	GameSystemInitialize();
}

void UpdateTask() {
	//要素数を表す変数
	int Size;

	//Player
	for (int i = 0; i < PLAYER_NUM; i++)
	{
		P[i].Update();
		P[i].WeaponPlus(&WeaponTask);
	}
	
	//Weapon
	Size = (int)WeaponTask.size();
	for (int i = 0; i < Size; i++)
	{
		WeaponTask[i]->Update();
		//alive==falseなら,武器を削除する
		if (WeaponTask[i]->GetAlive() == false) {
			delete WeaponTask[i];		//メモリを開放しておく
			WeaponTask.erase(WeaponTask.begin() + i);
			i--; Size--;
		}
	}

	//Enemy
	//追加
	EnemyAdd(&EnemyTask);
	//移動
	Size = (int)EnemyTask.size();
	for (int i = 0; i < Size; i++) {
		EnemyTask[i]->Update();
		//プレイヤーのx座標、y座標を使って弾を発射する
		EnemyTask[i]->BulletPlus(BulletTask, P[0].GetX(), P[0].GetY());
		//alive==falseなら,敵を削除する
		if (EnemyTask[i]->GetAlive() == false) {
			delete EnemyTask[i];		//メモリを開放しておく
			EnemyTask.erase(EnemyTask.begin() + i);
			i--; Size--;
		}
	}

	//Bullet
	//サイズソートをのちに実装((弾が重なった時の描画をきれいに
	Size = (int)BulletTask.size();
	for (int i = 0; i < Size; i++) {
		BulletTask[i]->Update();
		for (int j = 0; j < PLAYER_NUM; j++)
		{
			//BulletTask[i]->IsHit(P[j].GetX(), P[j].GetY());
		}
		if (BulletTask[i]->GetAlive() == false) {
			delete BulletTask[i];
			BulletTask.erase(BulletTask.begin() + i);
			i--; Size--;
		}
	}

	//System
	GameSystemUpdate();
}

void DrawTask() {
	//BackGround
	BackGroundDraw();

	//debug

	//DrawFormatString(0, 0, GetColor(255, 255, 255), 
	//			"bullet.size():%d,enemy.size():%d", BulletTask.size(), EnemyTask.size());


	//Player
	for (int i = 0; i < PLAYER_NUM; i++) {
		P[i].Draw();
	}

	//Weapon
	for (auto i : WeaponTask) {
		i->Draw();
	}

	//Bullet
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);	//加算表示
	for (auto i : BulletTask) {
		i->Draw();
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//Enemy
	for (auto i : EnemyTask) {
		i->Draw();
	}

	//System
	GameSystemDraw();
}

void FinalizeTask() {
	//Playerは、動的に確保していないのでdeleteしないでよい

	//Weapon
	for (auto i : WeaponTask) {
		delete i;
	}
	WeaponTask.clear();

	//Enemy
	for (auto i : EnemyTask) {
		delete i;
	}
	EnemyTask.clear();

	//Bullet
	for (auto i : BulletTask) {
		delete i;
	}
	BulletTask.clear();
}