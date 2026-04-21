#pragma once

class C_CharaBase {
private:
	float X;//X座標
	float Y;//Y座標
	float MoveSpeed;//移動速度　これを分解してXY速度を出す？
	float SpeedX;//X軸の速度
	float SpeedY;//Y軸の速度
public:
	C_CharaBase();
	~C_CharaBase();
	void Init();
	void Update();
	void Draw();
};
