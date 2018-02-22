#pragma once
#include "DxLib.h"
#include <string>

using namespace std;

/*
自作関数。中心にしたいx座標、
フォントのサイズ(CreateFontToHandleの第2引数)、
表示するテキストの内容
から左端のx座標を計算する、
*/
int CalcCenterX(int centerX, int fontSize, const char *cstr)
{
	int StrLen, StrWidth, StrSize = 0;
	StrLen = (int)strlen(cstr);
	StrWidth = GetDrawStringWidth(cstr, StrLen);
	string str = cstr;
	while (!str.empty())
	{
		if (IsDBCSLeadByte(str[0]) == 0)
		{
			str.erase(0, 1);
			StrSize++;
		}
		else
		{
			str.erase(0, 2);
			StrSize++;
		}
	}
	StrWidth = StrLen * fontSize / 2 + StrSize;
	return centerX - StrWidth / 2;
}