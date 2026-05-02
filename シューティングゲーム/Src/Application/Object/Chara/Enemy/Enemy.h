#pragma once
#include"../../ObjectBase.h"
class C_ObjectBase;
class C_EnemyBullet;

class C_Enemy :public C_ObjectBase {
private:
	std::shared_ptr<C_EnemyBullet> m_enemybullet;
	void Release();
public:

	C_Enemy();
	~C_Enemy();
	void Init();
	void Update();
	void Draw();
	void Reset();

	void Hit(int damage);
	void Dead();
};