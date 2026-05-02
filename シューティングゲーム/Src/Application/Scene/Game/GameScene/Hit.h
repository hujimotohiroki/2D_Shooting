#pragma once

class C_GameScene;
class C_Player;
class C_MyBullet;
class C_Enemy;
class C_EnemyBullet;
class C_Mp;

class C_Hit {
private:
	C_GameScene* m_owner;
	std::shared_ptr<C_Player> m_player;
	std::shared_ptr<C_MyBullet> m_mybullet;
	std::shared_ptr<C_Enemy> m_enemy;
	std::shared_ptr<C_EnemyBullet> m_enemybullet;
	std::shared_ptr<C_Mp> m_enemybullet;
	
public:
	C_Hit();
	~C_Hit() ;
	void Init();
	void Update();
	void Draw();
	bool CheckHit(Math::Vector2 A,Math::Vector2 B,float distance);

	void SetOwner(C_GameScene* owner) { m_owner = owner; }
};