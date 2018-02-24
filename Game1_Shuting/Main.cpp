/*
制作 居田 陸人(コーディング,画像素材),田中 海士(コーディング,画像素材),吉木 旺助(コーディング,音楽,効果音)
dxlibを使ったシューティングゲーム。
*/

#include "DxLib.h"
#include "SceneMgr.h"
#include "Keybord.h"
#include "Common.h"	//定数を共有するヘッダファイル(ウインドウサイズ、円周率など)


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	//----------------------------------------------------------
	//初期化処理
	ChangeWindowMode(TRUE),  //フルスクリーンモードの解除
		SetDrawScreen(DX_SCREEN_BACK),  //裏画面処理の準備
		SetSysCommandOffFlag(1),  //altポーズを使えなくする
		SetMainWindowText("弾幕連携譚"),   //ウインドウ名の指定
		SetWindowIconID(101),  //アイコンを表示する
							   //ウインドウサイズ、色情報の指定
		SetGraphMode(WINDOW_WIDE, WINDOW_HEIGHT, 32);
	DxLib_Init();
	//----------------------------------------------------------

	bool isEnd = false;

	while (ScreenFlip() == 0 && ProcessMessage() == 0
		&& ClearDrawScreen() == 0 && KeybordUpdate() == 0 && isEnd == false) {

		isEnd = SceneMgr();

	}

	DxLib_End();
	return 0;
}