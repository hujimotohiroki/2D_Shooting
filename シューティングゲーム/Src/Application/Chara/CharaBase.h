#pragma once

class C_GameScene;

class C_CharaBase {
protected:
	Math::Matrix Mat;
	Math::Vector2 Pos;
	float MoveSpeed;
	Math::Vector2 Speed;
	float Size;				//元画像を何倍にするか
	float Radius;			//正確なサイズ（半径）
	float HitRadius;		//当たり判定(半径)
	Math::Vector2 HitDiff;	//中心のずれ
	int Flag;				//種類
	int Anim;				//描画状態
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

	int GetFlag() { return Flag; }
	void SetFlag(int flag) { Flag = flag; }
	Math::Vector2 GetPos() { return Pos; }
	float GetHitRadius() { return HitRadius; }
	void SetOwner(C_GameScene* owner) { m_owner = owner; }
private:
	void Release();
};
