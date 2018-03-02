#pragma once

/*
移動するものすべての基底クラス。
引数 4つ 1.初期x座標 2.初期y座標 3.初速度 4.発射角度
*/
class Mover {
protected:
	float m_x, m_y,
		m_speed;
	double m_angle;
	bool m_alive;
public:
	Mover(float X, float Y, float Speed, double Angle);
	virtual void Update() = 0;
	virtual void Draw() = 0;
	bool GetAlive() { return m_alive; }
};

/*
移動するもののうち、入力に関係せず複雑な動きをするクラス。
速度と曲がり具合は全く対応しない。
固定弾:引数(4+4=)8つ。 5.どの画像を使うか 詳細はEnemy.cpp 6.倒した時に得られるスコア 7.加速度
8.初期の曲がり具合(曲がる程度) 一秒間にn*60度回転する。(60fps
9.曲がり具合の加速度 一秒間にn*60度回転量が増加する。(60fps
変化する座標に依存する弾:引数(4-1+6=)9つ。 初期角度をなくし、10.目標X 11.目標y
*/
class AutoMover :public Mover {
protected:
	int m_imageType;
	float m_speedRate;
	double m_carbDegree;
	double m_angleRate, m_anglePlus;
	int m_stopFrame, m_stopFrameCount;
	double m_stopCarbAngle;

public:
	AutoMover(float, float, int,
		float, float, double, double, double, int, double);

	AutoMover(float, float, float, float, int,
		float, float, double, double, double, int, double);

	void Update();
};