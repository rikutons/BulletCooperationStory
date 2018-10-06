#include "dxlib.h"
#include "ManualSelect.h"
#include "Common.h"
#include "MenuScene.h"

//-----------------------------------------------------------------------------
//íËêî
//ÉÅÉjÉÖÅ[ÇÃçÄñ⁄êî
#define ITEM_NUM 1

//-----------------------------------------------------------------------------

namespace {
	int image;
}

ManualSelect::ManualSelect() :BaseSelectScene(ITEM_NUM) {
	SetItemData(0, { "ñﬂÇÈ",730,550 });
	image = LoadGraph("../material/picture/Manual.png");
}

void ManualSelect::BackGroundDraw() {
	DrawRotaGraphF(WINDOW_WIDE / 2, WINDOW_HEIGHT / 2, 1.0, 0, image, TRUE);
}

void ManualSelect::DicisionProcess() {
	SetMenuMode(1);
}