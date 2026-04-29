#pragma once

class C_BulletBase {
protected:
	Math::Matrix Mat;
	Math::Vector2 Pos;
	float MoveSpeed;
	Math::Vector2 Speed;
	float Size;				//元画像を何倍にするか
	float Radius;			//正確なサイズ（半径）
	float HitRadius;		//当たり判定があるサイズ
	Math::Vector2 HitDiff;	//当たり判定のずれ
	float Angle;
	int Flag;				//種類
	int Timer;
	int attack;
	KdTexture Tex;
public:
	C_BulletBase();
	~C_BulletBase() { Release(); }
	void Init();
	void Update();
	void Draw();

	void Shot(Math::Vector2 playerPos, int flag);
	int GetFlag() { return Flag; }
	Math::Vector2 GetPos() { return Pos; }
	float GetHitRadius() { return HitRadius; }
	void Hit() { Flag = 0; }
private:
	void Release();
};
