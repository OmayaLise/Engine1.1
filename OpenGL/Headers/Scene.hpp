#pragma once

#include <GLFW/glfw3.h>
#include <glad/glad.h>

// Resources
#include "IResource.hpp"

// LowRenderer
#include "Camera.hpp"
#include "GameObject.hpp"
#include "LightManager.hpp"

// Physics
#include "PhysicManager.hpp"

//Editor

// DataStructure
#include "Graph.hpp"
#include "../Sources/InterfaceEditor.hpp"

namespace Resources
{
	enum class SceneType
	{
		ST_Game,
		ST_Menu,
		ST_Setting,
		ST_Credit,
	};

	struct NextScene
	{
		std::string name;
		SceneType sceneType;
	};

	class Scene : public IResource
	{
		// Attribute
	private:
		LowRenderer::Camera* camera;
		std::vector<LowRenderer::GameObject*> gameObjects;
		LowRenderer::LightManager lightManager;
		Core::DataStructure::Graph graph;
		Physics::PhysicsManager m_physicsManager;
		Core::Editor::InterfaceEditor m_editor;

	protected:
		unsigned int width;
		unsigned int height;

		// Methode
	public:
		Scene(const std::string& p_name, const std::string& p_path1, const std::string& p_path2, const unsigned int p_id);
		~Scene();

		void Init(const unsigned int p_width, const unsigned int p_height);
		virtual void Update(const Core::Inputs& p_Inputs, const double& p_deltaTime);
		virtual void Draw(const Core::Inputs& p_Inputs, std::chrono::duration<double>& elapsedMono, std::chrono::duration<double>& elapsedMulti);

		void AddGameObject(LowRenderer::GameObject* p_gameObject, LowRenderer::GOType p_type = LowRenderer::GOType::None);
		void AddDirectionLight(const LowRenderer::DirectionLight& p_light);
		void AddPointLight(const LowRenderer::PointLight& p_light);
		void AddSpotLight(const LowRenderer::SpotLight& p_light);

		Physics::Collider* CreateCollider(Resources::Mesh* p_mesh, Resources::Shader* p_shader, Physics::ColliderTypes types,bool isStatic);
		Physics::Collider* GetLastCollider() { return m_physicsManager.colliders[m_physicsManager.colliders.size()-1]; }

		bool SetParent(const std::string& p_nameParent, const std::string& p_nameChild) { return graph.SetParent(p_nameParent, p_nameChild); };
		void DrawTimer(std::chrono::duration<double>& elapsedMono, std::chrono::duration<double>& elapsedMulti);


	protected:
		void StartImGui() const;
		void EndImGui() const;
	
		void ReturnToMenu();
		void ShowQuit();
	};
}