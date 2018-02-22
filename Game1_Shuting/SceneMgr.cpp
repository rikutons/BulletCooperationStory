#include "dxlib.h"
#include "BaseScene.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "GameOverScene.h"

BaseScene *Scene;

eScene nowscene=eMenu;

bool SceneMgr()
{
	//nowsceneに合わせて、sceneを切り替える
	if (nowscene!=eNoneScene) {
		InitGraph();	//メモリの圧迫を防ぐために、画像をすべて開放しておく。
		WaitTimer(500); //シーンが変わったとき、0.5秒止めることで、シーンが一瞬で変わってプレイヤーが混乱することを防ぐ。
		delete Scene;
		switch (nowscene) {
		case eMenu:
			Scene = new Menu();
			break;
		case eGame:
			Scene = new Game();
			break;
		case eEnd:
			return true; //Endなら終了
			break;
		case eGameOver:
			Scene = new GameOver();
			break;
		default:
			break;
		}
		nowscene = eNoneScene;
	}
	Scene->Update();
	Scene->Draw();
	return false;
}

void SetScene (eScene nextScene){
	nowscene = nextScene;
};