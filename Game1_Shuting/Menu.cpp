#include "dxlib.h"
#include "Keybord.h"
#include "SceneMgr.h"
#include "Menu.h"

static int Menupoint;
static int TextTemplate;

static int SE_Select, SE_Decision;

MenuDeta menu[5];


Menu::Menu() {
	Menupoint = 0;
	TextTemplate = CreateFontToHandle(NULL, 10, -1, -1);
	menu[0] = { 100, 50,"メインモード" };
	menu[1] = { 100,150,"耐久モード" };
	menu[2] = { 100,250,"オプション" };
	menu[3] = { 100,350,"操作方法" };
	menu[4] = { 100,450,"終了" };
	SE_Select = LoadSoundMem("../material/se/選択音.ogg");
	SE_Decision=LoadSoundMem("../material/se/決定音.ogg");
}

void Menu::Update() {

	if (CursorCheck(KeybordGet(KEY_INPUT_DOWN))) { // 下キーが押されていたら下にカーソルを移動する
		Menupoint = (Menupoint + 1) % 5;
		PlaySoundMem(SE_Select, DX_PLAYTYPE_BACK);
	}
	if (CursorCheck(KeybordGet(KEY_INPUT_UP))) { // 上キーが押されていたら上にカーソルを移動する
		Menupoint = (Menupoint + 4) % 5;
		PlaySoundMem(SE_Select, DX_PLAYTYPE_BACK);
	}
	
	if (KeybordGet(KEY_INPUT_RETURN) == 1) {//エンターキーが押されたら
		PlaySoundMem(SE_Decision, DX_PLAYTYPE_BACK);
		
		if (Menupoint != 0 && Menupoint != 4) {
			strcpy_s(menu[Menupoint].MenuName, "未実装です。終了します。");
			Menupoint = 4;
		}
		
		eScene pointScene=static_cast<eScene>(Menupoint);	//int型のMenupointをeScene型のpointSceneに明示的に変換
		SetScene(pointScene);
	}
}

void Menu::Draw() {
	int white = GetColor(255, 255, 255);
	int red = GetColor(255, 0, 0);
	for (int i = 0; i < 5; i++) {
		if (Menupoint == i)
			DrawString(menu[i].x + 20, menu[i].y, menu[i].MenuName, red);
		else
			DrawString(menu[i].x, menu[i].y, menu[i].MenuName, white);
	}
}