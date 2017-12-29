#pragma once

/*
移動するものすべての基底クラス。
引数 4つ 1.初期x座標 2.初期y座標 3.初速度 4.発射角度
*/
class Mover {
protected:
	float	x, y,
		speed;
	double angle;
	bool alive;
public:
	Mover(float X, float Y, float Speed, double Angle);
	virtual void Update() = 0;
	virtual void Draw() = 0;
	bool GetAlive();
};

/*
移動するもののうち、入力に関係せず複雑な動きをするクラス。
固定弾:引数(4+4=)8つ。 5.どの画像を使うか 詳細はEnemy.cpp 6.倒した時に得られるスコア 7.加速度 8.初期の曲がり具合(曲がる程度) 
9.曲がり具合の加速度 少ないほどよく回る。anglerate=1,speed=1で毎フレーム1回転。0だと回転なし
変化する座標に依存する弾:引数(4-1+6=)9つ。 初期角度をなくし、10.目標X 11.目標y
*/

class AutoMover :public Mover {
protected:
	int ImageType;
	float speedrate;
	double carbdegree;
	double anglerate;
public:
	AutoMover(float X, float Y, int _ImageType, float Speed, float Speedrate, double Angle , double Carbdegree, double Anglerate);	//固定弾

	AutoMover(float X, float Y, float GoalX, float GoalY, int _ImageType, float Speed, float Speedrate, double Carbdegree, double Anglerate);	
	//変化する座標に依存する弾
	void Update();
};