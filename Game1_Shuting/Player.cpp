#include "dxlib.h"
#include "Keybord.h"
#include "SceneMgr.h"
#include "Common.h"
#include "Player.h"
#include "Weapon.h"
#include <vector>

//-----------------------------------------------------------------------------
//定数
//無敵時間のフレーム数
#define INV_TIME 180

//無敵時間の点滅感覚
#define FRASH_INTERVAL 30

//-----------------------------------------------------------------------------

namespace {
	//0.自機1 1.自機2 2.ファンネル1 3.ファンネル2
	int image[4];
}

//Weaponを発射する間隔を制御する
int shotCount;

void PlayerInitialize() {
	image[0] = LoadGraph("../material/picture/Player01.png");
	image[1] = LoadGraph("../material/picture/Player02.png");
	image[2] = LoadGraph("../material/picture/Funnel01.png");
	image[3] = LoadGraph("../material/picture/Funnel02.png");
	shotCount = 0;
}

//GameTaskで、配列で宣言する際専用の引数なしのコンストラクタ
Player::Player() : Mover(0, 0, 0, 0) {}

Player::Player(float X, float Y, int PlayerNum) :
	Mover(X, Y, 0, 0), m_funnelAngle(0), m_playerNum(PlayerNum), m_invincibleTime(0) {}


void Player::Update() {
	//keyP[プレイヤーの番号][キーコンフィグ] = {左 右 上 下 低速}
	int keyP[2][5] = { { KEY_INPUT_A , KEY_INPUT_D , KEY_INPUT_W ,
							KEY_INPUT_S ,KEY_INPUT_LSHIFT },
						{ KEY_INPUT_LEFT , KEY_INPUT_RIGHT , KEY_INPUT_UP ,
							KEY_INPUT_DOWN ,KEY_INPUT_RSHIFT } };


	if (KeybordGet(keyP[m_playerNum][4]) > 0) //低速
		m_speed = 3;
	else
		m_speed = 5;
	//斜め移動時の処理のために、一度別の変数を介する
	float xplus = 0, yplus = 0;
	//移動処理 枠外に出るような移動は行わない
	if (KeybordGet(keyP[m_playerNum][0]) > 0 &&
		m_x > (m_playerNum == 0 ? FRAME_SIZE_X : POSX_LIMMIT_P2) + PLAYER_SIZE) // 左
		xplus -= m_speed;
	if (KeybordGet(keyP[m_playerNum][1]) > 0 &&
		m_x < (m_playerNum == 0 ? POSX_LIMMIT_P1 : WINDOW_WIDE - FRAME_SIZE_X) - PLAYER_SIZE)   // 右
		xplus += m_speed;
	if (KeybordGet(keyP[m_playerNum][2]) > 0 && m_y > FRAME_SIZE_Y + PLAYER_SIZE)  // 上
		yplus -= m_speed;
	if (KeybordGet(keyP[m_playerNum][3]) > 0 && m_y < WINDOW_HEIGHT - FRAME_SIZE_Y - PLAYER_SIZE)  // 下
		yplus += m_speed;
	//xとy方向両方に移動するとき、斜め移動の違和感をなくすため少し減速する
	//値は1/ルート2の近似値
	if (xplus != 0 && yplus != 0) {
		xplus *= 0.707f;
		yplus *= 0.707f;
	}
	m_x += xplus;
	m_y += yplus;

	if (KeybordGet(KEY_INPUT_ESCAPE) > 0) 	//Escでメニューに戻る
		SetScene(eMenu);

	m_funnelAngle += 0.05;//ファンネルを回す

	if (m_invincibleTime > 0) m_invincibleTime--;

	if (m_invincibleTime > 0 && m_invincibleTime%FRASH_INTERVAL < FRASH_INTERVAL / 2) {
		m_isDraw = false;
	}
	else m_isDraw = true;
}

void Player::Draw() {
	if (m_isDraw) {
		DrawRotaGraphF(m_x, m_y, 0.4, 0, image[m_playerNum], TRUE);
		DrawRotaGraphF(m_x, m_y, 1, m_funnelAngle, image[m_playerNum + 2], TRUE);
	}
}

//武器を発射するメソッド
void Player::WeaponPlus(std::vector<Weapon> &weapon) {
	//2pの時だけカウントする
	shotCount += m_playerNum;

	if (shotCount % 10 == 0) {
		weapon.push_back(Weapon(m_x, m_y, m_playerNum));
	}
}

//被弾時の無敵時間を追加するメソッド
void Player::InvTimePlus() {
	m_invincibleTime = INV_TIME;
}