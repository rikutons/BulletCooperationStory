#pragma once
#include"BaseScene.h"

enum eScene {
	eMenu=-1,
	eGame=0,
	eEnd=4,

	eNoneScene=5,	//eNoneはいろいろなところで使うので、eSceneのeNoneと分かるように、Scene、とつけておく。
};

bool SceneMgrUpdate();
void SceneMgrDraw();

void SetScene(eScene next);