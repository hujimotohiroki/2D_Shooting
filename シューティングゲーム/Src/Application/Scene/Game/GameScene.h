#pragma once

#include "../BaseScene.h"

class Scene;
class C_Player;
class C_Enemy;
class C_Boss;
class C_MyBullet;
class C_EnemyBullet;
class C_Hit;
class C_Mp;

class C_GameScene : public C_BaseScene
{
private:

	// テクスチャ ・・・ 画像データ
	
	KdTexture backTex1;
	KdTexture backTex2;
	KdTexture enemyTex;
	KdTexture mybulletTex;
	KdTexture enemybulletTex;
	KdTexture expTex;

	std::shared_ptr<C_Player> m_player;

	static const int enemynum = 10;		//総数
	std::shared_ptr<C_Enemy> m_enemy[enemynum];

	std::shared_ptr<C_Boss> m_boss;


	//弾（自分の）の変数
	static const int mybulletnum = 30;	//最大表示数
	std::shared_ptr<C_MyBullet> m_mybullet[mybulletnum];



	//弾（敵機の）の変数
	static const int enemybulletnum = 1000;	//最大表示数
	std::shared_ptr<C_EnemyBullet> m_enemybullet[enemybulletnum];
	
	std::shared_ptr<C_Hit>m_hit;

	//背景
	Math::Matrix backMat1;
	float backY1;
	Math::Matrix backMat2;
	float backY2;

	//爆発の変数
	static const int expnum = enemynum + 2;	//総数（敵機の数+2[ボスと自機]）
	Math::Matrix expMat[expnum];			//座標回転拡縮を管理する行列
	float expX[expnum];						//X座標
	float expY[expnum];						//Y座標
	int expFlag[expnum];					//使用フラグ
	float expAnimCnt[expnum];				//爆発アニメの何コマ目か

	int bucount;	//敵機を倒した数

	int shotWait;	//弾のインターバル
	int score;		//スコア

protected:
	Scene* m_owner;
public:
	C_GameScene() { Init(); }
	~C_GameScene();
	// 初期設定
	void Init() override;

	// 解放
	void Release()override;

	// 更新処理
	void Update()override;

	// 描画処理
	void Draw2D()override;


	void RESET();

	void Explosion(float x, float y);

	int IS_HIT(float aX, float aY, float bX, float bY, float l);

	void AddScore(int AddScore) { score += AddScore; }
	void DropMP(Math::Vector2 Pos);


	std::shared_ptr<C_Player> GetPlayer();
	std::shared_ptr<C_Enemy> GetEnemy(int en);
	std::shared_ptr<C_MyBullet> GetMyBullet(int bu);
	std::shared_ptr<C_EnemyBullet> GetEnemyBullet(int bu);
	std::shared_ptr<C_Mp> GetMp(int bu);
};