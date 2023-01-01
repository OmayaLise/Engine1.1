#pragma once

#include <vector>

#include "GameObject.hpp"
#include "Camera.hpp"
#include "LightManager.hpp"

namespace Core::DataStructure
{
	int constexpr INVALID_INDEX = -1;

	struct GraphNode
	{
		int indexGameObject = INVALID_INDEX; // Index in gameObjects
		int parentIndex		= INVALID_INDEX; // Index in nodes
		std::vector<int> childsIndex;		 // Index in nodes
	};

	class Graph
	{
		// Attribure
	private:
		std::vector<GraphNode> nodes;
		std::vector<LowRenderer::GameObject*>* gameObjects;

		// Methode
	public:
		Graph(std::vector<LowRenderer::GameObject*>& p_gameObject);
		~Graph();

		void Update(const Core::Inputs& p_Inputs, const double p_deltaTime);
		void Draw(LowRenderer::Camera& p_camera, LowRenderer::LightManager& p_lightManager);

		void AddNode(int p_index);
		bool SetParent(const std::string& p_nameParent, const std::string& p_nameChild);

		std::vector<GraphNode>* GetNodes();
		LowRenderer::GameObject* GetGameObject(const unsigned int p_index);
		GraphNode& GetNode(const unsigned int p_index);

	private:
		void UpdateChild(const GraphNode& p_child, const Core::Inputs& p_Inputs, const double p_deltaTime);
		void DrawChild(LowRenderer::Camera& p_camera, LowRenderer::LightManager& p_lightManager, const GraphNode& p_child);
		
		bool ParentCheck(const unsigned int p_index) const;
		bool InitCheck(const unsigned int p_index);

		// Get and Set
		Core::Maths::Mat4& GetMatrixModelParent(const GraphNode& p_childs);
	};
}