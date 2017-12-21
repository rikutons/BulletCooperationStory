#include "dxlib.h"
#include "Bullet.h"
#include "Game.h"
#include "BulletMode.h"
#include "BulletMgr.h"
#include <vector>
#include "Constant.h"

using namespace std;

extern float cx, cy;

static vector<BaseBullet*> bullet;

static vector<BaseBulletMode*> BulletMode;

void BulletMgrInitialize() {
	BulletMode.push_back(new ModeBoss1);
}

void BulletMgrUpdate() {

	DrawFormatString(0, 0, GetColor(255, 255, 255), "bullet.size:%d,BulletMode.size:%d", bullet.size(), BulletMode.size());
	
	//新しい弾を追加する
	for (auto _BulletMode : BulletMode) {
		_BulletMode->newbullet(&bullet);
	}

	//弾を動かす
	for (auto _bullet : bullet) {
		_bullet->Update();
	}

	//配列数が増えすぎるとメモリ消費量が膨大になるので、画面外に行った弾をメモリ解放、削除する。
	//尚、不自然に球が消えてしまうことを防ぐため、球が消える範囲を実際のウインドウサイズより多少大きくしてある。
	for (unsigned int i = 0; i < bullet.size(); i++) {
		if (bullet[i]->GetBulletx() > WindowWide*1.2 || bullet[i]->GetBulletx() < WindowWide*-0.2 || bullet[i]->GetBullety() > WindowHeight*1.2 || bullet[i]->GetBullety() < WindowHeight*-0.2) {
			delete bullet[i];
			bullet.erase(bullet.begin() + i);
		}
	}
}

void BulletMgrDraw() {
	//サイズソートをのちに実装((球が重なった時の描画をきれいに

	for (auto _bullet : bullet) {
		_bullet->Draw();
	}
}


void BulletMgrFinalize() {
	for (auto _bullet : bullet) {
		delete _bullet;
	}
	bullet.clear();
	BulletMode.clear();
}


/*
次の弾のModeを指定する
必要な引数2つ{	1.eMode モード名の指定(eBoss1など),
				2.bool さっきまで使っていたモードを破棄するか否か(破棄しない場合は二つ以上のモードの同時進行となる);}
*/
void SetBulletMode(eMode pointMode, bool trush) {
	if (trush) {
		BulletMode.pop_back();
	}
	switch(pointMode) {
	case eBoss1:
		BulletMode.push_back(new ModeBoss1());
		break;
	case eBoss2:
		BulletMode.push_back(new ModeBoss2());
		break;
	}
}