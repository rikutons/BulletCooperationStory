#include "dxlib.h"
#include "Constant.h"

static int m_Image01;

void BackGroundInitialize() {
	m_Image01 = LoadGraph("/makes/mt/îwåi01.png");
}

void BackGroundDraw() {
	DrawRotaGraph(WindowWide/2, WindowHeight/2, 1, 0, m_Image01, TRUE);
}