#pragma once
#include "BaseScene.h"

class MenuDeta {
public:
	int x;
	int y;
	char MenuName[30];
};
class Menu:public BaseScene {
	void Initialize();
	void Update();
	void Draw();
};