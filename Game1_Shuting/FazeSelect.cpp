#include "Dxlib.h"
#include "SceneMgr.h"
#include "FazeSelect.h"
#include "MenuScene.h"
#include "EnemyAdd.h"

//-----------------------------------------------------------------------------
//定数
//メニューの項目数
#define ITEM_NUM 4

//-----------------------------------------------------------------------------

namespace {
	int F_Kaiso50;
}

FazeSelect::FazeSelect() :BaseSelectScene(ITEM_NUM) {
	F_Kaiso50 = CreateFontToHandle(
		"廻想体 ネクスト B", 50, 3, DX_FONTTYPE_ANTIALIASING_EDGE);
	SetItemData(0, { "フェイズ 1",100,180 });
	SetItemData(1, { "フェイズ 2",100,280 });
	SetItemData(2, { "フェイズ 3(ボスのみ)",100,380 });
	SetItemData(3, { "戻る" ,100,480 });
}

void FazeSelect::BackGroundDraw() {
	DrawStringToHandle(60, 80,
		"開始フェイズ選択", GetColor(220, 220, 255), F_Kaiso50);
}


void FazeSelect::DicisionProcess() {
	switch (m_selectPoint) {
	case 3:
		SetMenuMode(1);
		break;
	default:
		SetFaze(m_selectPoint + 1);
		SetScene(eGame);
		break;
	}
}