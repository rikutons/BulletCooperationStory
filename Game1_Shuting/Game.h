#pragma once
#include "BaseScene.h"
class Game:public BaseScene {
public:
	Game();
	void Update();
	void Draw();
	~Game();
};
void SetGameover();