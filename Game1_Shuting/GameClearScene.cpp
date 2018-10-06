#include "dxlib.h"
#include "SceneMgr.h"
#include "GameClearScene.h"
#include "Common.h"
#include "Keybord.h"

//-----------------------------------------------------------------------------
//定数
//メニューの項目数
#define ITEM_NUM 2

//-----------------------------------------------------------------------------

namespace {
	int image[1];
}

GameClear::GameClear() {
	image[0]= LoadGraph("../material/picture/GameClear01.png");
}

void GameClear::Update() {
	if (KeybordGet(KEY_INPUT_RETURN) == 1) {//エンターキーが押されたら
		SetScene(eMenu);
	}
}

void GameClear::Draw() {
	DrawRotaGraphF(WINDOW_WIDE/2, WINDOW_HEIGHT/2, 1, 0, image[0], TRUE);
}