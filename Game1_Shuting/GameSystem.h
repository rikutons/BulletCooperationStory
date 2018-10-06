#pragma once

void GameSystemInitialize();
void GameSystemUpdate();
void BackGroundDraw();
void GameSystemDraw();
void LifeDown();
void LifePlus();
void AddScore(int, int);
void ChangeBackGround();
bool GetChangeBackGround();
int GetGameTime();
bool GetIsGameOver();
bool GetIsSelectEscape();
void SetIsSelectEscape(bool);
