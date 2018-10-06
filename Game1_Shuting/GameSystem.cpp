#include <string>
#include <boost/format.hpp>
#include "dxlib.h"
#include "Common.h"
#include "Keybord.h"
#include "EffectMgr.h"
#include "SoundMgr.h"

//-----------------------------------------------------------------------------
//定数
//敵ごとのスコア
const int EScore[] = { 1000,3000,3000,3000,15000,15000,15000,100000 };

//-----------------------------------------------------------------------------

using namespace std;

namespace {
	int image[2];
	int MV_BackGroundChange;
	bool isChangeBackGround;
	int gameTime;
	int score[PLAYER_NUM];
	int life;
	int F_Airstrike;
	bool isPlayMovie;
	bool isEscapeSelect;
}

void GameSystemInitialize() {
	image[0] = LoadGraph("../material/picture/BackGround01.png");
	image[1] = LoadGraph("../material/picture/BackGround02.png");
	MV_BackGroundChange = LoadGraph(
		"../material/movie/backGroundChange.mp4");
	isChangeBackGround = false;
	gameTime = 0;
	life = 10;
	for (int i = 0; i < PLAYER_NUM; i++) {
		score[i] = 0;
	}
	//"Airstrike"  の24pt,太さ3のフォントを作成
	F_Airstrike = CreateFontToHandle(
		"Airstrike", 22, 3, DX_FONTTYPE_ANTIALIASING_EDGE);
	isPlayMovie = true;
	isEscapeSelect = false;
}

void GameSystemUpdate() {
	gameTime++;
	if (KeybordGet(KEY_INPUT_ESCAPE) > 0) 	//Escでメニューに戻る
		isEscapeSelect = true;
}

void BackGroundDraw() {
	int type = (isChangeBackGround ? 1 : 0);
	DrawRotaGraph(
		WINDOW_WIDE / 2, WINDOW_HEIGHT / 2, 1, 0, image[type], TRUE);
	if (isChangeBackGround&&isPlayMovie) {
		PlayMovieToGraph(MV_BackGroundChange);
		DrawGraph(0, 0, MV_BackGroundChange, FALSE);
		//背景動画の再生が停止(=終了)していたら、動画の描画をやめる
		if (GetMovieStateToGraph(MV_BackGroundChange) == 0) {
			DeleteGraph(MV_BackGroundChange);
			isPlayMovie = false;
		}
	}
}

void GameSystemDraw() {
	string Output;

	for (int i = 0; i < PLAYER_NUM; i++) {
		Output = (boost::format("%dp Score:%07d") %
			(i + 1) % score[i]).str();
		DrawStringToHandle(
			FRAME_SIZE_X + 20 + i * 393, WINDOW_HEIGHT - FRAME_SIZE_Y + 2,
			Output.c_str(), GetColor(255, 255, 255), F_Airstrike);
	}
	Output = (boost::format("Life:%d") % life).str();
	DrawStringToHandle(
		350, WINDOW_HEIGHT - FRAME_SIZE_Y + 2,
		Output.c_str(), GetColor(255, 155, 155), F_Airstrike);
	//時間
	Output = (boost::format("Time %02d:%02d") %
		(gameTime / 3600 % 3600) % (gameTime / 60 % 60)).str();
	DrawStringToHandle(WINDOW_WIDE / 2 - 90, 0,
		Output.c_str(), GetColor(255, 255, 255), F_Airstrike);
}

void LifeDown() {
	life--;
}

void LifePlus() {
	life += 2;
	PlayEffect(WINDOW_WIDE / 2, WINDOW_HEIGHT - FRAME_SIZE_Y / 2, 4);
	PlaySE(5);
}

void AddScore(int pNum, int enemyType) {
	score[pNum] += EScore[enemyType];
}

void ChangeBackGround() {
	isChangeBackGround = true;
}

bool GetChangeBackGround() {
	return isChangeBackGround;
}

int GetGameTime() {
	return gameTime;
}

bool GetIsGameOver() {
	return life == 0;
}

bool GetIsSelectEscape() {
	return isEscapeSelect;
}

void SetIsSelectEscape(bool IsEscapeSelect) {
	isEscapeSelect = IsEscapeSelect;
}