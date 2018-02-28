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

//プレイヤーの数は固定なので、固定長配列を使用する
Player playerTask[PLAYER_NUM];
vector<Weapon> weaponTask;
vector<Enemy> enemyTask;
vector<Bullet> bulletTask;


Game::Game() {
	Player p1(PLAYER1_X, PLAYER1_Y, 0);
	Player p2(PLAYER2_X, PLAYER2_Y, 1);
	playerTask[0] = p1;
	playerTask[1] = p2;
	PlayerInitialize();
	WeaponInitialize();
	EnemyInitialize();
	EnemyAddInitialize();
	BulletInitialize();
	GameSystemInitialize();
}

void Game::Update() {
	//要素数を表す変数
	int size;

	//Player
	for (int i = 0; i < PLAYER_NUM; i++)
	{
		playerTask[i].Update();
		playerTask[i].WeaponPlus(weaponTask);
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

	//Enemy
	//追加処理
	EnemyAdd(enemyTask);
	//移動、弾の発射、削除
	size = (int)enemyTask.size();
	for (int i = 0; i < size; i++) {
		enemyTask[i].Update();
		//プレイヤーのx座標、y座標を使って弾を発射する
		enemyTask[i].BulletPlus(bulletTask, playerTask[0].GetX(), playerTask[0].GetY());
		/*for (auto &j : weaponTask) {
			if (enemyTask[i].IsHit(j.GetX(), j.GetY(),j.GetWeaponNum())) {
				j.SetAlive(false);
			}
		}*/
		if (enemyTask[i].GetAlive() == false) {
			enemyTask.erase(enemyTask.begin() + i);
			i--; size--;
		}
	}
	bulletTask.shrink_to_fit();

	//Bullet
	//サイズソートをのちに実装((弾が重なった時の描画をきれいに
	size = (int)bulletTask.size();
	for (int i = 0; i < size; i++) {
		bulletTask[i].Update();
		for (int j = 0; j < PLAYER_NUM; j++)//当たり判定
		{
			if (playerTask[j].GetInvTime() != 0) continue;
			if (bulletTask[i].IsHit(playerTask[j].GetX(), playerTask[j].GetY())) {
				LifeDown(j);
				playerTask[j].InvTimePlus();
			}
		}
		if (bulletTask[i].GetAlive() == false) {
			bulletTask.erase(bulletTask.begin() + i);
			i--; size--;
		}
	}
	bulletTask.shrink_to_fit();

	//System trueならゲームオーバー
	if (GameSystemUpdate() == true) SetScene(eGameOver);
}

void Game::Draw() {
	//BackGround
	BackGroundDraw();

	//debug
	//DrawFormatString(0, 0, GetColor(255, 255, 255),
	//	"Bullet.capacity():%d,Bullet.size():%d", bulletTask.capacity(), bulletTask.size());

	//Player
	for (int i = 0; i < PLAYER_NUM; i++) playerTask[i].Draw();

	//Bullet
	for (auto i : weaponTask) i.Draw();

	//Bullet
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);	//加算表示
	for (auto i : bulletTask) i.Draw();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//Enemy
	for (auto i : enemyTask) i.Draw();

	//System
	GameSystemDraw();
}

Game::~Game() {
	//Playerは、動的に確保していないのでdeleteしないでよい

	//Weapon
	vector<Weapon>().swap(weaponTask);

	//Enemy
	vector<Enemy>().swap(enemyTask);

	//Bullet
	vector<Bullet>().swap(bulletTask);
}