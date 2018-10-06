/*
弾幕連携譚 v1.0
[18/4/01追記]
制作者,参考にしたサイト,工夫した点などの情報は,
プロジェクトファイルより一つ上の階層の,README.txtに
書いているので,そちらをご覧ください.
*/

#include "DxLib.h"
#include "Keybord.h"
#include "Common.h"	//定数を共有するヘッダファイル(ウインドウサイズ,円周率など)
#include "EffectMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"
#include "BaseSelectScene.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	//----------------------------------------------------------
	//DXlibの初期化処理
	ChangeWindowMode(TRUE),  //フルスクリーンモードの解除
		SetDrawScreen(DX_SCREEN_BACK),  //裏画面処理の準備
		SetSysCommandOffFlag(1),  //altポーズを使えなくする
		SetMainWindowText("弾幕連携譚"),   //ウインドウ名の指定
		SetWindowIconID(101),  //アイコンを表示する
							   //ウインドウサイズ,色情報の指定
		SetGraphMode(WINDOW_WIDE, WINDOW_HEIGHT, 32);
	DxLib_Init();
	//----------------------------------------------------------
	
	SceneMgrInitialize();
	SoundMgrInitialize();
	BaseSelectSceneInitialize();

	bool isEnd = false;

	while (ScreenFlip() == 0 && ProcessMessage() == 0
		&& ClearDrawScreen() == 0 && KeybordUpdate() == 0 && isEnd == false) {

		isEnd = SceneMgr();

	}
	
	DxLib_End();
	return 0;
}