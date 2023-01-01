#include "Credit.hpp"

namespace Resources
{
	Credit::Credit(const std::string& p_name, const std::string& p_path1, const std::string& p_path2, const unsigned int p_id)
		: Menu(p_name, p_path1, p_path2, p_id)
	{
	}

	void Credit::Update(const Core::Inputs& p_Inputs,const double& p_deltaTime)
	{
		if(p_Inputs.quit)
			Scene::ReturnToMenu();
	}

	void Credit::Draw(const Core::Inputs& p_Inputs, std::chrono::duration<double>& elapsedMono, std::chrono::duration<double>& elapsedMulti)
	{
		StartImGui();
		
		ImVec2 size = ImVec2(width, height);
		ImGui::SetWindowPos("Credit", ImVec2());
		ImGui::SetWindowSize("Credit", size);

		ImGui::Begin("Credit");
		ImGui::SetCursorPos(ImVec2(width / 2 - 110, height / 2 - 15));
		ImGui::Text("Programmers team");
		ImGui::SetCursorPos(ImVec2(width / 2 - 100, height / 2 + 15));
		ImGui::Text("Lise Omaya");
		ImGui::SetCursorPos(ImVec2(width / 2 - 100, height / 2 + 40));
		ImGui::Text("Devine Vincent");
		
		ShowQuit();

		ImGui::End();

		EndImGui();
	}
}