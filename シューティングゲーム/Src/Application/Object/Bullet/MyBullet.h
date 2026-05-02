#pragma once
#include "../ObjectBase.h"
class C_ObjectBase;
class C_GameScene;
class C_MyBullet :public C_ObjectBase {
private:
	C_GameScene* m_owner;
	void Release();
public:

	C_MyBullet();
	~C_MyBullet();
	void Init();
	void Update();
	void Draw();
	void Reset();

	void Shot(Math::Vector2 playerPos, int flag);
	void Hit();
	void SetOwner(C_GameScene* owner) { m_owner = owner; }
};