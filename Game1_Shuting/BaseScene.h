#pragma once
#include "SceneMgr.h"


//シーンの基底クラス。
class BaseScene{

protected:
	int mImageHandle;                //画像ハンドル格納用変数

public:
	BaseScene(* changer);
	virtual ~BaseScene() {}
	virtual void Initialize() {}   
	virtual void Finalize() {}     
	virtual void Update() {}       
	virtual void Draw() {}         

};