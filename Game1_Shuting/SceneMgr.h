#pragma once
#include"BaseScene.h"

enum eScene {
	eMenu=-1,
	eGame=0,
	eEnd=4,

	eNoneScene=5,	//eNoneはいろいろなところで使うので、eSceneのeNoneと分かるように、Scene、とつけておく。
};
void SceneMgrInitialize();
void SceneMgrUpdate();
void SceneMgrDraw();
void SceneMgrFinalize();

void SetScene(eScene a);