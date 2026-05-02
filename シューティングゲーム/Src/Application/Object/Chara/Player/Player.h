#pragma once
#include "../../ObjectBase.h"
class C_ObjectBase;
class C_MyBullet;


class C_Player : public C_ObjectBase  {
private:
	std::shared_ptr<C_MyBullet> m_mybullet;
	void Release() override;
	float mp;
	
public:

	C_Player();
	~C_Player()override;
	void Init()override;
	void Update()override;
	void Draw()override;
	void Reset()override;

	void Hit(int damage);
	void Dead();
	
};