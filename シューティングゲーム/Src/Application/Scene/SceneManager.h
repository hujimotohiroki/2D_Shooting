#pragma once

class C_BaseScene;

class SceneManager {
public:
	enum SceneType {
		Title,
		Game
	};
	void PreUpdate();
	void Update();
	void Draw();
	void SetNextScene(SceneType _nextScene) {
		m_nextSceneType = _nextScene;
	}
	SceneType GetCurrentScene() const {
		return m_currentSceneType;
	}
private:
	void Init();
	void Release();
	void ChangeScene(SceneType _sceneType);

	std::shared_ptr<C_BaseScene> m_currentScene;

	SceneType m_currentSceneType = SceneType::Title;
	SceneType m_nextSceneType = m_currentSceneType;
private:
	SceneManager() { Init(); }
	~SceneManager() { Release(); }
public:
	static SceneManager& Instance() {
		static SceneManager instance;
		return instance;
	}
};