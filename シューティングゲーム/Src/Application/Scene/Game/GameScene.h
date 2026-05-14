#pragma once

#include "../BaseScene.h"

class Scene;
class C_ObjectBase;

struct enemywait {
	Math::Vector2 pos;
	int hp;
	int flag;
	int timer;
};

class C_GameScene : public C_BaseScene
{
private:
	// テクスチャ ・・・ 画像データ
	
	KdTexture backTex1;
	KdTexture backTex2;
	KdTexture farTex1;
	KdTexture farTex2;
	KdTexture clearTex;
	KdTexture gameoverTex;
	KdTexture clearTex2;
	KdTexture gameoverTex2;
	KdTexture keyTex;
	KdTexture dangerTex;
	
	KdTexture expTex;

	bool BossFlag = false;
	bool playerFlag = false;
	static const int enemynum = 21;		
	enemywait enemywaiting[enemynum] ;
	//背景
	Math::Matrix backMat1;
	float backX1;
	Math::Matrix backMat2;
	float backX2;
	Math::Matrix farMat1;
	float farX1;
	Math::Matrix farMat2;
	float farX2;

	Math::Matrix clearMat;
	Math::Matrix gameoverMat;
	Math::Matrix clearMat2;
	Math::Matrix gameoverMat2;
	Math::Matrix keyMat;
	Math::Matrix dangerMat;

	//爆発の変数
	static const int expnum = enemynum + 2;	//総数（敵機の数+2[ボスと自機]）
	Math::Matrix expMat[expnum];			//座標回転拡縮を管理する行列
	float expX[expnum];						//X座標
	float expY[expnum];						//Y座標
	int expFlag[expnum];					//使用フラグ
	float expAnimCnt[expnum];				//爆発アニメの何コマ目か

	int bucount;	//敵機を倒した数

	int wall;

	int ClearTimer;

	int nowenemy;
	int nowtime;
	int shotWait;	//弾のインターバル
	int score;		//スコア

	bool clearflag;
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

	void EnemyShot(Math::Vector2 EnemyPos, int flag,int angle);
	void EnemySpreadShot(Math::Vector2 EnemyPos, int flag);
	void EnemySnipeShot(Math::Vector2 EnemyPos, Math::Vector2 playerPos, int flag);
	void PlayerShot(Math::Vector2 PlayerPos, int flag, float Radius, int hp, float size,int angle);
	
	void SummonEnemy(int Hp, int flag);
	void AddScore(int AddScore) { score += AddScore; }
	void DropMP(Math::Vector2 Pos,int drop);
	std::vector<std::shared_ptr<C_ObjectBase>> GetObjList() {
		return m_objList;
	}
	void SetPlayerFlag(bool flag) { playerFlag = flag; }
	void SetBossFlag(bool flag);
	int GetWall() { return wall; }
	void SetWall(int Wall) { wall = Wall; }
	void SpawnWall(int wall);
	bool GetClearFlag(){ return clearflag; }
};