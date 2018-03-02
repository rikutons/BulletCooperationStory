#include "Dxlib.h"
#include "Keybord.h"
#include "SceneMgr.h"
#include "MenuScene.h"
#include "SoundMgr.h"

//---------------------------------------------------------
//定数
//メニューの項目数
#define ITEM_NUM 5

//---------------------------------------------------------

namespace {
	int menuPoint;
	int F_Meiryo;
	int MV_BackGround;
	MenuDeta menu[ITEM_NUM];
}

Menu::Menu() {
	menuPoint = 0;
	
	MV_BackGround = LoadGraph("../material/picture/menuBackGround.mp4");
	
	F_Meiryo = CreateFontToHandle("メイリオ", 30, 3, DX_FONTTYPE_ANTIALIASING_EDGE);
	menu[0] = { 100, 70,"メインモード" };
	menu[1] = { 100,170,"耐久モード" };
	menu[2] = { 100,270,"オプション" };
	menu[3] = { 100,370,"操作方法" };
	menu[4] = { 100,470,"終了" };
}

void Menu::Update() {

	//背景動画の再生が停止(=終了)していたら、最初のフレームに戻す
	if (GetMovieStateToGraph(MV_BackGround) == 0) {
		SeekMovieToGraph(MV_BackGround, 0);
	}

	// 下キーかSキーが押されていたら下にカーソルを移動する
	if (CursorCheck(KeybordGet(KEY_INPUT_DOWN)) ||
		CursorCheck(KeybordGet(KEY_INPUT_S))) { 
		menuPoint = (menuPoint + 1) % ITEM_NUM;
		PlaySE(0);
	}

	// 上キーかWキーが押されていたら上にカーソルを移動する
	if (CursorCheck(KeybordGet(KEY_INPUT_UP)) ||
		CursorCheck(KeybordGet(KEY_INPUT_W))) { 
		menuPoint = (menuPoint + 4) % ITEM_NUM;
		PlaySE(0);
	}

	if (KeybordGet(KEY_INPUT_RETURN) == 1) {//エンターキーが押されたら
		PlaySE(1);
		if (menuPoint != 0 && menuPoint != 4) {
			strcpy_s(menu[menuPoint].MenuName, "未実装です。終了します。");
			menuPoint = 4;
		}
		//int型のmenuPointをeScene型のpointSceneに明示的に変換
		eScene pointScene = static_cast<eScene>(menuPoint);
		SetScene(pointScene);
	}
}

void Menu::Draw() {
	PlayMovieToGraph(MV_BackGround);
	DrawGraph(0, 0, MV_BackGround, FALSE);
	int white = GetColor(205, 205, 205);
	int red = GetColor(255, 0, 0);
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);	//加算表示
	for (int i = 0; i < ITEM_NUM; i++) {
		if (menuPoint == i)
			DrawStringToHandle(menu[i].x + 20, menu[i].y,
				menu[i].MenuName, red, F_Meiryo);
		else
			DrawStringToHandle(menu[i].x, menu[i].y,
				menu[i].MenuName, white, F_Meiryo);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}