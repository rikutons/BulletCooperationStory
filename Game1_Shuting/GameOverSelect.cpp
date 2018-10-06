#include "dxlib.h"
#include "SceneMgr.h"
#include "GameoverSelect.h"
#include "Common.h"
#include "MyDxlib.h"

//-----------------------------------------------------------------------------
//定数
//メニューの項目数
#define ITEM_NUM 2

//-----------------------------------------------------------------------------

namespace {
	int F_Meiryo70;
	int gameOverTextX;
	//メニューと構造が似ているので、メニューの構造体を使う
}

GameOverSelect::GameOverSelect()
	:BaseSelectScene(ITEM_NUM) {
	F_Meiryo70 = CreateFontToHandle(
		"メイリオ", 70, 3, DX_FONTTYPE_ANTIALIASING_EDGE);
	gameOverTextX = CalcCenterX(WINDOW_WIDE / 2, 70, "Game Over!!");

	int x[2];
	x[0] = CalcCenterX(WINDOW_WIDE / 2, 30, "もう一度プレイ");
	x[1] = CalcCenterX(WINDOW_WIDE / 2, 30, "メニューに戻る");
	SetItemData(0, { "もう一度プレイ" ,x[0],250 });
	SetItemData(1, { "メニューに戻る" ,x[1],300 });
}

void GameOverSelect::BackGroundDraw() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBox(0, 0, WINDOW_WIDE, WINDOW_HEIGHT, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawStringToHandle(gameOverTextX, 130,
		"Game Over!!", GetColor(255, 0, 0), F_Meiryo70);
}

void GameOverSelect::DicisionProcess() {
	switch (m_selectPoint) {
	case 0:
		SetScene(eGame);
		break;
	case 1:
		SetScene(eMenu);
		break;
	}
}