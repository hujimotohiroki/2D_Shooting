#pragma once

class C_GameScene;

class C_Hit {
private:
	C_GameScene* m_owner;
public:
	C_Hit();
	~C_Hit() ;
	void Init();
	void Update();
	void Draw();
	void SetOwner(C_GameScene* owner) { m_owner = owner; }
};