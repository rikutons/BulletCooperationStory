#include "dxlib.h"
#include "Keybord.h"
#include "SceneMgr.h"
#include "Game.h"
#include <math.h>
#include "Constant.h"

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

void CheckDeath() {
	int Cr;
	int R, G, B;
	//プレイヤーの座標を中心に、正六角形の頂点に城があれば、死亡判定を送る。getpixelは重いので、最低限の6回の判定にしている。
	//また、200×200の画像のため中心がint型では定まらないので、0.5を足したり引いたりして、中心ぴったりから判定するようにしている。
	for (int i = 0; i < 6; i++) {
		Cr = GetPixel(cx - 0.5 + cos(PI*i / 3) * 5, cy + 0.5 + sin(PI*i / 3) * 5);

		GetColor2(Cr, &R, &G, &B);
		if (R > 210 && G > 210 && B > 210) {
			SetGameover();
			break;
		}
	}
}