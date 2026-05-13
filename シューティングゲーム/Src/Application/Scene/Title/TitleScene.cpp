#include "TitleScene.h"
#include "../SceneManager.h"
C_TitleScene::~C_TitleScene()
{}

void C_TitleScene::Init()
{
	backTex1.Load("Texture/back.png");
	backTex2.Load("Texture/back.png");
	farTex1.Load("Texture/far.png");
	farTex2.Load("Texture/far.png");
	titleTex.Load("Texture/Title/title.png");
	titleTex2.Load("Texture/Title/title2.png");
	keyTex.Load("Texture/UI/icons-keyboard-16x16-1bit-ansdor.png");
	backX1 = 0;
	backX2 = 1277;
	farX1 = 0;
	farX2 = 1277;
}

void C_TitleScene::Release()
{}

void C_TitleScene::Update()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
		SceneManager::Instance().SetNextScene(SceneManager::SceneType::Game);
	}
	backMat1 = Math::Matrix::CreateTranslation(backX1, 0, 0);
	backMat2 = Math::Matrix::CreateTranslation(backX2, 0, 0);
	farMat1 = Math::Matrix::CreateTranslation(farX1, 0, 0);
	farMat2 = Math::Matrix::CreateTranslation(farX2, 0, 0);
	Math::Matrix trans = Math::Matrix::CreateTranslation(0, 150, 0);
	Math::Matrix scale = Math::Matrix::CreateScale(2, 2, 0);
	titleMat = scale * trans;
	titleMat2 = Math::Matrix::CreateTranslation(0, -200, 0);
	trans = Math::Matrix::CreateTranslation(-50, -200, 0);
	scale = Math::Matrix::CreateScale(3, 3, 0);
	keyMat = scale * trans;
}

void C_TitleScene::Draw2D()
{
	SHADER.m_spriteShader.SetMatrix(backMat1);
	SHADER.m_spriteShader.DrawTex(&backTex1, Math::Rectangle{ 0, 0, 1280, 720 }, 1.0f);
	SHADER.m_spriteShader.SetMatrix(backMat2);
	SHADER.m_spriteShader.DrawTex(&backTex2, Math::Rectangle{ 0, 0, 1280, 720 }, 1.0f);
	SHADER.m_spriteShader.SetMatrix(farMat1);
	SHADER.m_spriteShader.DrawTex(&farTex1, Math::Rectangle{ 0, 0, 1280, 720 }, 1.0f);
	SHADER.m_spriteShader.SetMatrix(farMat2);
	SHADER.m_spriteShader.DrawTex(&farTex2, Math::Rectangle{ 0, 0, 1280, 720 }, 1.0f);
	
	SHADER.m_spriteShader.SetMatrix(titleMat);
	SHADER.m_spriteShader.DrawTex(&titleTex, Math::Rectangle{ 0, 0, 435, 72 }, 1.0f);
	SHADER.m_spriteShader.SetMatrix(titleMat2);
	SHADER.m_spriteShader.DrawTex(&titleTex2, Math::Rectangle{ 0, 0, 573, 83 }, 1.0f);
	SHADER.m_spriteShader.SetMatrix(keyMat);
	SHADER.m_spriteShader.DrawTex(&keyTex, Math::Rectangle{ 80, 64, 16, 16 }, 1.0f);
	
	if (backX1 < -1277)backX1 = 1277;
	if (backX2 < -1277)backX2 = 1277;
	backX1 -= 2;
	backX2 -= 2;
	if (farX1 < -1277)farX1 = 1277;
	if (farX2 < -1277)farX2 = 1277;
	farX1 -= 3;
	farX2 -= 3;
}
