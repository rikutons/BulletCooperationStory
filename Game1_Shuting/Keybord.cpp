#include"dxlib.h"

namespace {
	int key[256]; // キーが押されているフレーム数を格納する
}

int KeybordUpdate() {
	char getKey[256];
	GetHitKeyStateAll(getKey);
	for (int i = 0; i < 256; i++) {
		//WASD等の時は別の処理(ゲームパッドの反映)をしたいので飛ばす
		if (i == KEY_INPUT_W || i == KEY_INPUT_A || i == KEY_INPUT_S || i == KEY_INPUT_D ||
			i == KEY_INPUT_LSHIFT || i == KEY_INPUT_RETURN || i == KEY_INPUT_ESCAPE);
		else if (getKey[i] != 0) {
			key[i]++;
		}
		else {
			key[i] = 0;
		}
	}

	int getPad = GetJoypadInputState(DX_INPUT_PAD1);

	//WASD,ゲームパッドスティック
	if ((getPad & PAD_INPUT_UP) != 0 || getKey[KEY_INPUT_W] != 0) key[KEY_INPUT_W]++;
	else key[KEY_INPUT_W] = 0;
	if ((getPad & PAD_INPUT_LEFT) != 0 || getKey[KEY_INPUT_A] != 0) key[KEY_INPUT_A]++;
	else key[KEY_INPUT_A] = 0;
	if ((getPad & PAD_INPUT_DOWN) != 0 || getKey[KEY_INPUT_S] != 0) key[KEY_INPUT_S]++;
	else key[KEY_INPUT_S] = 0;
	if ((getPad & PAD_INPUT_RIGHT) != 0 || getKey[KEY_INPUT_D] != 0) key[KEY_INPUT_D]++;
	else key[KEY_INPUT_D] = 0;


	//Enter,Esc,Shift
	if ((getPad & PAD_INPUT_1) != 0 ||
		getKey[KEY_INPUT_LSHIFT] != 0) key[KEY_INPUT_LSHIFT]++;
	else key[KEY_INPUT_LSHIFT] = 0;
	if ((getPad & PAD_INPUT_2) != 0 ||
		getKey[KEY_INPUT_RETURN] != 0) key[KEY_INPUT_RETURN]++;
	else key[KEY_INPUT_RETURN] = 0;
	if ((getPad & PAD_INPUT_5) != 0 ||
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