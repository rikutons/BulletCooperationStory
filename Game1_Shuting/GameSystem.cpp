#include <string>
#include <boost/format.hpp>
#include "dxlib.h"
#include "Common.h"

using namespace std;

namespace {
	int image[1]; //0.îwåi
	int gameTime;
	int score[PLAYER_NUM];
	int life[PLAYER_NUM];
	int F_Airstrike;
}

void GameSystemInitialize() {
	image[0] = LoadGraph("../material/picture/BackGround01.png");
	gameTime = 0;
	for (int i = 0; i < PLAYER_NUM; i++) {
		score[i] = 0;
		life[i] = 3;
	}

	//"Airstrike"  ÇÃ24pt,ëæÇ≥3ÇÃÉtÉHÉìÉgÇçÏê¨
	F_Airstrike = CreateFontToHandle("Airstrike", 22, 3, DX_FONTTYPE_ANTIALIASING_EDGE);
}

bool GameSystemUpdate() {
	gameTime++;
	if (life[0] < 0 && life[1] < 0) {
		return true;
	}
	return false;
}

void BackGroundDraw() {

	DrawRotaGraph(WINDOW_WIDE / 2, WINDOW_HEIGHT / 2 + 1, 1, 0, image[0], TRUE);

}

void GameSystemDraw() {
	string Output;

	for (int i = 0; i < PLAYER_NUM; i++) {
		Output = (boost::format("%dp Score:%07d Life:%d") %
			(i + 1) % score[i] % life[i]).str();
		DrawStringToHandle(FRAME_SIZE_X - 10 + i * 373, WINDOW_HEIGHT - FRAME_SIZE_Y + 2,
			Output.c_str(), GetColor(255, 255, 255), F_Airstrike);
	}
	//éûä‘
	Output = (boost::format("Time %02d:%02d") %
		(gameTime / 3600 % 3600) % (gameTime / 60 % 60)).str();
	DrawStringToHandle(WINDOW_WIDE / 2 - 90, 0,
		Output.c_str(), GetColor(255, 255, 255), F_Airstrike);
}

void LifeDown(int pNum) {
	life[pNum]--;
}

void AddScore(int pNum, int enemyScore) {
	score[pNum] += enemyScore;
}