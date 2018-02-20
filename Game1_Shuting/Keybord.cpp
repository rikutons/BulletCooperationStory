#include"dxlib.h"

static int m_Key[256]; // キーが押されているフレーム数を格納する

int KeybordUpdate() {
	char getKey[256];
	GetHitKeyStateAll(getKey);
	for (int i = 0; i < 256; i++) {
		//WASD等の時は別の処理(ゲームパッドの反映)をしたいので飛ばす
		if (i == KEY_INPUT_W || i == KEY_INPUT_A || i == KEY_INPUT_S || i == KEY_INPUT_D ||
			i == KEY_INPUT_LSHIFT || i == KEY_INPUT_RETURN || i == KEY_INPUT_ESCAPE);
		else if (getKey[i] != 0) {
			m_Key[i]++;
		}
		else {
			m_Key[i] = 0;
		}
	}

	int getPad = GetJoypadInputState(DX_INPUT_PAD1);

	//WASD,ゲームパッドスティック
	if ((getPad & PAD_INPUT_UP) != 0 || getKey[KEY_INPUT_W] != 0) m_Key[KEY_INPUT_W]++;
	else m_Key[KEY_INPUT_W] = 0;
	if ((getPad & PAD_INPUT_LEFT) != 0 || getKey[KEY_INPUT_A] != 0) m_Key[KEY_INPUT_A]++;
	else m_Key[KEY_INPUT_A] = 0;
	if ((getPad & PAD_INPUT_DOWN) != 0 || getKey[KEY_INPUT_S] != 0) m_Key[KEY_INPUT_S]++;
	else m_Key[KEY_INPUT_S] = 0;
	if ((getPad & PAD_INPUT_RIGHT) != 0 || getKey[KEY_INPUT_D] != 0) m_Key[KEY_INPUT_D]++;
	else m_Key[KEY_INPUT_D] = 0;


	//Enter,Esc,Shift
	if ((getPad & PAD_INPUT_1) != 0 ||
		getKey[KEY_INPUT_LSHIFT] != 0) m_Key[KEY_INPUT_LSHIFT]++;
	else m_Key[KEY_INPUT_LSHIFT] = 0;
	if ((getPad & PAD_INPUT_2) != 0 ||
		getKey[KEY_INPUT_RETURN] != 0) m_Key[KEY_INPUT_RETURN]++;
	else m_Key[KEY_INPUT_RETURN] = 0;
	if ((getPad & PAD_INPUT_5) != 0 ||
		getKey[KEY_INPUT_ESCAPE] != 0) m_Key[KEY_INPUT_ESCAPE]++;
	else m_Key[KEY_INPUT_ESCAPE] = 0;
	return 0;
}

int KeybordGet(int KeyCode) {
	return m_Key[KeyCode];
}

//カーソルが、長押しするほど加速する仕様
bool CursorCheck(int framecount) {
	if (framecount == 1 || framecount == 30
		|| framecount % 6 == 0 && framecount > 39 || framecount % 3 == 0 && framecount > 80)
		return true;
	else
		return false;
}