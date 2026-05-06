#pragma once

#include "../BaseScene.h"

class Scene;
class C_ObjectBase;

struct enemywait {
	Math::Vector2 pos;
	int flag;
	int timer;
};

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

	bool BossFlag = false;
	static const int enemynum = 1;		
	enemywait enemywaiting[enemynum] ;
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

	int nowtime;
	int shotWait;	//弾のインターバル
	int score;		//スコア
	std::vector<std::shared_ptr<C_ObjectBase>> m_objList;
	
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

	void EnemyShot(Math::Vector2 EnemyPos, int flag);
	void EnemySpreadShot(Math::Vector2 EnemyPos, int flag);
	void EnemySnipeShot(Math::Vector2 EnemyPos, Math::Vector2 playerPos, int flag);
	void PlayerShot(Math::Vector2 PlayerPos, int flag);
	void AddScore(int AddScore) { score += AddScore; }
	void DropMP(Math::Vector2 Pos,int drop);
	std::vector<std::shared_ptr<C_ObjectBase>> GetObjList() {
		return m_objList;
	}
	
	void LoadEnemy();
};