#include <string>
#include "dxlib.h"
#include "Common.h"

static int Image[1];
int GameTime;
static int score;
int F_Meiryo;

void GameSystemInitialize(){
	Image[0] = LoadGraph("../material/picture/背景01.png");
	GameTime = 0;
	score = 0;
	F_Meiryo = CreateFontToHandle("メイリオ", 70, 3, DX_FONTTYPE_ANTIALIASING_EDGE);//"メイリオ"  の70pt,太さ3のフォントを作成
	
}

void GameSystemUpdate() {
	GameTime++;
}

void GameSystemDraw(){
	DrawRotaGraph(WINDOW_WIDE/2, WINDOW_HEIGHT/2, 1, 0, Image[0], TRUE);
	//DrawStringToHandle(180, 130, , GetColor(255, 0, 0), F_Meiryo); スコアと時間の表示 とりあえずあきらめた
	//DrawStringToHandle(210, 130, "Time=%d:%d",GameTime/3600,GameTime/60, GetColor(255, 0, 0), F_Meiryo);
}