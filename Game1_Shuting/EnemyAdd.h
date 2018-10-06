#pragma once
#include <vector>
#include "Enemy.h"

void EnemyAddInitialize();
void SetFaze(int);
void EnemyAdd(std::vector<Enemy*>&);
void SetSpecialAdd(int, double);
