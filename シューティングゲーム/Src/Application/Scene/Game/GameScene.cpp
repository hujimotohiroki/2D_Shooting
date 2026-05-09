#include "GameScene.h"
#include "time.h"
#include "../../Object/Chara/Player/Player.h"
#include "../../Object/Chara/Enemy/Enemy.h"
#include "../../Object/Chara/Boss/Boss.h"
#include "../../Object/Bullet/Mybullet.h"
#include "../../Object/Bullet/Enemybullet.h"
#include "../../Object/Bullet/Mp.h"
#include "../SceneManager.h"
#define rep(i,N) for(int i=0;i<N;i++)
//プログラムを打つときは半角英数字で
//コメントを打つ時は行の頭にスラッシュ２つ
//1秒間に60回実行される(60FPSの場合)
C_GameScene::~C_GameScene()
{
	backTex1.Release();
	backTex2.Release();
	farTex1.Release();
	farTex2.Release();
	expTex.Release();
}
void C_GameScene::Draw2D()
{
	//背景
	SHADER.m_spriteShader.SetMatrix(backMat1);
	SHADER.m_spriteShader.DrawTex(&backTex1, Math::Rectangle{ 0, 0, 1280, 720 }, 1.0f);
	SHADER.m_spriteShader.SetMatrix(backMat2);
	SHADER.m_spriteShader.DrawTex(&backTex2, Math::Rectangle{ 0, 0, 1280, 720 }, 1.0f);
	SHADER.m_spriteShader.SetMatrix(farMat1);
	SHADER.m_spriteShader.DrawTex(&farTex1, Math::Rectangle{ 0, 0, 1280, 720 }, 1.0f);
	SHADER.m_spriteShader.SetMatrix(farMat2);
	SHADER.m_spriteShader.DrawTex(&farTex2, Math::Rectangle{ 0, 0, 1280, 720 }, 1.0f);

	rep(i,m_objList.size()) {
		m_objList[i]->Draw();
	}

	rep(ex, expnum) {
		SHADER.m_spriteShader.SetMatrix(expMat[ex]);
		if (expFlag[ex])SHADER.m_spriteShader.DrawTex(&expTex, Math::Rectangle{ (int)(expAnimCnt[ex]) * 64, 0, 64, 64 }, 1.0f);
	}

	char text[200];
	sprintf_s(text, sizeof(text), "Score %d", m_objList.size());
	SHADER.m_spriteShader.DrawString(-608, 328, text, Math::Vector4(1, 1, 0, 1));
	//if (!m_player)SHADER.m_spriteShader.DrawString(0, 0, "GAMEOVER", Math::Vector4(1, 1, 0, 1));
}

//1秒間に60回実行される(60FPSの場合)
void C_GameScene::Update()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000) RESET();//関数宣言したらALT+Enterで関数定義
	for (int en = nowenemy; en < enemynum;en++) {
		if (nowtime >enemywaiting[en].timer){
			std::shared_ptr<C_Enemy> m_enemy;
			m_enemy = std::make_shared<C_Enemy>();
			m_enemy->Init();
			m_enemy->SetOwner(this);
			m_enemy->SetPos(enemywaiting[en].pos);
			m_enemy->SetHP(enemywaiting[en].hp);
			m_enemy->SetFlag(enemywaiting[en].flag);
			m_objList.push_back(m_enemy);
			nowenemy++;
		}
	}
	if (score > 0 && !BossFlag) {
		std::shared_ptr<C_Boss> m_boss;
		m_boss = std::make_shared<C_Boss>();
		m_boss->Init();
		m_boss->SetOwner(this);
		m_boss->SetFlag(1);
		m_objList.push_back(m_boss);
		BossFlag = true;
	}
	//使い終わった弾や敵(Flag=0)を消すのを忘れないように
	rep (i,m_objList.size()) {
		m_objList[i]->Update();
		if (m_objList[i]->GetFlag() == 0) {
			m_objList.erase(m_objList.begin() + i);
			i--;
		}
	}
	

	shotWait--;
	if (shotWait < 0)shotWait = 0;
	rep(ex, expnum) {
		if (expFlag[ex] == 1) expAnimCnt[ex] += 0.5f;
		if (expAnimCnt[ex] == 8) {
			expFlag[ex] = 0;
			expAnimCnt[ex] = 0;
		}
	}

	if (backX1 < -1277)backX1 = 1277;
	if (backX2 < -1277)backX2 = 1277;
	backX1 -= 3;
	backX2 -= 3;
	if (farX1 < -1277)farX1 = 1277;
	if (farX2 < -1277)farX2 = 1277;
	farX1 -= 3;
	farX2 -= 3;

	nowtime++;

	//↓Updateの最後に行列作成↓↓
	backMat1 = Math::Matrix::CreateTranslation(backX1,0, 0);
	backMat2 = Math::Matrix::CreateTranslation(backX2,0, 0);
	farMat1 = Math::Matrix::CreateTranslation(farX1,0, 0);
	farMat2 = Math::Matrix::CreateTranslation(farX2,0, 0);
	
	rep(ex, expnum) expMat[ex] = Math::Matrix::CreateTranslation(expX[ex], expY[ex], 0);
}

