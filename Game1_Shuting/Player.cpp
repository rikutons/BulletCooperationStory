#include "dxlib.h"
#include "Keybord.h"
#include "SceneMgr.h"
#include "Common.h"
#include "Player.h"



//0.自機 1.ファンネル
static int Image[2];

void PlayerInitialize() {
	Image[0] = LoadGraph("../material/picture/自機01.png");
	Image[1] = LoadGraph("../material/picture/ファンネル01.png");
}


Player::Player(float X, float Y, float Speed, double Angle) :
	Mover(X, Y, Speed, Angle), FunnelAngle(0) {}


void Player::Update() {
	if (KeybordGet(KEY_INPUT_LSHIFT) > 0)
		speed = 3;
	else
		speed = 5;

	//移動処理 枠外に出るような移動は行わない
	if (KeybordGet(KEY_INPUT_LEFT)	> 0 && x > 0			+ FRAME_SIZE_X)  // 左
		x -= speed;
	if (KeybordGet(KEY_INPUT_RIGHT)	> 0 && x < WINDOW_WIDE	- FRAME_SIZE_X)  // 右
		x += speed;
	if (KeybordGet(KEY_INPUT_UP)	> 0 && y > 0			+ FRAME_SIZE_Y)  // 上
		y -= speed;
	if (KeybordGet(KEY_INPUT_DOWN)	> 0 && y < WINDOW_HEIGHT - FRAME_SIZE_Y)  // 下
		y += speed;

	if (KeybordGet(KEY_INPUT_ESCAPE) > 0) 			//Escでメニューに戻る
		SetScene(eMenu);

	FunnelAngle += 0.05;//ファンネルを回す
}

void Player::Draw() {
	DrawRotaGraphF(x, y, 0.4, 0, Image[0], TRUE);
	DrawRotaGraphF(x, y, 1, FunnelAngle, Image[1], TRUE);
}
