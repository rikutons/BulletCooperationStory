#pragma once
#include "DxLib.h"
#include <string>

/*
自作関数1 CalcCenterX
中心にしたいx座標、
フォントのサイズ(CreateFontToHandleの第2引数)、
表示するテキストの内容
から左端のx座標を計算する、
*/
int CalcCenterX(int centerX, int fontSize, const char *cstr)
{
	int strLen, strWidth;
	int strSize = 0;
	strLen = (int)strlen(cstr);
	strWidth = GetDrawStringWidth(cstr, strLen);
	std::string str = cstr;
	while (!str.empty())
	{
		if (IsDBCSLeadByte(str[0]) == 0)
		{
			str.erase(0, 1);
			strSize++;
		}
		else
		{
			str.erase(0, 2);
			strSize++;
		}
	}
	strWidth = strLen * fontSize / 2 + strSize;
	return centerX - strWidth / 2;
}