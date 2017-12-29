#include "dxlib.h"
#include "Keybord.h"
#include "SceneMgr.h"
#include "Game.h"
#include <math.h>
#include "Common.h"

extern float cx, cy;

void Gameover() {
	int Gameover;
	WaitTimer(500);
	ScreenFlip(); 
	ClearDrawScreen();
	Gameover = CreateFontToHandle("メイリオ", 70, 3, DX_FONTTYPE_ANTIALIASING_EDGE);//"メイリオ"  の70pt,太さ3のフォントを作成
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && KeybordUpdate() == 0) {

		DrawStringToHandle(180, 130, "Game Over!!", GetColor(255, 0, 0), Gameover);
		DrawStringToHandle(180, 330, "Pless Enter.", GetColor(255, 255, 255), Gameover);
		if (KeybordGet(KEY_INPUT_RETURN) > 0) { // エンターキーが押されていたら
			break;
		}
	}
	SetScene(eGame);
}