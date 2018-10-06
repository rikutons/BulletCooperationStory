#pragma once

enum eScene {
	eMenu = -1,
	eGame = 0,
	eEnd = 4,

	eNoneScene = 5,	//eNoneはいろいろなところで使うので、eSceneのeNoneと分かるように、Scene、とつけておく。
	eGameClear = 6,
};

void SceneMgrInitialize();
bool SceneMgr();

void SetScene(eScene);