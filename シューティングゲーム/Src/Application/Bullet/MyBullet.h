#pragma once
#include "BulletBase.h"
class C_BulletBase;
class C_GameScene;
class C_MyBullet :public C_BulletBase {
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

	int GetFlag() { return Flag;}
	void Shot(float playerX,float playerY);
	void SetOwner(C_GameScene* owner) { m_owner = owner; }
};