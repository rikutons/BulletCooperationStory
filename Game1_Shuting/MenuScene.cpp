#include "dxlib.h"
#include "Keybord.h"
#include "SceneMgr.h"
#include "MenuScene.h"

//-----------------------------------------------------
//定数
//メニューの項目数
#define ITEM_NUM 5

//----------------------------------------------------

static int F_Meiryo;
static int Menupoint;
static int SE_Select, SE_Decision;
static int Movie_BackGround;

static MenuDeta menu[ITEM_NUM];


Menu::Menu() {
	F_Meiryo = CreateFontToHandle("メイリオ", 30, 3, DX_FONTTYPE_ANTIALIASING_EDGE);
	Menupoint = 0;
	menu[0] = { 100, 70,"メインモード" };
	menu[1] = { 100,170,"耐久モード" };
	menu[2] = { 100,270,"オプション" };
	menu[3] = { 100,370,"操作方法" };
	menu[4] = { 100,470,"終了" };
	Movie_BackGround = LoadGraph("../material/picture/menuBackGround.mp4");
	SE_Select = LoadSoundMem("../material/se/選択音.ogg");
	SE_Decision = LoadSoundMem("../material/se/決定音.ogg");
}

void Menu::Update() {

	//背景動画の再生が停止(=終了)していたら、最初のフレームに戻す
	if (GetMovieStateToGraph(Movie_BackGround) == 0) {
		SeekMovieToGraph(Movie_BackGround, 0);
	}

	if (CursorCheck(KeybordGet(KEY_INPUT_DOWN)) ||
		CursorCheck(KeybordGet(KEY_INPUT_S))) { // 下キーかSキーが押されていたら下にカーソルを移動する
		Menupoint = (Menupoint + 1) % ITEM_NUM;
		PlaySoundMem(SE_Select, DX_PLAYTYPE_BACK);
	}
	if (CursorCheck(KeybordGet(KEY_INPUT_UP)) ||
		CursorCheck(KeybordGet(KEY_INPUT_W))) { // 上キーかWキーが押されていたら上にカーソルを移動する
		Menupoint = (Menupoint + 4) % ITEM_NUM;
		PlaySoundMem(SE_Select, DX_PLAYTYPE_BACK);
	}

	if (KeybordGet(KEY_INPUT_RETURN) == 1) {//エンターキーが押されたら
		PlaySoundMem(SE_Decision, DX_PLAYTYPE_BACK);

		if (Menupoint != 0 && Menupoint != 4) {
			strcpy_s(menu[Menupoint].MenuName, "未実装です。終了します。");
			Menupoint = 4;
		}

		eScene pointScene = static_cast<eScene>(Menupoint);	//int型のMenupointをeScene型のpointSceneに明示的に変換
		SetScene(pointScene);
	}
}

void Menu::Draw() {
	PlayMovieToGraph(Movie_BackGround);
	DrawGraph(0, 0, Movie_BackGround, FALSE);
	int white = GetColor(205, 205, 205);
	int red = GetColor(255, 0, 0);
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);	//加算表示
	for (int i = 0; i < ITEM_NUM; i++) {
		if (Menupoint == i)
			DrawStringToHandle(menu[i].x + 20, menu[i].y,
				menu[i].MenuName, red, F_Meiryo);
		else
			DrawStringToHandle(menu[i].x, menu[i].y,
				menu[i].MenuName, white, F_Meiryo);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}