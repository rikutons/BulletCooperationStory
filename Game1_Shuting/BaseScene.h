#pragma once
#include "SceneMgr.h"


//シーンの基底クラス。
class BaseScene{

public:
	BaseScene(* changer);
	virtual ~BaseScene() {}
	virtual void Update() {}       
	virtual void Draw() {}         

};