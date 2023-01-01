#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Graph.hpp"
#include "GameObject.hpp"

namespace Core::Editor
{
	class InterfaceEditor
	{
	public:
		InterfaceEditor();
		~InterfaceEditor();

		// Methods
		void InitGUI(GLFWwindow* window);
		void DrawEditorWindow(Core::DataStructure::Graph p_graph);
		bool IsMouseHoverUI();

	private:

		// Attribute
		bool m_mouseOnWindow;
		LowRenderer::GameObject* m_GoSelected = nullptr;

		// Methods
		void NewFrame();
		void EndFrame();
		void HierachyWindow(Core::DataStructure::Graph p_graph);
		void DrawChildrenObject(std::vector<int>& childrenIndex, Core::DataStructure::Graph p_graph);
		void InspectorWindow();
		void ShowTransform(Physics::Transform* p_transform, const char* p_name, const char* p_prefix);
		void ShowCollider(Physics::Collider* coll);
		void ShowRigidbody(Physics::Rigidbody& rb);

	};



}