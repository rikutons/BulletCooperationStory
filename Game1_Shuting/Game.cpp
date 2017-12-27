#include "Player.h"
#include "Keybord.h"
#include "Boss.h"
#include "BulletMgr.h"
#include "Bullet.h"
#include "Gameover.h"
#include "SceneMgr.h"
#include "Game.h"
#include "BackGround.h"

static int Gameoverflag;

Game::Game(){
	BackGroundInitialize();
	PlayerInitialize();
	BossInitialize();
	BulletInitialize();
	BossInitialize();
	BulletMgrInitialize();
	Gameoverflag = 0;
}

void Game::Update() {
	PlayerUpdate();
	KeybordUpdate();
	BulletMgrUpdate();
	BossUpdate();
}

void Game::Draw() {
	BulletMgrDraw();
	CheckDeath();		//”»’è‚Ìã‚ª”’‚È‚çŽ‰–b”»’è‚ð‘—‚éŠÖ”B•`‰æ‚³‚ê‚½’e‚ðŒ©‚ÄŽ€–S‚·‚é‚©‚Ç‚¤‚©”»’f‚·‚é‚Ì‚ÅA’e‚ð•`‰æ‚µ‚½Œã‚És‚¤B
	BackGroundDraw();
	PlayerDraw();
	BulletMgrDraw();	//’e‚Ìã‚ÉƒvƒŒƒCƒ„[‚ª‚¢‚é‚Æ•sŽ©‘R‚È‚Ì‚ÅA’e‚ð‚à‚¤ˆê“x•`‰æ‚µ‚Ä‚¨‚­B
	BossDraw();
	if (Gameoverflag > 0) {
		Gameover();
		Gameoverflag = 0;
	}
}

Game::~Game() {
	BulletMgrFinalize();
}

void SetGameover() {
	Gameoverflag++;
}