#include "GameScene.h"
#include "time.h"
#include "../../Chara/Player.h"
#include "../../Chara/Enemy/Enemy.h"
#include "../../Chara/Boss/Boss.h"
#include "../../Bullet/Mybullet.h"
#include "../SceneManager.h"
#define rep(i,N) for(int i=0;i<N;i++)
//プログラムを打つときは半角英数字で
//コメントを打つ時は行の頭にスラッシュ２つ
//1秒間に60回実行される(60FPSの場合)
C_GameScene::~C_GameScene()
{
	backTex1.Release();
	backTex2.Release();
	expTex.Release();
}
void C_GameScene::Draw2D()
{
	//背景
	SHADER.m_spriteShader.SetMatrix(backMat1);
	SHADER.m_spriteShader.DrawTex(&backTex1, Math::Rectangle{ 0, 0, 1280, 720 }, 1.0f);
	SHADER.m_spriteShader.SetMatrix(backMat2);
	SHADER.m_spriteShader.DrawTex(&backTex2, Math::Rectangle{ 0, 0, 1280, 720 }, 1.0f);

	if (m_player) {
		m_player->Draw();
	}

	rep(en, enemynum) {
		if(m_enemy[en]) {
			m_enemy[en]->Draw();
		}
	}

	if (m_boss) {
		m_boss->Draw();
	}

	rep(ex, expnum) {
		SHADER.m_spriteShader.SetMatrix(expMat[ex]);
		if (expFlag[ex])SHADER.m_spriteShader.DrawTex(&expTex, Math::Rectangle{ (int)(expAnimCnt[ex]) * 64, 0, 64, 64 }, 1.0f);
	}


	rep(bu, mybulletnum) {
		if (m_mybullet[bu]) {
			m_mybullet[bu]->Draw();
		}

	}

	char text[200];
	sprintf_s(text, sizeof(text), "Score %d", score);
	SHADER.m_spriteShader.DrawString(-608, 328, text, Math::Vector4(1, 1, 0, 1));
	if (!m_player)SHADER.m_spriteShader.DrawString(0, 0, "GAMEOVER", Math::Vector4(1, 1, 0, 1));\
}

//1秒間に60回実行される(60FPSの場合)
void C_GameScene::Update()
{
	if (m_player) {
		m_player->Update();
	}
	rep(en, enemynum) {
		if(m_enemy[en]){
			m_enemy[en]->Update();
		}
	}
	/*if (playerFlag == 1) {
		
		//↑プレイヤーの操作

		rep(en, enemynum) {
			if (enemyFlag[en] == 1) {
				if (IS_HIT(playerX, playerY, enemyX[en], enemyY[en], playerRadius + enemyRadius[en])) {
					playerHP -= 10;
					enemyFlag[en] = 0;
					Explosion(playerX, playerY);
				}
			}
		}
		if (bossFlag == 1) {
			if (IS_HIT(playerX, playerY, bossX, bossY, bossRadius + playerRadius)) {
				playerHP = 0;
				Explosion(playerX, playerY);
			}
		}
		//プレイヤーの死亡判定
		if (playerHP == 0) {
			playerFlag = 0;
		}
		playerAnimCnt++;
		if (playerAnimCnt == 4)playerAnimCnt = 0;
	}*/

	shotWait--;
	if (shotWait < 0)shotWait = 0;
	rep(ex, expnum) {
		if (expFlag[ex] == 1) expAnimCnt[ex] += 0.5f;
		if (expAnimCnt[ex] == 8) {
			expFlag[ex] = 0;
			expAnimCnt[ex] = 0;
		}
	}
	//爆発アニメーション

	//敵の撃破
	//rep(en, enemynum) {
	//	rep(bu, mybulletnum) {
	//		if (mybulletFlag[bu] != 0 && enemyFlag[en] != 0) {
	//			if (IS_HIT(enemyX[en], enemyY[en], mybulletX[bu], mybulletY[bu], enemyRadius[en] + mybulletRadius[bu])) {
	//				switch (mybulletFlag[bu]) {
	//				case 1:
	//					enemyHP[en]--;
	//				}
	//				mybulletFlag[bu] = 0;
	//				mybulletY[bu] = 456;
	//			}
	//		}
	//	}

	//}

	//敵の復活
	//if (rand() % 100 < 2) {
	//	rep(en, enemynum) {
	//		if (enemyFlag[en] == 0) {
	//			enemyX[en] = 608;
	//			enemyY[en] = rand() % 655 - 328;
	//			enemyFlag[en] = 1;
	//			enemyspeedX[en] = -1;
	//			enemyspeedY[en] = 0;
	//			enemySize[en] = 1.0f;
	//			enemyRadius[en] = 32.0f;
	//			enemyTimer[en] = 0;
	//			//Flagによって変えたい
	//			switch (enemyFlag[en]) {
	//			case 1:
	//				enemyHP[en] = 3;
	//				break;
	//			}				
	//			break;
	//		}
	//	}
	//}


	if (GetAsyncKeyState(VK_RETURN) & 0x8000) RESET();//関数宣言したらALT+Enterで関数定義

	if (backY1 < -717)backY1 = 717;
	if (backY2 < -717)backY2 = 717;
	backY1 -= 3;
	backY2 -= 3;

	rep(bu, mybulletnum) {
		if (m_mybullet[bu]) {
			m_mybullet[bu]->Update();
		}
	}


	//ボスの処理
	//if (score >= 50 && !bossFlag) bossFlag = 1;
	m_boss->Update();

	
	rep(bu, enemybulletnum) {
		if (enemybulletFlag[bu] != 0) {
			enemybulletTimer[bu]++;
		}
	}

	//↓Updateの最後に行列作成↓↓
	
	
	backMat1 = Math::Matrix::CreateTranslation(0, backY1, 0);
	backMat2 = Math::Matrix::CreateTranslation(0, backY2, 0);
	rep(bu, enemybulletnum) {
		Math::Matrix trans = Math::Matrix::CreateTranslation(enemybulletX[bu], (int)(enemybulletY[bu]), 0);
		Math::Matrix scale = Math::Matrix::CreateScale(enemybulletSize[bu], enemybulletSize[bu], 0);
		Math::Matrix rotate = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(enemybulletAngle[bu]));
		enemybulletMat[bu] = scale * rotate * trans;
	}
	
	rep(ex, expnum) expMat[ex] = Math::Matrix::CreateTranslation(expX[ex], expY[ex], 0);
}

