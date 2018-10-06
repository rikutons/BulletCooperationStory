#include "DxLib.h"

namespace {
	int BGMHandle[4];
	int SEHandle[6];
	int nowBGMId;
}

void SoundMgrInitialize() {
	BGMHandle[0] = LoadSoundMem("../material/bgm/menu.ogg");
	BGMHandle[1] = LoadSoundMem("../material/bgm/ìπíÜã»1.ogg");
	BGMHandle[2] = LoadSoundMem("../material/bgm/ìπíÜã»2.ogg");
	BGMHandle[3] = LoadSoundMem("../material/bgm/vsBOSS.ogg");
	nowBGMId = 0;

	SEHandle[0] = LoadSoundMem("../material/se/Select.ogg");
	SEHandle[1] = LoadSoundMem("../material/se/Decision.ogg");
	SEHandle[2] = LoadSoundMem("../material/se/Hit.ogg");
	SEHandle[3] = LoadSoundMem("../material/se/Explosion.ogg");
	SEHandle[4] = LoadSoundMem("../material/se/Clear.ogg");
	SEHandle[5] = LoadSoundMem("../material/se/Cure.ogg");
}

//-1Çà¯êîÇ…Ç∑ÇÈÇ∆ÅAâπäyÇé~ÇﬂÇÈ
void ChangeBGM(int bgmId) {
	StopSoundMem(BGMHandle[nowBGMId]);
	if (bgmId != -1) {
		PlaySoundMem(BGMHandle[bgmId], DX_PLAYTYPE_LOOP);
		nowBGMId = bgmId;
	}
}

void PlaySE(int seId) {
	PlaySoundMem(SEHandle[seId], DX_PLAYTYPE_BACK);
}
