#include "dxlib.h"
#include "BaseScene.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "GameoverSelect.h"
#include "GameClearScene.h"
#include "SoundMgr.h"
#include "EffectMgr.h"

namespace {
	BaseScene *scene;
	eScene nowScene;
	bool isReady;
	int F_orangeJuice;
}

void SceneMgrInitialize() {
	nowScene = eMenu;
	isReady = false;
	F_orangeJuice = CreateFontToHandle(
		"orange juice", 24, 3, DX_FONTTYPE_ANTIALIASING_EDGE);
}

bool SceneMgr()
{
	//nowSceneに合わせて、sceneを切り替える
	if (nowScene != eNoneScene) {
		if (!isReady) {
			DrawStringToHandle(600, 560,
				"Now Loading...", GetColor(255, 255, 255), F_orangeJuice);
			isReady = true;
			return false;
		}
		else isReady = false;
		InitGraph();	//メモリの圧迫を防ぐために、画像をすべて開放しておく。
		delete scene;

		if (nowScene != eEnd) {
			EffectMgrInitialize();
		}
		switch (nowScene) {
		case eMenu:
			ChangeBGM(0);
			scene = new Menu();
			break;
		case eGame:
			scene = new Game();
			break;
		case eEnd:
			return true; //Endなら終了
		case eGameClear:
			scene = new GameClear();
			break;
		default:
			break;
		}
		nowScene = eNoneScene;
	}
	scene->Update();

	scene->Draw();

	return false;
}

void SetScene(eScene nextScene) {
	nowScene = nextScene;
};