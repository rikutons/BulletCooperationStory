#pragma once


//--------------------------------------------------------
//定数

const double PI = 3.14159265359;

//ウインドウサイズ
const int WindowWide = 800;
const int WindowHeight = 600;

//枠の大きさ
const int FrameSizeX = 40;
const int FrameSizeY = 30;

//プレイヤーの座標の初期値
const float InitialX = 400.f;
const float InitialY = 200.f;

//当たり判定の半径
const float PHitRange  = 11; //プレイヤー
const float BHitRange[] = { 68 }; //弾配列

//ボスの座標の初期値
const float BossX = 400.f;
const float BossY = 100.f;