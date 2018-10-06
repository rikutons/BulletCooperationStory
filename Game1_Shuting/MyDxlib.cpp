#include "DxLib.h"
#include <string>

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