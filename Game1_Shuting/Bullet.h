#pragma once
#include "dxlib.h"

void BulletInitialize();

/*
弾の基底クラス
必要な引数(4つ){float 始点x,	float 始点y,	int 弾の色(16色から番号指定),double サイズ(こっから判定を自動計算させたい)}
*/

class BaseBullet
{
protected:
	float x;
	float y;
	int color;
	double size;
	int deathjudge;
public:
	BaseBullet() {}
	BaseBullet(float a, float b, int c, double d);
	float GetBulletx();
	float GetBullety();
	virtual void Update() = 0;
	void Draw();
};

/*
弾のパターン1 曲がる
必要な引数(4つ+5つ){(基底クラスの4つ)				5.double 発射時の角度(60分法),	6.double 角度変更の速度、方向(一秒に、60/2n回時計回りに回転する),
					 7.double 角度変更の加速度,		8.float 初期速度,				9.float 速度の加速度;}
まったくテストしてないけど単調なカーブならほとんどこれで実装できるはず..！
*/
class B1rotation : public BaseBullet {
	double angle;
	double angleaccel;
	double anglespeed;
	float speed;
	float speedaccel;
public:
	B1rotation(float _x, float _y, int _c, double _s, double _angle, double _anglespeed, double _angleaccel, float _speed, float _speedaccel)
		:BaseBullet(_x, _y, _c, _s), angle(_angle / 180 * 3.14159265359), anglespeed(_anglespeed), angleaccel(_angleaccel), speed(_speed), speedaccel(_speedaccel) {};
	void Update();
};

/*
弾のパターン2 プレイヤー察知
必要な引数(4つ+4つ){(基底クラスの4つ)			5.6.弾のパターン1と同じ速度、加速度
					7.double 目標地点x			8.目標地点y(7.8共にcx,cyを入れることでプレイヤーを狙う)}
*/
class B2straight : public BaseBullet {
	double player_angle;
	float speed;
	float speedaccel;
	float goalx, goaly;
public:
	B2straight(float _x, float _y, int _c, double _s, float a, float b, float e, float f);
	void Update();
};