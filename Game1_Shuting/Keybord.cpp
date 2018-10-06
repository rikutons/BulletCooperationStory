#include"dxlib.h"

namespace {
	int key[256]; // キーが押されているフレーム数を格納する
}

int KeybordUpdate() {
	char getKey[256];
	GetHitKeyStateAll(getKey);
	for (int i = 0; i < 256; i++) {
		//WASD等の時は別の処理(ゲームパッドの反映)をしたいので飛ばす
		if (i == KEY_INPUT_W || i == KEY_INPUT_A ||
			i == KEY_INPUT_S || i == KEY_INPUT_D || KEY_INPUT_Q ||
			i == KEY_INPUT_UP || i == KEY_INPUT_LEFT ||
			i == KEY_INPUT_DOWN || i == KEY_INPUT_RIGHT ||
			i == KEY_INPUT_RSHIFT || i == KEY_INPUT_LSHIFT ||
			i == KEY_INPUT_RETURN || i == KEY_INPUT_ESCAPE);
		else if (getKey[i] != 0) {
			key[i]++;
		}
		else {
			key[i] = 0;
		}
	}

	int getPad1 = GetJoypadInputState(DX_INPUT_PAD1);
	int getPad2 = GetJoypadInputState(DX_INPUT_PAD2);

	//WASD,ゲームパッド1スティック
	if ((getPad1 & PAD_INPUT_UP) != 0 || getKey[KEY_INPUT_W] != 0)
		key[KEY_INPUT_W]++;
	else key[KEY_INPUT_W] = 0;
	if ((getPad1 & PAD_INPUT_LEFT) != 0 || getKey[KEY_INPUT_A] != 0)
		key[KEY_INPUT_A]++;
	else key[KEY_INPUT_A] = 0;
	if ((getPad1 & PAD_INPUT_DOWN) != 0 || getKey[KEY_INPUT_S] != 0)
		key[KEY_INPUT_S]++;
	else key[KEY_INPUT_S] = 0;
	if ((getPad1 & PAD_INPUT_RIGHT) != 0 || getKey[KEY_INPUT_D] != 0)
		key[KEY_INPUT_D]++;
	else key[KEY_INPUT_D] = 0;

	//方向,ゲームパッド2スティック
	if ((getPad2 & PAD_INPUT_UP) != 0 || getKey[KEY_INPUT_UP] != 0)
		key[KEY_INPUT_UP]++;
	else key[KEY_INPUT_UP] = 0;
	if ((getPad2 & PAD_INPUT_LEFT) != 0 || getKey[KEY_INPUT_LEFT] != 0)
		key[KEY_INPUT_LEFT]++;
	else key[KEY_INPUT_LEFT] = 0;
	if ((getPad2 & PAD_INPUT_DOWN) != 0 || getKey[KEY_INPUT_DOWN] != 0)
		key[KEY_INPUT_DOWN]++;
	else key[KEY_INPUT_DOWN] = 0;
	if ((getPad2 & PAD_INPUT_RIGHT) != 0 || getKey[KEY_INPUT_RIGHT] != 0)
		key[KEY_INPUT_RIGHT]++;
	else key[KEY_INPUT_RIGHT] = 0;

	//XInput基準
	//Enter,Esc,Shift,Q(SKIP)
	if ((getPad1 & PAD_INPUT_3) != 0 ||
		getKey[KEY_INPUT_LSHIFT] != 0) key[KEY_INPUT_LSHIFT]++;
	else key[KEY_INPUT_LSHIFT] = 0;

	if ((getPad2 & PAD_INPUT_3) != 0 ||
		getKey[KEY_INPUT_RSHIFT] != 0) key[KEY_INPUT_RSHIFT]++;
	else key[KEY_INPUT_RSHIFT] = 0;

	if ((getPad1 & PAD_INPUT_1) != 0 || (getPad2 & PAD_INPUT_1) != 0 ||
		getKey[KEY_INPUT_Q] != 0) key[KEY_INPUT_Q]++;
	else key[KEY_INPUT_Q] = 0;

	if ((getPad1 & PAD_INPUT_2) != 0 || (getPad2 & PAD_INPUT_2) != 0 ||
		getKey[KEY_INPUT_RETURN] != 0) key[KEY_INPUT_RETURN]++;
	else key[KEY_INPUT_RETURN] = 0;

	if ((getPad1 & PAD_INPUT_5) != 0 || (getPad2 & PAD_INPUT_5) != 0 ||
		getKey[KEY_INPUT_ESCAPE] != 0) key[KEY_INPUT_ESCAPE]++;
	else key[KEY_INPUT_ESCAPE] = 0;

	return 0;
}

int KeybordGet(int KeyCode) {
	return key[KeyCode];
}

//カーソルが、長押しするほど加速する仕様
bool CursorCheck(int frameCount) {
	if (frameCount == 1 || frameCount == 30
		|| frameCount % 6 == 0 && frameCount > 39 || frameCount % 3 == 0 && frameCount > 80)
		return true;
	else
		return false;
}