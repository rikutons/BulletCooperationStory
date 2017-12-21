#include "dxlib.h"
#include "Constant.h"

static int m_Image;

void BossInitialize(){
	m_Image = LoadGraph("/makes/mt/É{ÉX01.png");
}

void BossUpdate() {

}

void BossDraw() {
	DrawRotaGraph(BossX, BossY, 0.8, 3.14, m_Image, TRUE);
}