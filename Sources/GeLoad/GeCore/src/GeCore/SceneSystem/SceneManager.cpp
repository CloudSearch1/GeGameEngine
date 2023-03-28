#include <GeUtils/Filesystem/tinyxml2.h>
#include <GeWindow/Dialogs/MessageBox.h>

#include "GeCore/SceneSystem/SceneManager.h"
#include "GeCore/ECS/Components/CDirectionalLight.h"
#include "GeCore/ECS/Components/CAmbientSphereLight.h"
#include "GeCore/ECS/Components/CCamera.h"

GeCore::SceneSystem::SceneManager::SceneManager(const std::string& p_sceneRootFolder) : m_sceneRootFolder(p_sceneRootFolder)
{
	LoadEmptyScene();
}

GeCore::SceneSystem::SceneManager::~SceneManager()
{
	UnloadCurrentScene();
}

void GeCore::SceneSystem::SceneManager::Update()
{
	if (m_delayedLoadCall)
	{
		m_delayedLoadCall();
		m_delayedLoadCall = 0;
	}
}

void GeCore::SceneSystem::SceneManager::LoadAndPlayDelayed(const std::string& p_path, bool p_absolute)
{
	m_delayedLoadCall = [this, p_path, p_absolute]
	{
		std::string previousSourcePath = GetCurrentSceneSourcePath();
		LoadScene(p_path, p_absolute);
		StoreCurrentSceneSourcePath(previousSourcePath);
		GetCurrentScene()->Play();
	};
}

void GeCore::SceneSystem::SceneManager::LoadEmptyScene()
{
	UnloadCurrentScene();

	m_currentScene = new Scene();

	SceneLoadEvent.Invoke();
}

void GeCore::SceneSystem::SceneManager::LoadEmptyLightedScene()
{
	UnloadCurrentScene();

	m_currentScene = new Scene();

	SceneLoadEvent.Invoke();

	auto& directionalLight = m_currentScene->CreateActor("Directional Light");
	directionalLight.AddComponent<ECS::Components::CDirectionalLight>().SetIntensity(0.75f);
	directionalLight.transform.SetLocalPosition({ 0.0f, 10.0f, 0.0f });
	directionalLight.transform.SetLocalRotation(GeMaths::FQuaternion({ 120.0f, -40.0f, 0.0f }));

	auto& ambientLight = m_currentScene->CreateActor("Ambient Light");
	ambientLight.AddComponent<ECS::Components::CAmbientSphereLight>().SetRadius(10000.0f);

	auto& camera = m_currentScene->CreateActor("Main Camera");
	camera.AddComponent<ECS::Components::CCamera>();
	camera.transform.SetLocalPosition({ 0.0f, 3.0f, 8.0f });
	camera.transform.SetLocalRotation(GeMaths::FQuaternion({ 20.0f, 180.0f, 0.0f }));
}

bool GeCore::SceneSystem::SceneManager::LoadScene(const std::string& p_path, bool p_absolute)
{
	std::string completePath = (p_absolute ? "" : m_sceneRootFolder) + p_path;

	tinyxml2::XMLDocument doc;
	doc.LoadFile(completePath.c_str());

	if (LoadSceneFromMemory(doc))
	{
		StoreCurrentSceneSourcePath(completePath);
		return true;
	}

	return false;
}

bool GeCore::SceneSystem::SceneManager::LoadSceneFromMemory(tinyxml2::XMLDocument& p_doc)
{
	if (!p_doc.Error())
	{
		tinyxml2::XMLNode* root = p_doc.FirstChild();
		if (root)
		{
			tinyxml2::XMLNode* sceneNode = root->FirstChildElement("scene");
			if (sceneNode)
			{
				LoadEmptyScene();
				m_currentScene->OnDeserialize(p_doc, sceneNode);
				return true;
			}
		}
	}

	GeWindow::Dialogs::MessageBox message("Scene loading failed", "The scene you are trying to load was not found or corrupted", GeWindow::Dialogs::MessageBox::EMessageType::ERROR, GeWindow::Dialogs::MessageBox::EButtonLayout::OK, true);
	return false;
}

void GeCore::SceneSystem::SceneManager::UnloadCurrentScene()
{
	if (m_currentScene)
	{
		delete m_currentScene;
		m_currentScene = nullptr;
		SceneUnloadEvent.Invoke();
	}

	ForgetCurrentSceneSourcePath();
}

bool GeCore::SceneSystem::SceneManager::HasCurrentScene() const
{
	return m_currentScene;
}

GeCore::SceneSystem::Scene* GeCore::SceneSystem::SceneManager::GetCurrentScene()
{
	return m_currentScene;
}

std::string GeCore::SceneSystem::SceneManager::GetCurrentSceneSourcePath() const
{
	return m_currentSceneSourcePath;
}

bool GeCore::SceneSystem::SceneManager::IsCurrentSceneLoadedFromDisk() const
{
	return m_currentSceneLoadedFromPath;
}

void GeCore::SceneSystem::SceneManager::StoreCurrentSceneSourcePath(const std::string& p_path)
{
	m_currentSceneSourcePath = p_path;
	m_currentSceneLoadedFromPath = true;
	CurrentSceneSourcePathChangedEvent.Invoke(m_currentSceneSourcePath);
}

void GeCore::SceneSystem::SceneManager::ForgetCurrentSceneSourcePath()
{
	m_currentSceneSourcePath = "";
	m_currentSceneLoadedFromPath = false;
	CurrentSceneSourcePathChangedEvent.Invoke(m_currentSceneSourcePath);
}
