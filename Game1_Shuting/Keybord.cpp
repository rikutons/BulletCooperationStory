#include"dxlib.h"

static int m_Key[256]; // キーが押されているフレーム数を格納する

int KeybordUpdate() {
	char tmpKey[256]; // 現在のキーの入力状態を格納する
	GetHitKeyStateAll(tmpKey); // 全てのキーの入力状態を得る
	for (int i = 0; i < 256; i++) {
		if (tmpKey[i] != 0) { // i番のキーコードに対応するキーが押されていたら
			m_Key[i]++;     // 加算
		}
		else {              // 押されていなければ
			m_Key[i] = 0;   // 0にする
		}
	}
	return 0;
}

int KeybordGet(int KeyCode) {
	return m_Key[KeyCode];
}

bool CursorCheck(int framecount) {
	if (framecount == 1 || framecount == 30 || framecount % 10 == 0 && framecount > 49)
		return true;
	else
		return false;
}