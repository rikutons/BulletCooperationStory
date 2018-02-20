#include "dxlib.h"
#include "Keybord.h"
#include "SceneMgr.h"
#include "Common.h"
#include "Weapon.h"

//-----------------------------------------------------
//定数
//武器の速度
#define SPEED 10

//-----------------------------------------------------

static int Image[2];

void WeaponInitialize() {
	Image[0] = LoadGraph("../material/picture/Weapon01.png");
	Image[1] = LoadGraph("../material/picture/Weapon02.png");
}


Weapon::Weapon(float X, float Y,int WeaponNum) :
	Mover(X,Y,SPEED,0),weaponNum(WeaponNum) {}


void Weapon::Update() {
	y -= speed;
	/*
	画面外に行った武器を削除するため、もし画面外に出たならalive=falseにする。
	尚、不自然に武器が消えてしまうことを防ぐため、
	ものが消える範囲を実際のウインドウサイズより多少大きくしてある。
	武器は上にしか動かないので、y座標のマイナス判定のみ行う。
	*/
	if (y < WINDOW_HEIGHT*-0.2) alive = false;
}

void Weapon::Draw() {
	DrawRotaGraphF(x, y, 0.2, 0, Image[weaponNum], TRUE);
}
