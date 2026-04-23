#pragma once

class C_CharaBase {
protected:
	Math::Matrix Mat;
	float X;
	float Y;
	float MoveSpeed;
	float SpeedX;
	float SpeedY;
	float Size;			//元画像を何倍にするか
	float Radius;		//正確なサイズ（半径）
	int Flag;			//種類
	int Anim;			//描画状態
	int Timer;
	int HP;
	KdTexture Tex;
public:
	C_CharaBase();
	~C_CharaBase() { Release(); }
	void Init();
	void Update();
	void Draw();
private:
	void Release();
};
