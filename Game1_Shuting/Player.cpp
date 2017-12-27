#include "dxlib.h"
#include "Keybord.h"
#include "SceneMgr.h"
#include "Common.h"

static int m_Image01,m_Image02;
static double m_Image2angle;

extern float cx,cy;

int PlayerSpeed;


void PlayerInitialize() {
	m_Image01 = LoadGraph("../material/picture/自機01.png");
	m_Image02 = LoadGraph("../material/picture/ファンネル01.png");
	cx = InitialX;
	cy = InitialY;
	m_Image2angle=0;
}

void PlayerUpdate() {
	if (KeybordGet(KEY_INPUT_LSHIFT)>0) {
		PlayerSpeed = 3;
	}
	else {
		PlayerSpeed = 5;
	}
	if (KeybordGet(KEY_INPUT_RIGHT) > 0 && cx < WindowWide-FrameSizeX) { // 右キーが押されていたら右に進む
		cx +=PlayerSpeed;
	}
	if (KeybordGet(KEY_INPUT_DOWN) > 0 && cy < WindowHeight-FrameSizeY) { // 下キーが押されていたら下に進む
		cy +=PlayerSpeed;
	}
	if (KeybordGet(KEY_INPUT_LEFT) > 0 && cx > 0+FrameSizeX) { // 左キーが押されていたら左に進む
		cx -=PlayerSpeed;
	}
	if (KeybordGet(KEY_INPUT_UP) > 0 && cy > 0+FrameSizeY) { // 上キーが押されていたら上に進む
		cy -=PlayerSpeed;
	}
	if (KeybordGet(KEY_INPUT_ESCAPE) > 0) {			//Escでメニューに戻る
		SetScene(eMenu);
	}
	m_Image2angle += 0.05;//ファンネルを回す
}

void PlayerDraw() {
	DrawRotaGraphF(cx, cy, 0.4, 0, m_Image01, TRUE);
	DrawRotaGraphF(cx, cy, 1, m_Image2angle, m_Image02, TRUE);
}