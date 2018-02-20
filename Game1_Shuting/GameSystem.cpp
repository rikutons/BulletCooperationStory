#include <string>
#include <boost/format.hpp>
#include "dxlib.h"
#include "Common.h"

using namespace std;
static int Image[1]; //0.îwåi
int GameTime;
static int Score[PLAYER_NUM];
static int Life[PLAYER_NUM];
int F_Airstrike;

void GameSystemInitialize() {
	Image[0] = LoadGraph("../material/picture/BackGround01.png");
	GameTime = 0;
	for (int i = 0; i < PLAYER_NUM; i++) {
		Score[i] = 0;
		Life[i] = 3;
	}

	//"Airstrike"  ÇÃ24pt,ëæÇ≥3ÇÃÉtÉHÉìÉgÇçÏê¨
	F_Airstrike = CreateFontToHandle("Airstrike", 22, 3, DX_FONTTYPE_ANTIALIASING_EDGE);
}

void GameSystemUpdate() {
	GameTime++;
}

void BackGroundDraw() {

	DrawRotaGraph(WINDOW_WIDE / 2, WINDOW_HEIGHT / 2 + 1, 1, 0, Image[0], TRUE);

}

void GameSystemDraw() {
	string Output;

	for (int i = 0; i < PLAYER_NUM; i++) {
		Output = (boost::format("%dp Score:%07d Life:%d") %
			(i + 1) % Score[i] % Life[i]).str();
		DrawStringToHandle(FRAME_SIZE_X - 10 + i * 373, WINDOW_HEIGHT - FRAME_SIZE_Y+2,
			Output.c_str(), GetColor(255, 255, 255), F_Airstrike);
	}
	//éûä‘
	Output = (boost::format("Time %02d:%02d") %
		(GameTime / 3600 % 3600) % (GameTime / 60 % 60)).str();
	DrawStringToHandle(WINDOW_WIDE / 2 - 90, 0,
		Output.c_str(), GetColor(255, 255, 255), F_Airstrike);
}