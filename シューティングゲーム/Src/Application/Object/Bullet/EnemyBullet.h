#pragma once
#include "../ObjectBase.h"
class C_ObjectBase;
class C_GameScene;
class C_EnemyBullet :public C_ObjectBase {
private:
	C_GameScene* m_owner;
	void Release()override;
public:

	C_EnemyBullet();
	~C_EnemyBullet()override;
	void Init()override;
	void Update()override;
	void Draw()override;
	void Reset()override;

	void Shot(Math::Vector2 enemyPos, int flag);
	void Hit();
	void SetOwner(C_GameScene* owner) { m_owner = owner; }
};