/*

DrawFormatString(0, 0, GetColor(255,255,255), "数値1:%d,数値2:%d", , );

DrawFormatString(BOSS_X, 240, GetColor(255, 255, 255), "x:%f,y:%f", x, y);


------------弾の動きライブラリ？--------------
前方にランダムに放射
if (BulletModeFlag % 1 == 0)
bullet->push_back(new B2straight(BOSS_X,BOSS_Y, GetRand(15), 0.05, 0.f, 0.1f,GetRand(64000)/BOSS_Y.f,GetRand(38000)/BOSS_Y.f+BOSS_Y));
----------------------------------------------
*/
