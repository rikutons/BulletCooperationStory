#pragma once
#include "BaseScene.h"

class Menu :public BaseScene {
public:
	Menu();
	void Update();
	void Draw();
};

void SetMenuMode(int nextMode);