#include "Enemy.h"
#include "EnemyAdd.h"
#include "SoundMgr.h"
#include "SceneMgr.h"
#include "EffectMgr.h"
#include "Boss.h"
#include "Common.h"
#include "Dxlib.h"
#include "GameSystem.h"
#include "Keybord.h"

//-----------------------------------------------------------------------------
//定数
//武器の当たり判定の半径
#define W_HIT_RANGE 5

//ボスの当たり判定の半径
const int BHitRange[] = { 50,50,50,94 };

//中ボス、ボス敵のID
#define MEDIUM_BOSS1_ID 4
#define MEDIUM_BOSS2_ID 5
#define MEDIUM_BOSS3_ID 6
#define BOSS_ID 7

//-----------------------------------------------------------------------------

Boss::Boss(
	int ImageType, eBulletMode Mode,
	int BulletColor, int ShotSpeed,
	int MoveFrame, int StopFrame, int SpecialShotLife) :
	Enemy(
		400, -200,
		ImageType, Mode,
		1.f, 0.f,
		180, 0, 0.0,
		BulletColor, 0, ShotSpeed, 0,
		StopFrame),
	m_moveFrame(MoveFrame), m_specialShotLife(SpecialShotLife),
	m_isSpecialShot(false), m_nowMode(eNoneMode), m_isPlayEffect(true),
	m_specialShotCount(0), m_isMoveCenter(true), m_beforeBulletPattern(-1),
	m_faze(0) {
	m_moveStartFrame = (m_mode == eBoss1 ? 700 : 300);
	m_stopFrameCount = m_stopFrame;
};

