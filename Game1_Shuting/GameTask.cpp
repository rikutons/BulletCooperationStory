#include <vector>
#include "GameTask.h"
#include "Common.h"
#include "Player.h"
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
#define PLAYER_X 400.f
#define PLAYER_Y 200.f

//-------------------------------------------------------------------------------------------------

//PlayerTaskを簡略化した名称。よく使う、また一つしかないため簡略化した
Player P(0, 0, 0.f, 0);

//ポインタ型にしたのは、deleteしたかったから
vector<Enemy*> EnemyTask;
vector<Bullet*> BulletTask;

void InitializeTask() {
	Player p(PLAYER_X, PLAYER_Y, 0.f, 0);
	P = p;
	PlayerInitialize();
	EnemyInitialize();
	EnemyAddInitialize();
	BulletInitialize();
	GameSystemInitialize();
}

void UpdateTask() {
	//要素数を表す変数
	int Size;

	//Player
	P.Update();

	//Enemy
	//追加
	EnemyAdd(&EnemyTask);
	//移動
	Size = EnemyTask.size();
	for (int i = 0; i < Size;i++) {
		EnemyTask[i]->Update();
		//プレイヤーのx座標、y座標を使って弾を発射する
		EnemyTask[i]->BulletPlus(BulletTask,P.GetX(), P.GetY());	
		//alive==falseなら,敵を削除する
		if (EnemyTask[i]->GetAlive() == false) { 
			delete EnemyTask[i];		//メモリを開放しておく
			EnemyTask.erase(EnemyTask.begin() + i);
			i--; Size--;
		}
	}

	//Bullet
	//サイズソートをのちに実装((弾が重なった時の描画をきれいに
	Size = BulletTask.size();
	for (int i = 0; i < Size; i++) {
		BulletTask[i]->Update();
		BulletTask[i]->IsHit(P.GetX(),P.GetY());
		if (BulletTask[i]->GetAlive() == false) {
			delete BulletTask[i];
			BulletTask.erase(BulletTask.begin() + i);
			i--; Size--;
		}
	}

	//System
	void GameSystemUpdate();
}

void DrawTask() {
	//System 背景を含むので、一番最初に描画
 	GameSystemDraw();

	//debug
	
	DrawFormatString(0, 0, GetColor(255, 255, 255), 
				"bullet.size():%d,enemy.size():%d", BulletTask.size(), EnemyTask.size());
	

	//Player
	P.Draw();
	
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
}

void FinalizeTask() {
	//Playerは、動的に確保していないのでdeleteしないでよい

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