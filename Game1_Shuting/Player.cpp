#include "dxlib.h"
#include "Keybord.h"
#include "SceneMgr.h"
#include "Common.h"
#include "Player.h"
#include "Weapon.h"
#include <vector>



//0.自機1 1.自機2 2.ファンネル1 3.ファンネル2
static int Image[4];

//Weaponを発射する間隔を制御する
int Wtime;

void PlayerInitialize() {
	Image[0] = LoadGraph("../material/picture/Player01.png");
	Image[1] = LoadGraph("../material/picture/Player02.png");
	Image[2] = LoadGraph("../material/picture/Funnel01.png");
	Image[3] = LoadGraph("../material/picture/Funnel02.png");
	Wtime = 0;
}

//GameTaskで、配列で宣言する際専用の引数なしのコンストラクタ
Player::Player() : Mover(0, 0, 0, 0) {}

Player::Player(float X, float Y,int PlayerNum) :
	Mover(X, Y, 0, 0), FunnelAngle(0), playerNum(PlayerNum) {}


void Player::Update() {
	//keyP[プレイヤーの番号][キーコンフィグ] = {左 右 上 下 低速}
	int keyP[2][5] = { { KEY_INPUT_A , KEY_INPUT_D , KEY_INPUT_W ,
							KEY_INPUT_S ,KEY_INPUT_LSHIFT },
						{ KEY_INPUT_LEFT , KEY_INPUT_RIGHT , KEY_INPUT_UP ,
							KEY_INPUT_DOWN ,KEY_INPUT_RSHIFT } };


	if (KeybordGet(keyP[playerNum][4]) > 0) //低速
		speed = 3;
	else
		speed = 5;
	//斜め移動時の処理のために、一度別の変数を介する
	float xplus = 0, yplus = 0;
	//移動処理 枠外に出るような移動は行わない
	if (KeybordGet(keyP[playerNum][0]) > 0 &&
		x > (playerNum == 0 ? FRAME_SIZE_X : POSX_LIMMIT_P2) + PLAYER_SIZE) // 左
		xplus -= speed;
	if (KeybordGet(keyP[playerNum][1]) > 0 &&
		x < (playerNum == 0 ? POSX_LIMMIT_P1 : WINDOW_WIDE - FRAME_SIZE_X) - PLAYER_SIZE)   // 右
		xplus += speed;
	if (KeybordGet(keyP[playerNum][2]) > 0 && y > FRAME_SIZE_Y + PLAYER_SIZE)  // 上
		yplus -= speed;
	if (KeybordGet(keyP[playerNum][3]) > 0 && y < WINDOW_HEIGHT - FRAME_SIZE_Y - PLAYER_SIZE)  // 下
		yplus += speed;
	//xとy方向両方に移動するとき、斜め移動の違和感をなくすため少し減速する
	//値は1/ルート2の近似値
	if (xplus != 0 && yplus != 0) {
		xplus *= 0.707f;
		yplus *= 0.707f;
	}
	x += xplus;
	y += yplus;

	if (KeybordGet(KEY_INPUT_ESCAPE) > 0) 	//Escでメニューに戻る
		SetScene(eMenu);

	FunnelAngle += 0.05;//ファンネルを回す
}

void Player::Draw() {
	DrawRotaGraphF(x, y, 0.4, 0, Image[playerNum], TRUE);
	DrawRotaGraphF(x, y, 1, FunnelAngle, Image[playerNum+2], TRUE);
}

void Player::WeaponPlus(std::vector<Weapon> &weapon) {
	//2pの時だけカウントする
	Wtime += playerNum;

	if (Wtime % 10 == 0) {
		weapon.push_back(Weapon(x, y, playerNum));
	}
}