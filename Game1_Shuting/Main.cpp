/* 
@yukkuriesu
dxlibを使ったシューティングゲーム
モジュール内の静的な変数名は原則m_を付けること、
Initialize(初期化)、Update(計算、更新)、Draw(描画)、Get(中身の取得)等の明確な分離などに気を付けたい。
keybordの部分だけは完全にコピーペーストだが、他は考え方は参考にしたものの、基本的に応用させつつ自分で書いていることを明記しておく。
*/

#include "DxLib.h"
#include "Game.h"
#include "SceneMgr.h"
#include "Keybord.h"
#include "Common.h"	//定数を共有するヘッダファイル(ウインドウサイズ、円周率など)


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
				//左から フルスクリーンモードの解除,Dxlibの初期化,裏画面処理の準備,ウインドウ名の指定
	ChangeWindowMode(TRUE),  SetDrawScreen(DX_SCREEN_BACK),SetMainWindowText("弾幕連携譚");

	//altポーズを使えなくする
	SetSysCommandOffFlag(1);
	//アイコンを表示する
	SetWindowIconID(101);
	SetGraphMode(WINDOW_WIDE, WINDOW_HEIGHT, 32);
	DxLib_Init();


	bool EndFlag = false;

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && KeybordUpdate() == 0 && !EndFlag) {
		EndFlag=SceneMgrUpdate();
		SceneMgrDraw();
	}


	DxLib_End();
	return 0;
}