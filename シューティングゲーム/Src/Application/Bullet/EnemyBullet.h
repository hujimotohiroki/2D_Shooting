#pragma once
#include "BulletBase.h"
class C_BulletBase;
class C_GameScene;
class C_EnemyBullet :public C_BulletBase {
private:
	C_GameScene* m_owner;
	void Release();
public:

	C_EnemyBullet();
	~C_EnemyBullet();
	void Init();
	void Update();
	void Draw();
	void Reset();

	void Hit();
	void SetOwner(C_GameScene* owner) { m_owner = owner; }
};