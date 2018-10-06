#pragma once


/*
自作関数1 CalcCenterX
中心にしたいx座標、
フォントのサイズ(CreateFontToHandleの第2引数)、
表示するテキストの内容
から左端のx座標を計算する、
*/
int CalcCenterX(int centerX, int fontSize, const char *cstr);