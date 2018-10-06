#pragma once
//2つ以上のファイルで共有して使う処理を管理する

//-----------------------------------------------------------------------------
//定数

//ウインドウサイズ
#define WINDOW_WIDE 800
#define WINDOW_HEIGHT 600

//枠の大きさ
#define FRAME_SIZE_X 40
#define FRAME_SIZE_Y 30
#define FRAME_SIZE_MIDDLE 20

//プレイヤーごとの枠のx座標限界
#define POSX_LIMMIT_P1 WINDOW_WIDE/2-FRAME_SIZE_MIDDLE/2 
#define POSX_LIMMIT_P2 WINDOW_WIDE/2+FRAME_SIZE_MIDDLE/2 

//プレイヤーを正方形ととらえたときの半径
#define PLAYER_SIZE 25

//プレイヤーの数
#define PLAYER_NUM 2

#define PI 3.141592653589793238462643383279

//無限大
#define INF 100000000