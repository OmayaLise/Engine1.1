#include "Menu.hpp"

#include "App.hpp"

namespace Resources
{
	Menu::Menu(const std::string& p_name, const std::string& p_path1, const std::string& p_path2, const unsigned int p_id)
		: Scene(p_name, p_path1, p_path2, p_id)
	{
	}


	void Menu::Update(const Core::Inputs& p_inputs, const double& p_deltaTime)
	{
	}

	void Menu::Draw(const Core::Inputs& p_Inputs, std::chrono::duration<double>& elapsedMono, std::chrono::duration<double>& elapsedMulti)
	{
		StartImGui();

		ImVec2 size = ImVec2(width, height);
		ImGui::SetWindowPos("Menu", ImVec2());
		ImGui::SetWindowSize("Menu", size);

		ImGui::Begin("Menu");

		ImGui::SetCursorPos(ImVec2(width / 2 - 200, height / 2 - 200));

		ImGui::SetWindowFontScale(3);
		ImGui::Text("Patrik's Adventures");
		ImGui::SetWindowFontScale(1);
		ImGui::SetCursorPos(ImVec2(width / 2 - 100, height / 2 - 100));
		if (ImGui::Button("Start", ImVec2(200, 50)))
			Core::App::nextScene = NextScene{ "Scene1", SceneType::ST_Game };

		std::string multi = "Multithread";
		if (Core::ThreadsManager::multithread == true)
			ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(0, 255, 0, 150));
		else
			ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(255, 0, 0, 150));

		ImGui::SetCursorPos(ImVec2(width / 2 - 100, height / 2 - 35));
		if (ImGui::Button(multi.c_str(), ImVec2(200, 50)))
			Core::ThreadsManager::multithread = !Core::ThreadsManager::multithread;
		ImGui::PopStyleColor();
		
		ImGui::SetCursorPos(ImVec2(width / 2 - 100, height / 2 + 35));
		if (ImGui::Button("Setting", ImVec2(200, 50)))
			Core::App::nextScene = NextScene{ "Setting", SceneType::ST_Setting };

		ImGui::SetCursorPos(ImVec2(width / 2 - 100, height / 2 + 100));
		if (ImGui::Button("Credit", ImVec2(200, 50)))
			Core::App::nextScene = NextScene{ "Credit", SceneType::ST_Credit };

		ImGui::SetCursorPos(ImVec2(width / 2 - 100, height / 2 + 170));
		if (ImGui::Button("Quit", ImVec2(200, 50)))

			Quit();

		ImGui::End();

		EndImGui();
	}

	void Menu::Quit()
	{
		Core::App::StopGame();
	}
}