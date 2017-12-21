#pragma once

enum eMode {
	eBoss1,
	eBoss2,
	eBoss3,

	eNoneMode,
};
void BulletMgrInitialize();
void BulletMgrUpdate();
void BulletMgrDraw();
void BulletMgrFinalize();
void SetBulletMode(eMode a,bool trush);