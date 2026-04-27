#pragma once

class C_GameScene;

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
	int PrevShot;
	int HP;
	KdTexture Tex;
	C_GameScene* m_owner;
public:
	C_CharaBase();
	~C_CharaBase() { Release(); }
	void Init();
	void Update();
	void Draw();

	void SetOwner(C_GameScene* owner) { m_owner = owner; }
private:
	void Release();
};
