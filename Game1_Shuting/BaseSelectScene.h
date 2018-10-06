#pragma once
#include "BaseScene.h"
void BaseSelectSceneInitialize();

struct ItemData {
	char itemName[30];
	int x;
	int y;
};

class BaseSelectScene :public BaseScene {
	int m_itemNum;
	virtual void BackGroundDraw() {};
	virtual void DicisionProcess() = 0;
protected:
	ItemData m_itemData[10];
	int m_selectPoint;

public:
	BaseSelectScene(int ItemNum) :m_itemNum(ItemNum), m_selectPoint(0) {}
	void SetItemData(int ItemNum, ItemData data);
	void Update();
	void Draw();
};