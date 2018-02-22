#include <vector>
#include "GameScene.h"
#include "Common.h"
#include "Player.h"
#include "Weapon.h"
#include "Enemy.h"
#include "EnemyAdd.h"
#include "Bullet.h"
#include "GameSystem.h"

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

vector<Weapon> WeaponTask;
vector<Enemy> EnemyTask;
vector<Bullet> BulletTask;


Game::Game() {
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

void Game::Update() {
	//要素数を表す変数
	int Size;

	//Player
	for (int i = 0; i < PLAYER_NUM; i++)
	{
		P[i].Update();
		P[i].WeaponPlus(WeaponTask);
	}

	//Weapon
	Size = (int)WeaponTask.size();
	for (int i = 0; i < Size; i++)
	{
		WeaponTask[i].Update();
		if (WeaponTask[i].GetAlive() == false) {//alive==falseなら,武器を削除する
			WeaponTask.erase(WeaponTask.begin() + i);
			i--; Size--;
		}
	}
	WeaponTask.shrink_to_fit();//削除した分のメモリを開放する

	//Enemy
	//追加処理
	EnemyAdd(EnemyTask);
	//移動、弾の発射、削除
	Size = (int)EnemyTask.size();
	for (int i = 0; i < Size; i++) {
		EnemyTask[i].Update();
		//プレイヤーのx座標、y座標を使って弾を発射する
		EnemyTask[i].BulletPlus(BulletTask, P[0].GetX(), P[0].GetY());
		if (EnemyTask[i].GetAlive() == false) {
			EnemyTask.erase(EnemyTask.begin() + i);
			i--; Size--;
		}
	}
	BulletTask.shrink_to_fit();

	//Bullet
	//サイズソートをのちに実装((弾が重なった時の描画をきれいに
	Size = (int)BulletTask.size();
	for (int i = 0; i < Size; i++) {
		BulletTask[i].Update();
		for (int j = 0; j < PLAYER_NUM; j++)//当たり判定
		{
			BulletTask[i].IsHit(P[j].GetX(), P[j].GetY(), j);
		}
		if (BulletTask[i].GetAlive() == false) {
			BulletTask.erase(BulletTask.begin() + i);
			i--; Size--;
		}
	}
	BulletTask.shrink_to_fit();

	//System trueならゲームオーバー
	if (GameSystemUpdate() == true) SetScene(eGameOver);
}

void Game::Draw() {
	//BackGround
	BackGroundDraw();

	//debug
	//DrawFormatString(0, 0, GetColor(255, 255, 255),
	//	"Bullet.capacity():%d,Bullet.size():%d", BulletTask.capacity(), BulletTask.size());

	//Player
	for (int i = 0; i < PLAYER_NUM; i++) P[i].Draw();

	//Bullet
	for (auto i : WeaponTask) i.Draw();

	//Bullet
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);	//加算表示
	for (auto i : BulletTask) i.Draw();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//Enemy
	for (auto i : EnemyTask) i.Draw();

	//System
	GameSystemDraw();
}

Game::~Game() {
	//Playerは、動的に確保していないのでdeleteしないでよい

	//Weapon
	vector<Weapon>().swap(WeaponTask);

	//Enemy
	vector<Enemy>().swap(EnemyTask);

	//Bullet
	vector<Bullet>().swap(BulletTask);
}