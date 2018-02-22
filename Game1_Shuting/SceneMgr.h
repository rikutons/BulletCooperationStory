#pragma once

enum eScene {
	eMenu = -1,
	eGame = 0,
	eEnd = 4,

	eNoneScene = 5,	//eNoneはいろいろなところで使うので、eSceneのeNoneと分かるように、Scene、とつけておく。
	eGameOver = 6,
};

bool SceneMgr();

void SetScene(eScene next);