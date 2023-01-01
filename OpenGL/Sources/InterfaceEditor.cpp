#include "InterfaceEditor.hpp"

namespace Core::Editor
{
	InterfaceEditor::InterfaceEditor()
	{
	}

	InterfaceEditor::~InterfaceEditor()
	{
		/*ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();*/
	}

	void InterfaceEditor::InitGUI(GLFWwindow* window)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGui::StyleColorsDark();
		ImGuiStyle& style = ImGui::GetStyle();

		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 330");
	}

	void InterfaceEditor::DrawEditorWindow( Core::DataStructure::Graph p_graph)
	{
		//NewFrame();

		HierachyWindow(p_graph);
		InspectorWindow();

		//EndFrame();
	}

	bool InterfaceEditor::IsMouseHoverUI()
	{
		return true;
	}

	void InterfaceEditor::NewFrame()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		m_mouseOnWindow = false;
	}

	void InterfaceEditor::EndFrame()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void InterfaceEditor::HierachyWindow( Core::DataStructure::Graph p_graph)
	{
		bool open = true;
		ImVec2 size = ImVec2();
		size.x = 400;
		size.y = 1080;
		ImVec2 pos = ImVec2();
		pos.x = 0;
		pos.y = 0;
		// render your GUI
		ImGui::SetWindowPos("Scene Graph", pos);
		ImGui::SetWindowSize("Scene Graph", size);
		ImGui::Begin("Scene Graph", &open, ImGuiWindowFlags_NoResize);
		if (ImGui::IsMouseHoveringRect(pos, size))
			m_mouseOnWindow = true;

		std::vector<Core::DataStructure::GraphNode>& nodes = *p_graph.GetNodes();

		for (size_t i = 0; i < nodes.size(); ++i)
		{
			if (nodes[i].parentIndex == Core::DataStructure::INVALID_INDEX)
			{
				LowRenderer::GameObject* item = p_graph.GetGameObject(nodes[i].indexGameObject);
				ImGui::Selectable(item->GetName().c_str());
				if (ImGui::IsItemClicked()) m_GoSelected = p_graph.GetGameObject(nodes[i].indexGameObject);
				DrawChildrenObject(nodes[i].childsIndex, p_graph);
			}
		}

		ImGui::End();
	}

	void InterfaceEditor::DrawChildrenObject(std::vector<int>& childrenIndex, Core::DataStructure::Graph p_graph)
	{

		ImGui::Indent();
		for (int i = 0; i < childrenIndex.size(); i++)
		{
			int indexItem = p_graph.GetNode(childrenIndex[i]).indexGameObject;
			LowRenderer::GameObject* item = p_graph.GetGameObject(indexItem);
			ImGui::Selectable(item->GetName().c_str());
			if (ImGui::IsItemClicked()) m_GoSelected = p_graph.GetGameObject(indexItem);
			DrawChildrenObject(p_graph.GetNode(childrenIndex[i]).childsIndex, p_graph);
		}
		ImGui::Unindent();
	}

	void InterfaceEditor::InspectorWindow()
	{
		bool open = true;
		ImVec2 size = ImVec2();
		size.x = 400;
		size.y = 1080;
		ImVec2 pos = ImVec2();
		pos.x = 1520;
		pos.y = 0;
		// render your GUI

		ImGui::SetWindowPos("Inspector", pos);
		ImGui::SetWindowSize("Inspector", size);
		ImGui::Begin("Inspector", &open, ImGuiWindowFlags_NoResize);
		ImVec2 max;
		max.x = pos.x + size.x;
		max.y = pos.y + size.y;
		if (ImGui::IsMouseHoveringRect(pos, max))
			m_mouseOnWindow = true;

		ImGui::Spacing();
		if (m_GoSelected != nullptr)
		{
			std::string name = m_GoSelected->GetName();
			if (ImGui::CollapsingHeader(name.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::Indent();
				Physics::Transform* itemTransform = m_GoSelected->GetTransfrom();
				ShowTransform(itemTransform, "Local Tranform", "Local ");
				ImGui::Spacing();
				ImGui::Separator();
				itemTransform->matrix = itemTransform->GetLocalTransform();
			}

			if (m_GoSelected->GetCollider() != nullptr)
			{
				ShowCollider(m_GoSelected->GetCollider());
			}
			if (m_GoSelected->GetRigidbody().isEnable)
			{
				ShowRigidbody(m_GoSelected->GetRigidbody());
			}
		}
		ImGui::End();
	}

	void InterfaceEditor::ShowTransform(Physics::Transform* p_transform, const char* p_name, const char* p_prefix)
	{
		if (ImGui::CollapsingHeader(p_name, ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::Spacing();
			std::string text = p_prefix;
			text += "Position";
			ImGui::DragFloat3(text.c_str(), p_transform->translation.coord);


			text = p_prefix;
			text += "Rotation";
			ImGui::DragFloat3(text.c_str(), p_transform->rotation.coord);

			text = p_prefix;
			text += "Scale";
			ImGui::DragFloat3(text.c_str(), p_transform->scale.coord);

		}
	}

	void InterfaceEditor::ShowCollider(Physics::Collider* coll)
	{
		std::string name ="Collider";
		if (typeid(*coll) == typeid(Physics::BoxCollider)) name = "Box Collider";
		if (typeid(*coll) == typeid(Physics::SphereCollider)) name = "Sphere Collider";
		if (typeid(*coll) == typeid(Physics::CapsuleCollider)) name = "Capsule Collider";
		

		if (ImGui::CollapsingHeader(name.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::Checkbox("Enable", &coll->isEnable);
			ImGui::Checkbox("Kinematic", &coll->kinematic);
			ImGui::Checkbox("Trigger", &coll->isTrigger);
			ImGui::DragFloat3("Center", coll->center.coord);

			if (typeid(*coll) == typeid(Physics::BoxCollider) )
			{
				Physics::BoxCollider* box = dynamic_cast<Physics::BoxCollider*>(coll);
				ImGui::DragFloat3("Extents", box->extents.coord);
			}
			if (typeid(*coll) == typeid(Physics::CapsuleCollider))
			{
				Physics::CapsuleCollider* capsule = dynamic_cast<Physics::CapsuleCollider*>(coll);
				ImGui::DragFloat3("Extents", capsule->extents.coord);
			}
			if (typeid(*coll) == typeid(Physics::SphereCollider))
			{
				Physics::SphereCollider* sphere = dynamic_cast<Physics::SphereCollider*>(coll);
				ImGui::DragFloat("Radius", &sphere->radius);
			}
		}
	}

	void InterfaceEditor::ShowRigidbody(Physics::Rigidbody& rb)
	{
		if (ImGui::CollapsingHeader("Rigidbody", ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::Checkbox("Enable", &rb.isEnable);
			ImGui::Checkbox("Use Gravity", &rb.useGravity);
			ImGui::DragFloat3("Velocity", rb.velocity.coord, ImGuiSliderFlags_NoInput);
			ImGui::DragFloat3("Gravity Velocity", rb.gravityVelocity.coord, ImGuiSliderFlags_NoInput);
		} 
	}

}