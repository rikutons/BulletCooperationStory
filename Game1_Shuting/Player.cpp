#include "dxlib.h"
#include "Keybord.h"
#include "SceneMgr.h"
#include "Common.h"
#include "Player.h"
#include "Weapon.h"
#include <vector>
#include "SoundMgr.h"
#include "GameSystem.h"

//-----------------------------------------------------------------------------
//定数
//無敵時間のフレーム数
#define INV_TIME 180

//無敵時間の点滅感覚
#define FRASH_INTERVAL 30

//通常移動時の武器の速度
#define WEAPON_SPEED 10.0f

//-----------------------------------------------------------------------------

namespace {
	//0.自機1 1.自機2 2.ファンネル1 3.ファンネル2
	int image[4];
	//Weaponを発射する間隔を制御する
}


void PlayerInitialize() {
	image[0] = LoadGraph("../material/picture/Player01.png");
	image[1] = LoadGraph("../material/picture/Player02.png");
	image[2] = LoadGraph("../material/picture/Funnel01.png");
	image[3] = LoadGraph("../material/picture/Funnel02.png");
}

//GameTaskで、配列で宣言する際専用の引数なしのコンストラクタ
Player::Player() : Mover(0, 0, 0, 0) {}

Player::Player(float X, float Y, int PlayerNum) :
	Mover(X, Y, 0, 0), m_funnelAngle(0),
	m_playerNum(PlayerNum), m_invincibleTime(0) {}


void Player::Update() {
	//keyP[プレイヤーの番号][キーコンフィグ] = {左 右 上 下 低速}
	int keyP[2][5] = {
		{ KEY_INPUT_A , KEY_INPUT_D , KEY_INPUT_W ,
							KEY_INPUT_S ,KEY_INPUT_LSHIFT },
		{ KEY_INPUT_LEFT , KEY_INPUT_RIGHT , KEY_INPUT_UP ,
							KEY_INPUT_DOWN ,KEY_INPUT_RSHIFT }
	};

	if (KeybordGet(keyP[m_playerNum][4]) > 0) //低速
		m_speed = 2;
	//m_speed = 3;
	else
		m_speed = 5;
	//斜め移動時の処理のために、一度別の変数を介する
	float xplus = 0, yplus = 0;
	//移動処理 枠外に出るような移動は行わない
	bool isChangeBackGround = GetChangeBackGround();
	if (KeybordGet(keyP[m_playerNum][0]) > 0 &&
		m_x > (m_playerNum == 0 || isChangeBackGround ?
			FRAME_SIZE_X : POSX_LIMMIT_P2) + PLAYER_SIZE) {
		xplus -= m_speed; // 左
	}
	if (KeybordGet(keyP[m_playerNum][1]) > 0 &&
		m_x < (m_playerNum == 1 || isChangeBackGround ?
			WINDOW_WIDE - FRAME_SIZE_X : POSX_LIMMIT_P1) - PLAYER_SIZE) {
		xplus += m_speed; // 右
	}
	if (KeybordGet(keyP[m_playerNum][2]) > 0 &&
		m_y > FRAME_SIZE_Y + PLAYER_SIZE) {
		yplus -= m_speed; // 上
	}
	if (KeybordGet(keyP[m_playerNum][3]) > 0 &&
		m_y < WINDOW_HEIGHT - FRAME_SIZE_Y - PLAYER_SIZE) {
		yplus += m_speed; // 下
	}
	//xとy方向両方に移動するとき、斜め移動の違和感をなくすため少し減速する
	//値は1/ルート2の近似値
	if (xplus != 0 && yplus != 0) {
		xplus *= 0.707f;
		yplus *= 0.707f;
	}
	m_x += xplus;
	m_y += yplus;



	m_funnelAngle += 0.05;//ファンネルを回す

	if (m_invincibleTime > 0) m_invincibleTime--;

	if (m_invincibleTime > 0 &&
		m_invincibleTime%FRASH_INTERVAL < FRASH_INTERVAL / 2) {
		m_isDraw = false;
	}
	else m_isDraw = true;
}

void Player::Draw() {
	if (m_isDraw&&m_alive) {
		DrawRotaGraphF(
			m_x, m_y, 1, 0, image[m_playerNum], TRUE);
		DrawRotaGraphF(
			m_x, m_y, 1, m_funnelAngle, image[m_playerNum + 2], TRUE);
	}
}

//武器を発射するメソッド
void Player::WeaponPlus(std::vector<Weapon> &weapon) {
	float speed = (m_speed == 5 ? WEAPON_SPEED : WEAPON_SPEED * 0.8f);
	int time = GetGameTime();
	if (time % 10 == 0) {
		weapon.push_back(Weapon(m_x, m_y, m_playerNum, speed, 0));
	}
	if (time % 25 == 0) {
		double angle = (m_speed == 5 ? 30.0 : 10.0);
		weapon.push_back(Weapon(m_x, m_y, m_playerNum, speed, angle));
		weapon.push_back(Weapon(m_x, m_y, m_playerNum, speed, -angle));
	}
	//2pの時だけカウントする
	time += m_playerNum;
}

//被弾時の無敵時間を追加するメソッド
void Player::InvTimePlus() {
	m_invincibleTime = INV_TIME;
	PlaySE(3);  //被弾ついでに爆発音
}