//ゲーム開始時のみ実行される
void C_GameScene::Init()
{
	// 画像の読み込み処理
	
	backTex1.Load("Texture/back.png");
	backTex2.Load("Texture/back.png");
	farTex1.Load("Texture/far.png");
	farTex2.Load("Texture/far.png");
	expTex.Load("Texture/explosion.png");
	backX1 = 0;
	backX2 = 1277;
	farX1 = 0;
	farX2 = 1277;

	{
		std::shared_ptr<C_Player> m_player;
		m_player = std::make_shared<C_Player>();
		m_player->Init();
		m_player->SetOwner(this);
		m_objList.push_back(m_player);
	}
	LoadEnemy();
	nowenemy = 0;
	nowtime = 0;
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

}



void C_GameScene::RESET()
{
	m_objList.clear();

	BossFlag = false;
	{
		std::shared_ptr<C_Player> m_player;
		m_player = std::make_shared<C_Player>();
		m_player->Init();
		m_player->SetOwner(this);
		m_objList.push_back(m_player);
	}

	nowenemy = 0;
	nowtime = 0;
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

void C_GameScene::Explosion(float x, float y)
{
	int ex = 0;
	while (expFlag[ex])ex++;
	expX[ex] = x;
	expY[ex] = y;
	expFlag[ex] = 1;
}


void C_GameScene::EnemyShot(Math::Vector2 EnemyPos, int flag)
{
	std::shared_ptr<C_EnemyBullet> enemybullet;
	enemybullet = std::make_shared<C_EnemyBullet>();
	enemybullet->Init();
	enemybullet->SetOwner(this);
	enemybullet->SetPos(EnemyPos);
	enemybullet->SetSpeed({-1,0});
	enemybullet->SetFlag(flag);
	m_objList.push_back(enemybullet);
}

void C_GameScene::EnemySpreadShot(Math::Vector2 EnemyPos, int flag)
{
	std::shared_ptr<C_EnemyBullet> enemybullet;
	enemybullet = std::make_shared<C_EnemyBullet>();
	enemybullet->Init();
	enemybullet->SetOwner(this);
	enemybullet->SetPos(EnemyPos);
	Math::Vector2 enemyMove;
	enemyMove.x = std::cos(DirectX::XMConvertToRadians(rand() % 91 + 135));
	enemyMove.y = std::sin(DirectX::XMConvertToRadians(rand() % 91 + 135));
	enemyMove.Normalize();
	enemybullet->SetSpeed(enemyMove);
	enemybullet->SetFlag(flag);
	m_objList.push_back(enemybullet);
}

void C_GameScene::EnemySnipeShot(Math::Vector2 EnemyPos, Math::Vector2 PlayerPos, int flag)
{
	std::shared_ptr<C_EnemyBullet> enemybullet;
	enemybullet = std::make_shared<C_EnemyBullet>();
	enemybullet->Init();
	enemybullet->SetOwner(this);
	enemybullet->SetPos(EnemyPos);
	Math::Vector2 enemyMove = PlayerPos - EnemyPos;
	enemyMove.x;
	enemyMove.Normalize();
	enemybullet->SetSpeed(enemyMove);
	enemybullet->SetFlag(flag);
	m_objList.push_back(enemybullet);
}

void C_GameScene::PlayerShot(Math::Vector2 PlayerPos, int flag, float Radius, int hp, float size)
{
	std::shared_ptr<C_MyBullet> mybullet;
	mybullet = std::make_shared<C_MyBullet>();
	mybullet->Init();
	mybullet->SetOwner(this);
	mybullet->SetPos(PlayerPos);
	mybullet->SetSpeed({ 1,0 });
	mybullet->SetFlag(flag);
	mybullet->SetRadius(Radius);
	mybullet->SetHitRadius(Radius);
	mybullet->SetHp(hp);
	mybullet->SetMaxHp(hp);
	mybullet->SetSize(size);
	m_objList.push_back(mybullet);
}

void C_GameScene::DropMP(Math::Vector2 Pos,int drop)
{
	rep(i,drop){
		std::shared_ptr<C_Mp> mp;
		mp = std::make_shared<C_Mp>();
		mp->Init();
		mp->SetOwner(this);
		mp->SetPos(Pos);
		mp->SetSpeed({ -1,0 });
		m_objList.push_back(mp);
	}
}


void C_GameScene::LoadEnemy()
{
	FILE* fp;
	fp = fopen("stagedata/Stage1.txt", "r");
	if (fp != nullptr) {
		printf("\nファイルの読み込み成功\n");
		float x, y;
		int hp,flag,timer;
		for (int en = 0;en < enemynum;en++) {
			fscanf_s(fp, "%f,%f,%d,%d,%d\n", &x, &y,&hp,&flag,&timer);
			Math::Vector2 pos = { x,y };
			enemywaiting[en] = {pos,hp,flag,timer};
		}
		fclose(fp);
	}
	else {
		printf("\nファイルの読み込み失敗\n");
	}
}