#include <string>
#include "dxlib.h"
#include "Game.h"
#include "Menu.h"
#include "End.h"
#include "SceneMgr.h"
#include "BaseScene.h"

using namespace std;

BaseScene *Scene=new Menu;

eScene nowscene;

void SceneMgrInitialize() {
	nowscene = eMenu;
	Scene->Initialize();
}

bool SceneMgrUpdate()
{
	bool end=false;
	if (nowscene!=eNoneScene) {
		InitGraph();	//メモリの圧迫を防ぐために、画像をすべて開放しておく。
		Scene->Finalize();
		WaitTimer(500);//シーンが変わったとき、0.5秒止めることで、シーンが一瞬で変わってプレイヤーが混乱することを防ぐ。
		delete Scene;
		switch (nowscene) {
		case eMenu:
			Scene = new Menu();
			break;
		case eGame:
			Scene = new Game();
			break;
		case eEnd:
			Scene = new End();
			end = true;
			break;
		default:
			break;
		}
		Scene->Initialize();
		nowscene = eNoneScene;
	}
	Scene->Update();
	return end;
}

void SceneMgrDraw() {
	Scene->Draw();
}

void SceneMgrFinalize() {
	Scene->Finalize();
}


void SetScene (eScene a){
	nowscene = a;
};