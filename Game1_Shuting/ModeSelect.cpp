#include "Dxlib.h"
#include "SceneMgr.h"
#include "ModeSelect.h"
#include "MenuScene.h"

//---------------------------------------------------------
//定数
//メニューの項目数
#define ITEM_NUM 3

//---------------------------------------------------------

ModeSelect::ModeSelect() :BaseSelectScene(ITEM_NUM) {
	SetItemData(0, { "メインモード",100,170 });
	SetItemData(1, { "操作方法" ,100,270 });
	SetItemData(2, { "終了" ,100,370 });
}


void ModeSelect::DicisionProcess() {
	switch (m_selectPoint) {
	case 0:
		SetMenuMode(2);
		break;
	case 1:
		SetMenuMode(3);
		break;
	case 2:
		SetScene(eEnd);
		break;
	}
}