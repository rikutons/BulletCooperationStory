#pragma once
#include "BaseScene.h"
class Game:public BaseScene {
	void Initialize();
	void Update();
	void Draw();
	void Finalize();
};
void SetGameover();