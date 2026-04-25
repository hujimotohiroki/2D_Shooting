#pragma once

class C_BulletBase {
protected:
	Math::Matrix Mat;
	float X;
	float Y;
	float MoveSpeed;
	float SpeedX;
	float SpeedY;
	float Size;			//元画像を何倍にするか
	float Radius;		//正確なサイズ（半径）
	float Angle;
	int Flag;			//種類
	int Timer;
	int attack;
	KdTexture Tex;
public:
	C_BulletBase();
	~C_BulletBase() { Release(); }
	void Init();
	void Update();
	void Draw();
private:
	void Release();
};
