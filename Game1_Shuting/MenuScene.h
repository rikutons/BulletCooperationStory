#pragma once
#include "BaseScene.h"

struct MenuDeta {
	int x;
	int y;
	char MenuName[30];
};

class Menu:public BaseScene {
public:
	Menu();
	void Update();
	void Draw();
};