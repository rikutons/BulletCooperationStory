#include <vector>
#include "Dxlib.h"

using namespace std;

struct EffectDeta {
	float x;
	float y;
	int mvHandle;
};

namespace {
	vector<EffectDeta> effectTask;
	int MV_Effect[6];
}

void EffectMgrInitialize() {
	MV_Effect[0] = LoadGraph("../material/movie/effect01.mp4");
	MV_Effect[1] = LoadGraph("../material/movie/effect02.mp4");
	MV_Effect[2] = LoadGraph("../material/movie/effect03.mp4");
	MV_Effect[3] = LoadGraph("../material/movie/effect04.mp4");
	MV_Effect[4] = LoadGraph("../material/movie/effect05.mp4");
	MV_Effect[5] = LoadGraph("../material/movie/effect06.mp4");
}

void EffectMgrUpdate() {
	int size = (int)effectTask.size();
	DrawFormatString(0, 0, GetColor(255, 255, 255), "êîíl1:%d", size);
	for (int i = 0; i < size; i++)
	{
		if (GetMovieStateToGraph(effectTask[i].mvHandle) == 0) {
			SeekMovieToGraph(effectTask[i].mvHandle, 0);
			effectTask.erase(effectTask.begin() + i);
			i--, size--;
		}
	}
}

void EffectMgrDraw() {
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	for (auto i : effectTask) {
		DrawRotaGraphF(i.x, i.y, 1.f, 0, i.mvHandle, FALSE);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void PlayEffect(float x, float y, int effectnum) {
	effectTask.push_back({ x,y,MV_Effect[effectnum] });
	PlayMovieToGraph(effectTask.back().mvHandle);
}