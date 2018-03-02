#include "DxLib.h"

namespace {
	int BGMHandle[2];
	int SEHandle[4];
	int nowBGMId;
}

void SoundMgrInitialize() {
	BGMHandle[0] = LoadSoundMem("../material/bgm/menu.ogg");
	BGMHandle[1] = LoadSoundMem("../material/bgm/vsBOSS.ogg");
	nowBGMId = 0;

	SEHandle[0] = LoadSoundMem("../material/se/Select.ogg");
	SEHandle[1] = LoadSoundMem("../material/se/Decision.ogg");
	SEHandle[2] = LoadSoundMem("../material/se/Hit.ogg");
	SEHandle[3] = LoadSoundMem("../material/se/Explosion.ogg");
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

void SoundMgrFinalize() {

}