#include "dxlib.h"
#include "BaseScene.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "GameOverScene.h"

BaseScene *scene;

eScene nowScene=eMenu;

bool SceneMgr()
{
	//nowSceneに合わせて、sceneを切り替える
	if (nowScene!=eNoneScene) {
		InitGraph();	//メモリの圧迫を防ぐために、画像をすべて開放しておく。
		WaitTimer(500); //シーンが変わったとき、0.5秒止めることで、シーンが一瞬で変わってプレイヤーが混乱することを防ぐ。
		delete scene;
		switch (nowScene) {
		case eMenu:
			scene = new Menu();
			break;
		case eGame:
			scene = new Game();
			break;
		case eEnd:
			return true; //Endなら終了
			break;
		case eGameOver:
			scene = new GameOver();
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

void SetScene (eScene nextScene){
	nowScene = nextScene;
};