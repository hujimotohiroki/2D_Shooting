#pragma once
#include"../../ObjectBase.h"
class C_ObjectBase;
class C_EnemyBullet;

class C_Enemy :public C_ObjectBase {
private:
	std::shared_ptr<C_EnemyBullet> m_enemybullet;
	void Release()override;
public:

	C_Enemy();
	~C_Enemy()override;
	void Init()override;
	void Update()override;
	void Draw()override;
	void Reset()override;

	void Hit(int damage);
	void Dead();
};