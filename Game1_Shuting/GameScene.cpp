#include <vector>
#include "GameScene.h"
#include "Common.h"
#include "Player.h"
#include "Weapon.h"
#include "Enemy.h"
#include "EnemyAdd.h"
#include "EffectMgr.h"
#include "Bullet.h"
#include "GameSystem.h"
#include "GameoverSelect.h"
#include "MyDxlib.h"
#include "EscapeSelect.h"

#include "DxLib.h"//debug

using namespace std;

//-------------------------------------------------------------------------------------------------
//定数

//プレイヤーの座標の初期値
const float PlayerSpawnX[] = { 215.f,585.f };
const float PlayerSpawnY[] = { 540.f,540.f };
//-------------------------------------------------------------------------------------------------

//プレイヤーの数は固定なので、固定長配列を使用する
namespace {
	Player playerTask[PLAYER_NUM];
	vector<Weapon> weaponTask;
	vector<Enemy*> enemyTask; //Bossを継承するのでポインタに
	vector<Bullet> bulletTask;
	GameOverSelect gameOverTask;
	EscapeSelect escapeTask;
}

Game::Game() {
	Player p1(PlayerSpawnX[0], PlayerSpawnY[0], 0);
	Player p2(PlayerSpawnX[1], PlayerSpawnY[1], 1);
	playerTask[0] = p1;
	playerTask[1] = p2;
	PlayerInitialize();
	WeaponInitialize();
	EnemyInitialize();
	EnemyAddInitialize();
	BulletInitialize();
	GameSystemInitialize();

	GameOverSelect g;
	gameOverTask = g;

	EscapeSelect e;
	escapeTask = e;
}

void Game::Update() {
	//System trueならゲームオーバーにして、その他の更新処理を行わない
	if (GetIsGameOver()) {
		gameOverTask.Update();
		return;
	}
	else if (GetIsSelectEscape()) {
		escapeTask.Update();
		return;
	}
	//要素数を表す変数
	int size;

	//Player
	for (int i = 0; i < PLAYER_NUM; i++)
	{
		if (playerTask[i].GetAlive()) {
			playerTask[i].Update();
			playerTask[i].WeaponPlus(weaponTask);
		}
	}

	//Weapon
	size = (int)weaponTask.size();
	for (int i = 0; i < size; i++)
	{
		weaponTask[i].Update();
		if (weaponTask[i].GetAlive() == false) {//alive==falseなら,武器を削除する
			weaponTask.erase(weaponTask.begin() + i);
			i--; size--;
		}
	}
	weaponTask.shrink_to_fit();//削除した分のメモリを開放する

	//Bullet bulletを先に動かしたいのでEnemyと順番を入れ替える
	size = (int)bulletTask.size();
	for (int i = 0; i < size; i++) {
		bulletTask[i].Update();
		for (int j = 0; j < PLAYER_NUM; j++)//当たり判定
		{
			if (playerTask[j].GetInvTime() != 0 ||
				playerTask[j].GetAlive() == false) continue;
			if (bulletTask[i].IsHit(
				playerTask[j].GetX(), playerTask[j].GetY())) {
				LifeDown();
				playerTask[j].InvTimePlus();
				playerTask[j].SetX(PlayerSpawnX[j]);
				playerTask[j].SetY(PlayerSpawnY[j]);
			}
		}
		if (bulletTask[i].GetAlive() == false) {
			bulletTask.erase(bulletTask.begin() + i);
			i--; size--;
		}
	}
	bulletTask.shrink_to_fit();

	//Enemy
	//追加処理
	EnemyAdd(enemyTask);
	//移動、弾の発射、削除
	size = (int)enemyTask.size();
	for (int i = 0; i < size; i++) {
		enemyTask[i]->Update();
		//プレイヤーのx座標、y座標を使って弾を発射する
		int aim = enemyTask[i]->GetAimP();
		if (playerTask[0].GetAlive() == false) aim = 1;
		if (playerTask[1].GetAlive() == false) aim = 0;
		enemyTask[i]->BulletPlus(
			bulletTask, playerTask[aim].GetX(), playerTask[aim].GetY());
		for (auto &j : weaponTask)//当たり判定
		{
			if (enemyTask[i]->IsHit(j.GetX(), j.GetY(), j.GetWeaponNum())) {
				j.SetAlive(false);
			}
		}
		if (enemyTask[i]->GetAlive() == false) {
			enemyTask.erase(enemyTask.begin() + i);
			i--; size--;
		}

	}
	bulletTask.shrink_to_fit();

	//System
	GameSystemUpdate();
	EffectMgrUpdate();

}

void Game::Draw() {
	//BackGround
	BackGroundDraw();

	//Player
	for (int i = 0; i < PLAYER_NUM; i++) playerTask[i].Draw();

	//Weapon
	for (auto i : weaponTask) i.Draw();

	//Enemy
	for (auto i : enemyTask) i->Draw();

	//Bullet
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	for (auto i : bulletTask) i.Draw();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	EffectMgrDraw();

	//System
	GameSystemDraw();

	if (GetIsGameOver()) {
		gameOverTask.Draw();
	}
	else if (GetIsSelectEscape()) {
		escapeTask.Draw();
		return;
	}
}

Game::~Game() {
	//Playerは、動的に確保していないのでdeleteしないでよい

	//Weapon
	vector<Weapon>().swap(weaponTask);

	//Bullet
	vector<Bullet>().swap(bulletTask);

	//Enemy
	vector<Enemy*>().swap(enemyTask);
}