void Boss::BulletPlus(std::vector<Bullet> &bullet, float cx, float cy) {
	float x = m_x, y = m_y;
	m_frameCount++;

	//登場時
	if (m_frameCount < m_moveStartFrame) {
		//ボスor中ボスで違う処理
		//Qキーが押されたらスキップ
		if (KeybordGet(KEY_INPUT_Q)) {
			m_frameCount = m_moveStartFrame - 1;
			m_y = 100;
			m_speed = 0;
			if (m_mode == eBoss1) ChangeBackGround();
		}
		if (m_mode == eBoss1) {
			if (m_frameCount == 500) {
				m_speed = 0;
				ChangeBackGround();
				PlayEffect(400, 300, 2);
			}
			else if (m_frameCount == 600) {
				m_speedRate = 0.08000001f;
				m_angle = 0;
			}
			else if (m_frameCount == 650) {
				m_speedRate = -0.08000001f;
			}
			else if (m_frameCount == 700) {
				m_speedRate = 0;
			}
		}
		else {
			if (m_frameCount == 299) {
				m_speed = 0;
			}
		}
	}
	//ライフが少ないとき
	else if (m_life <= m_specialShotLife) {
		//共通処理
		if (!m_isSpecialShot) {
			m_specialShotCount++;
		}
		if (m_isMoveCenter) {
			MoveCenter();
			m_isMoveCenter = false;
		}
		//誤差を修正
		if (!m_isSpecialShot&& abs(400 - m_x) < 0.1) {
			m_x = 400;
			m_speed = 0;
		}
		if (m_specialShotCount == m_moveFrame + 80) {
			m_isSpecialShot = true;
			m_specialShotCount = 0;
			m_frameCount = m_moveStartFrame;
		}
		int f = m_frameCount - m_moveStartFrame;
		m_nowMode = eNoneMode;

		//個別処理
		switch (m_mode)
		{
		case eMediumBoss1:
			y += 40;
			if (m_x == 400 && m_isPlayEffect) {
				PlayEffect(400, 300, 0);
				m_shotSpeed = 100;
			}
			else if (m_isSpecialShot) {
				m_nowMode = eMediumBoss1;
			}
			break;
		case eMediumBoss2:
			y += 40;
			if (m_x == 400 && m_isPlayEffect) {
				PlayEffect(400, 300, 1);
				m_shotSpeed = 150;
				m_bulletColor = 6;
			}
			else if (m_isSpecialShot) {
				if (f % 2 == 0) {
					BulletAdd(eMediumBoss2, bullet, x, y,
						cx, cy, &m_bulletAngle, &m_bulletColor);
				}
			}
			break;
		case eBoss1:
			switch (m_faze) {
			case 0:
				if (m_x == 400 && m_isPlayEffect) {
					PlayEffect(400, 300, 0);
					m_shotSpeed = 5;
					m_bulletColor = 3;
				}
				/*else if (m_life < 10) {
					m_faze = 1;
					m_life = 150;
					m_isSpecialShot = false;
					m_isPlayEffect = true;
				}*/
				else if (m_isSpecialShot) {
					m_nowMode = eBoss1_1;
					if (f*m_shotSpeed % 300 == 0) {
						SetSpecialAdd(1, m_bulletAngle);
					}
				}
				break;
			}
			break;
		}

		//共通処理
		if (m_x == 400 && m_isPlayEffect) {
			m_isPlayEffect = false;
		}
		if (f*m_shotSpeed % 300 == 0) {
			BulletAdd(m_nowMode, bullet, x, y,
				cx, cy, &m_bulletAngle, &m_bulletColor);
		}
	}
	//それ以外
	else {
		//共通処理
		int f =
			(m_frameCount - m_moveStartFrame) % (m_moveFrame + m_stopFrame);
		int stopFrame = f - m_moveFrame;
		bool isShot =
			(stopFrame >= 0 && stopFrame*m_shotSpeed % 300 == 0);
		if (f == 0) {
			int isDirLeft;
			while (true) {
				m_speedRate = (GetRand(220) + 80)*0.001f;
				isDirLeft = (GetRand(1) == 1 ? 1 : -1);
				//計算式はノート参照()
				float nextx = m_moveFrame * m_moveFrame
					/ 4 * m_speedRate *isDirLeft + m_x;
				if (nextx > WINDOW_WIDE*0.1&&nextx < WINDOW_WIDE*0.9)
					break;
			}
			m_angle = (isDirLeft == 1 ? PI / 2 : PI / 2 * 3);
			m_bulletAngle = 0;
		}
		else if (f == m_moveFrame / 2) {
			m_speedRate *= -1;
		}
		else if (f == m_moveFrame) {
			m_speed = 0;
			m_speedRate = 0;
		}

		//個別処理
		switch (m_mode)
		{
		case eMediumBoss1: {
			y += 40;
			if (f == 0) {
				//連続して同じパターンが出現することを防ぐ
				do {
					m_bulletPattern = GetRand(2);
				} while (m_beforeBulletPattern == m_bulletPattern);
				m_beforeBulletPattern = m_bulletPattern;
			}
			switch (m_bulletPattern) {
			case 0:
				if (f == 0) {
					m_shotSpeed = 30;
					m_nowMode = eSpiral8;
				}
				break;
			case 1:
				if (f == 0) {
					m_shotSpeed = 150;
					m_nowMode = eStraightFallR;
				}
				break;
			}
			break;
		}

		case eMediumBoss2: {
			y += 40;
			if (f == 0) {
				do {
					m_bulletPattern = GetRand(2);
				} while (m_beforeBulletPattern == m_bulletPattern);
				m_beforeBulletPattern = m_bulletPattern;
			}
			switch (m_bulletPattern) {
			case 0:
				if (f == 0) {
					m_shotSpeed = 150;
					m_bulletColor = 6;
					m_aimPlayerNum = GetRand(1);
				}
				else if (isShot) {
					if (stopFrame*m_shotSpeed / 5 % 300 == 0) {
						BulletAdd(eSpiral6P, bullet, m_x, y,
							cx, cy, &m_bulletAngle, &m_bulletColor);
					}
					m_nowMode = eSpiralRC;
				}
				break;
			case 1:
				y += 74;
				if (f == 0) {
					m_shotSpeed = 100;
					m_bulletColor = 0;
					m_bulletAngle = 180;
					m_nowMode = eStraightMC1;
				}
				if (f == m_moveFrame) {
					PlayEffect(m_x, m_y, 5);
				}
				if (f < m_moveFrame + 90) {
					isShot = false;
				}
				else if (f > m_moveFrame + 91 && GetGameTime() % 3 != 0) {
					m_frameCount--;
					isShot = true;
				}
				break;
			case 2:
				if (f == 0) {
					m_shotSpeed = 300;
					m_bulletColor = 2;
					m_nowMode = eNoneMode;
				}
				else if (stopFrame % (m_moveFrame / 2) == 0) {
					BulletAdd(eSpiralSPD32, bullet, m_x, y,
						cx, cy, &m_bulletAngle, &m_bulletColor);
				}
				break;
			}
			break;
		}
		case eBoss1:
			if (f == 0) {
				m_nowMode = eSpiralRfP32;
				m_bulletColor = 5;
				m_shotSpeed = 10;
				m_aimPlayerNum = GetRand(2);
			}
		}

		//共通処理
		if (isShot) {
			BulletAdd(m_nowMode, bullet, x, y,
				cx, cy, &m_bulletAngle, &m_bulletColor);
		}
	}
}

void Boss::MoveCenter() {
	m_speedRate = 0;
	float dx = m_x - 400;
	m_angle = (dx < 0 ? PI / 2 : PI / 2 * 3);
	m_speed = abs(dx) / m_moveFrame;
}

bool Boss::IsHit(float wx, float wy, int wnum) {
	//最初、また必殺技前の移動の時はダメージを食らわない
	if (m_mode != eBoss1 && m_frameCount <= 300 ||
		m_mode == eBoss1 && m_frameCount <= 700 ||
		m_specialShotCount > 0) return false;
	if ((wx - m_x)*(wx - m_x) + (wy - m_y)*(wy - m_y) <=
		(W_HIT_RANGE + BHitRange[m_imageType - 4])*
		(W_HIT_RANGE + BHitRange[m_imageType - 4])) {
		m_life--;
		PlaySE(2);  //被弾ついでにHit音
		if (m_life == 0) {
			m_alive = false;
			AddScore(wnum, m_imageType);
			//死亡したのがボスだったら特殊な処理
			switch (m_imageType) {
			case MEDIUM_BOSS1_ID:
				SetFaze(2);
				break;
			case MEDIUM_BOSS2_ID:
				SetFaze(3);
				break;
			case MEDIUM_BOSS3_ID:
				SetFaze(4);
				break;
			case BOSS_ID:
				PlaySE(4);  //クリア音声
				SetScene(eGameClear);
				break;
			default:
				break;
			}
			LifePlus();
		}
		return true;
	}
	return false;
}