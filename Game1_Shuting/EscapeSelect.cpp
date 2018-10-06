#include "dxlib.h"
#include "EscapeSelect.h"
#include "Common.h"
#include "MyDxlib.h"
#include "GameSystem.h"

//-----------------------------------------------------------------------------
//定数
//メニューの項目数
#define ITEM_NUM 2

//-----------------------------------------------------------------------------

namespace {
	int F_Meiryo70;
	int endTextX;
}

EscapeSelect::EscapeSelect() :BaseSelectScene(ITEM_NUM) {
	F_Meiryo70 = CreateFontToHandle(
		"メイリオ", 70, 3, DX_FONTTYPE_ANTIALIASING_EDGE);
	endTextX = CalcCenterX(WINDOW_WIDE / 2, 70, "終了しますか？");

	int x[2];
	x[0] = CalcCenterX(WINDOW_WIDE / 2, 30, "はい");
	x[1] = CalcCenterX(WINDOW_WIDE / 2, 30, "いいえ");
	SetItemData(0, { "はい",x[0],250 });
	SetItemData(1, { "いいえ",x[1],320 });
}

void EscapeSelect::BackGroundDraw() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBox(0, 0, WINDOW_WIDE, WINDOW_HEIGHT, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawStringToHandle(endTextX, 130,
		"終了しますか？", GetColor(0, 20, 255), F_Meiryo70);
}

void EscapeSelect::DicisionProcess() {
	switch (m_selectPoint) {
	case 0:
		SetScene(eMenu);
		break;
	case 1:
		SetIsSelectEscape(false);
		break;
	}
}