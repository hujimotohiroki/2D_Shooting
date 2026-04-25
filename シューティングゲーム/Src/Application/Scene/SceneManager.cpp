#include "SceneManager.h"
#include "Game/GameScene.h"
#include "Title/TitleScene.h"
void SceneManager::PreUpdate()
{
	if (m_currentSceneType != m_nextSceneType) {
		ChangeScene(m_nextSceneType);
	}
}

void SceneManager::Update()
{
	m_currentScene->Update();
}

void SceneManager::Draw()
{
	m_currentScene->Draw2D();
}

void SceneManager::Init()
{
	ChangeScene(m_currentSceneType);
}

void SceneManager::Release()
{}

void SceneManager::ChangeScene(SceneType _sceneType)
{
	switch (_sceneType) {
	case SceneType::Title:
		m_currentScene = std::make_shared<C_TitleScene>();
		break;
	case SceneType::Game:
		m_currentScene = std::make_shared<C_GameScene>();
		break;
	}
	m_currentSceneType = _sceneType;
}
