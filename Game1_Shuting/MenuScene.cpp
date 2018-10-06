#include "MenuScene.h"
#include "ModeSelect.h"
#include "FazeSelect.h"
#include "ManualSelect.h"
#include "dxlib.h"
#include "EffectMgr.h"
#include "BaseSelectScene.h"

enum eMenuMode
{
	eNoneMenuMode,
	eSelectMode = 1,
	eSelectFaze,
	eManual,
};

namespace {
	BaseSelectScene* menuMode;
	eMenuMode nowMenuMode;
	int MV_BackGround;
}

Menu::Menu() {
	nowMenuMode = eSelectMode;
	MV_BackGround = LoadGraph("../material/movie/menuBackGround.mp4");
	PlayMovieToGraph(MV_BackGround);
}

void Menu::Update() {
	//”wŒi“®‰æ‚ÌÄ¶‚ª’âŽ~(=I—¹)‚µ‚Ä‚¢‚½‚çAÅ‰‚ÌƒtƒŒ[ƒ€‚É–ß‚·
	if (GetMovieStateToGraph(MV_BackGround) == 0) {
		SeekMovieToGraph(MV_BackGround, 0);
		PlayMovieToGraph(MV_BackGround);
	}
	//nowMenuMode‚É‡‚í‚¹‚ÄAmenuMode‚ðØ‚è‘Ö‚¦‚é
	if (nowMenuMode != eNoneMenuMode) {
		delete menuMode;
		switch (nowMenuMode) {
		case eSelectMode:
			menuMode = new ModeSelect();
			break;
		case eSelectFaze:
			menuMode = new FazeSelect();
			break;
		case eManual:
			menuMode = new ManualSelect();
			break;
		default:
			break;
		}
		nowMenuMode = eNoneMenuMode;
	}
	menuMode->Update();
	EffectMgrUpdate();
}

void Menu::Draw() {
	DrawGraph(0, 0, MV_BackGround, FALSE);
	menuMode->Draw();
	EffectMgrDraw();
}

void SetMenuMode(int nextMode) {
	nowMenuMode = (eMenuMode)nextMode;
}