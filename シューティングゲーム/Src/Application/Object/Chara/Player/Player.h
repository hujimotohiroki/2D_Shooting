#pragma once
#include "../../ObjectBase.h"
class C_ObjectBase;
class C_MyBullet;


class C_Player : public C_ObjectBase  {
private:
	std::shared_ptr<C_MyBullet> m_mybullet;
	void Release();
	float mp;
	
public:

	C_Player();
	~C_Player();
	void Init();
	void Update();
	void Draw();
	void Reset();

	void Hit(int damage);
	void Dead();
	
};