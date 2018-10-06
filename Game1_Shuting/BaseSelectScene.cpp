#include "dxlib.h"
#include "BaseSelectScene.h"
#include "Keybord.h"
#include "SoundMgr.h"
#include "EffectMgr.h"

//どのシーンでも共通の変数
namespace {
	int F_Meiryo30;
}

void BaseSelectSceneInitialize() {
	F_Meiryo30 = CreateFontToHandle(
		"メイリオ", 30, 3, DX_FONTTYPE_ANTIALIASING_EDGE);
}

void BaseSelectScene::SetItemData(int ItemNum, ItemData data) {
	m_itemData[ItemNum] = data;
}

void BaseSelectScene::Update() {
	if (m_itemNum != 1) {
		// 下キーかSキーが押されていたら下にカーソルを移動する
		if (CursorCheck(KeybordGet(KEY_INPUT_DOWN)) ||
			CursorCheck(KeybordGet(KEY_INPUT_S))) {
			m_selectPoint = (m_selectPoint + 1) % m_itemNum;
			PlaySE(0);
		}

		// 上キーかWキーが押されていたら上にカーソルを移動する
		if (CursorCheck(KeybordGet(KEY_INPUT_UP)) ||
			CursorCheck(KeybordGet(KEY_INPUT_W))) {
			m_selectPoint = (m_selectPoint - 1 + m_itemNum) % m_itemNum;
			PlaySE(0);
		}
	}
	if (KeybordGet(KEY_INPUT_RETURN) == 1) {//エンターキーが押されたら
		PlaySE(1);
		PlayEffect(
			(float)m_itemData[m_selectPoint].x,
			(float)m_itemData[m_selectPoint].y, 3);
		DicisionProcess();
	}
}

void BaseSelectScene::Draw() {
	BackGroundDraw();
	int red = GetColor(255, 0, 0);
	int white = GetColor(240, 240, 240);
	for (int i = 0; i < m_itemNum; i++) {
		if (m_selectPoint == i)
			DrawStringToHandle(m_itemData[i].x - 20, m_itemData[i].y,
				m_itemData[i].itemName, red, F_Meiryo30);
		else
			DrawStringToHandle(m_itemData[i].x, m_itemData[i].y,
				m_itemData[i].itemName, white, F_Meiryo30);
	}
}