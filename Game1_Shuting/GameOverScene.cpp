#include "dxlib.h"
#include "Keybord.h"
#include "SceneMgr.h"
#include "GameoverScene.h"
#include "MenuScene.h"
#include "Common.h"
#include "MyDxlib.h"
#include "SoundMgr.h"

//-----------------------------------------------------------------------------
//定数
//メニューの項目数
#define ITEM_NUM 2

//-----------------------------------------------------------------------------

namespace {
	int menuPoint;
	int F_Meiryo30;
	int F_Meiryo70;
	int gameOverTextX;
	//メニューと構造が似ているので、メニューの構造体を使う
	MenuDeta menu[ITEM_NUM];
}

GameOver::GameOver() {
	menuPoint = 0;

	//"メイリオ"  の70pt(30pt),太さ3のフォントを作成
	F_Meiryo30 = CreateFontToHandle(
		"メイリオ", 30, 3, DX_FONTTYPE_ANTIALIASING_EDGE);

	F_Meiryo70 = CreateFontToHandle(
		"メイリオ", 70, 3, DX_FONTTYPE_ANTIALIASING_EDGE);

	gameOverTextX = CalcCenterX(WINDOW_WIDE / 2, 70, "Game Over!!");

	menu[0] = { -1,250,"もう一度プレイ" };
	menu[1] = { -1,350,"メニューに戻る" };
	for (int i = 0; i < ITEM_NUM; i++) {
		menu[i].x = CalcCenterX(WINDOW_WIDE / 2, 30, menu[i].MenuName);
	}
}

void GameOver::Update() {
	// 下キーかSキーが押されていたら下にカーソルを移動する
	if (CursorCheck(KeybordGet(KEY_INPUT_DOWN)) ||
		CursorCheck(KeybordGet(KEY_INPUT_S))) {
		menuPoint = (menuPoint + 1) % ITEM_NUM;
		PlaySE(0);
	}

	// 上キーかWキーが押されていたら上にカーソルを移動する
	if (CursorCheck(KeybordGet(KEY_INPUT_UP)) ||
		CursorCheck(KeybordGet(KEY_INPUT_W))) {
		menuPoint = (menuPoint + 1) % ITEM_NUM;
		PlaySE(0);
	}

	if (KeybordGet(KEY_INPUT_RETURN) == 1) {//エンターキーが押されたら
		PlaySE(1);
		eScene pointScene = (menuPoint == 0 ? eGame : eMenu);
		SetScene(pointScene); //シーンを変更する
	}
}

void GameOver::Draw() {
	DrawStringToHandle(gameOverTextX, 130,
		"Game Over!!", GetColor(255, 0, 0), F_Meiryo70);

	int red = GetColor(255, 0, 0);
	int white = GetColor(255, 255, 255);
	for (int i = 0; i < ITEM_NUM; i++) {
		if (menuPoint == i)
			DrawStringToHandle(menu[i].x - 20, menu[i].y,
				menu[i].MenuName, red, F_Meiryo30);
		else
			DrawStringToHandle(menu[i].x, menu[i].y,
				menu[i].MenuName, white, F_Meiryo30);
	}
}