#include "dxlib.h"
#include "Game.h"
#include "Menu.h"
#include "End.h"
#include "SceneMgr.h"
#include "BaseScene.h"

using namespace std;

BaseScene *Scene=new Menu();

eScene nowscene=eMenu;

bool SceneMgrUpdate()
{
	bool end=false;
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
			Scene = new End();
			end = true;
			break;
		default:
			break;
		}
		nowscene = eNoneScene;
	}
	Scene->Update();
	return end;
}

void SceneMgrDraw() {
	Scene->Draw();
}


void SetScene (eScene next){
	nowscene = next;
};