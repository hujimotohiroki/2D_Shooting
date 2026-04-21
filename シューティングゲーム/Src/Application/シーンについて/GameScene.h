#pragma once

class Scene;

class C_GameScene
{
private:

	// テクスチャ ・・・ 画像データ
	KdTexture charaTex;
	KdTexture backTex1;
	KdTexture backTex2;
	KdTexture enemyTex;
	KdTexture mybulletTex;
	KdTexture enemybulletTex;
	KdTexture expTex;

	//プレイヤー(自機)の変数
	Math::Matrix charaMat; //行列、座標・回転・拡縮を管理
	float playerX;			//X座標
	float playerY;			//Y座標
	float playerAnimCnt;	//どのアニメーションか
	float playerSize;		//大きさの倍率
	float playerRadius;		//半径何ドットで描写するか
	int playerFlag;			//生存フラグ
	int playerHP;			//体力

	//弾（自分の）の変数
	static const int mybulletnum = 30;	//最大表示数
	Math::Matrix mybulletMat[mybulletnum];	//座標回転拡縮を管理する行列
	float mybulletX[mybulletnum];			//X座標
	float mybulletY[mybulletnum];			//Y座標
	float mybulletspeedX[mybulletnum];		//X速度
	float mybulletspeedY[mybulletnum];		//Y速度
	float mybulletSize[mybulletnum];		//大きさの倍率
	float mybulletRadius[mybulletnum];		//半径何ドットで描写するか
	float mybulletAngle[mybulletnum];		//角度
	int mybulletFlag[mybulletnum];			//画面上に存在しているか
	int mybulletTimer[mybulletnum];			//発射されてからの時間

	//弾（敵機の）の変数
	static const int enemybulletnum = 100;	//最大表示数
	Math::Matrix enemybulletMat[enemybulletnum];	//座標回転拡縮を管理する行列
	float enemybulletX[enemybulletnum];				//X座標
	float enemybulletY[enemybulletnum];				//Y座標
	float enemybulletspeedX[enemybulletnum];		//X速度
	float enemybulletspeedY[enemybulletnum];		//Y速度
	float enemybulletSize[enemybulletnum];			//大きさの倍率
	float enemybulletAngle[enemybulletnum];			//角度
	float enemybulletRadius[enemybulletnum];		//半径何ドットで描写するか
	int enemybulletFlag[enemybulletnum];			//画面上に存在しているか
	int enemybulletTimer[enemybulletnum];			//発射されてからの時間

	//敵機の変数
	static const int enemynum = 10;		//総数
	Math::Matrix enemyMat[enemynum];	//座標回転拡縮を管理する行列
	float enemyX[enemynum];				//X座標
	float enemyY[enemynum];				//Y座標
	int enemyspeedX[enemynum];			//X速度
	int enemyspeedY[enemynum];			//X速度
	float enemySize[enemynum];			//大きさの倍率
	float enemyRadius[enemynum];		//半径何ドットで描写するか
	int enemyFlag[enemynum];			//生存フラグ
	int enemyTimer[enemynum];			//登場してからの時間
	int enemyHP[enemynum];				//体力

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

	//ボスの変数
	Math::Matrix bossMat;	//座標回転拡縮を管理する行列
	float bossSize;			//大きさの倍率
	float bossX;			//X座標
	float bossY;			//Y座標
	int bossFlag;			//生存フラグ
	float bossRadius;		//半径何ドットで描写するか
	float bossAngle;		//角度
	int bossHP;				//HP
	int bossTimer;			//出現からの時間

	int bucount;	//敵機を倒した数

	int shotWait;	//弾のインターバル
	int score;		//スコア

protected:
	Scene* m_owner;
public:

	~C_GameScene();
	// 初期設定
	void Init();

	// 解放
	void Release();

	// 更新処理
	void Update();

	// 描画処理
	void Draw2D();


	void RESET();

	void Explosion(float x, float y);

	int IS_HIT(float aX, float aY, float bX, float bY, float l);

};