//ゲーム開始時のみ実行される
void C_GameScene::Init()
{
	// 画像の読み込み処理
	
	backTex1.Load("Texture/back.png");
	backTex2.Load("Texture/back.png");
	enemybulletTex.Load("Texture/bullet.png");
	expTex.Load("Texture/explosion.png");
	backY1 = 0;
	backY2 = 720;

	m_player = std::make_shared<C_Player>();
	m_player->Init();
	m_player->SetOwner(this);
	rep(en,enemynum)
	{
		m_enemy[en] = std::make_shared<C_Enemy>();
		m_enemy[en]->Init();
	}

	m_boss = std::make_shared<C_Boss>();
	m_boss->Init();

	rep(bu, mybulletnum) {
		m_mybullet[bu] = std::make_shared<C_MyBullet>();
		m_mybullet[bu]->Init();
		m_mybullet[bu]->SetOwner(this);
	}

	rep(bu, enemybulletnum) {
		enemybulletX[bu] = 0;
		enemybulletY[bu] = 0;
		enemybulletspeedX[bu] = 0;
		enemybulletspeedY[bu] = 0;
		enemybulletSize[bu] = 1.0f;
		enemybulletRadius[bu] = 8.0f;
		enemybulletFlag[bu] = 0;
		enemybulletTimer[bu] = 0;
	}

	bucount = 0;
	shotWait = 0;
	//弾の初期設定
	srand(time(0));
	rand();

	//敵の初期設定
	score = 0;
	rep(ex, expnum) {
		expX[ex] = 0;
		expY[ex] = 0;
		expFlag[ex] = 0;
		expAnimCnt[ex] = 0;
	}
	//爆発の初期設定
}
//ゲーム終了時のみ実行される
void C_GameScene::Release()
{
	// 画像の解放処理
	backTex1.Release();
	backTex2.Release();
	expTex.Release();
}



void C_GameScene::RESET()
{
	if(m_player){
		m_player->Reset();
	}
	rep(en,enemynum)
	{
		if(m_enemy[en]) {
			m_enemy[en]->Reset();
		}
	}
	rep(bu, mybulletnum) {
		if (m_mybullet[bu]) {
			m_mybullet[bu]->Reset();
		}
	}

	rep(bu, enemybulletnum) {
		enemybulletX[bu] = 0;
		enemybulletY[bu] = 0;
		enemybulletspeedX[bu] = 0;
		enemybulletspeedY[bu] = 0;
		enemybulletFlag[bu] = 0;
		enemybulletTimer[bu] = 0;
	}

	if (m_boss) {
		m_boss->Reset();
	}
	
	rep(ex, expnum)expFlag[ex] = 0;
	score = 0;
}

void C_GameScene::Explosion(float x, float y)
{
	int ex = 0;
	while (expFlag[ex])ex++;
	expX[ex] = x;
	expY[ex] = y;
	expFlag[ex] = 1;
}

int C_GameScene::IS_HIT(float aX, float aY, float bX, float bY, float r)
{
	float a = aX - bX;
	float b = aY - bY;
	float c = sqrt(a * a + b * b);
	if (c < r) return 1;
	else return 0;
}

void C_GameScene::ShotMyBullet(float playerX,float playerY)
{
	rep(bu,mybulletnum)
	{
		if(!m_mybullet[bu]->GetFlag()){
			m_mybullet[bu]->Shot(playerX,playerY);
			break;
		}
	}
}
