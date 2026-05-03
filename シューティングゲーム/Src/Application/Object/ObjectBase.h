#pragma once

class C_GameScene;

class C_ObjectBase {

public:
	enum class ObjectType {
		None,
		Player,
		Enemy,
		Boss,
		MyBullet,
		EnemyBullet,
		Mp
	};

	C_ObjectBase();
	virtual ~C_ObjectBase() { Release(); }
	virtual void Init();
	virtual void Update();
	virtual void Draw();

	virtual void Reset();

	int GetFlag() { return Flag; }
	void SetFlag(int flag) { Flag = flag; }
	Math::Vector2 GetPos() { return Pos; }
	void SetPos(Math::Vector2 pos) { Pos = pos; }
	float GetHitRadius() { return HitRadius; }
	float GetRadius() { return Radius; }
	void SetOwner(C_GameScene* owner) { m_owner = owner; }
	ObjectType GetObjType() { return m_objType; }
	int GetObjDamage() { return Damage; }

	virtual void Hit(int damage) { ; }
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
	int Damage;				//与えるダメージ
	float Angle;
	KdTexture Tex;
	C_GameScene* m_owner;
	ObjectType m_objType= ObjectType::None;
private:
	virtual void Release();
};
