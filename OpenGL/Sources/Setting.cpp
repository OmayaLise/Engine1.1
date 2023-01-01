#include "Setting.hpp"

namespace Resources
{
	Setting::Setting(const std::string& p_name, const std::string& p_path1, const std::string& p_path2, const unsigned int p_id)
		: inputsManager(nullptr)
		, Menu(p_name, p_path1, p_path2, p_id)
	{
	}

	void Setting::Init(const unsigned int p_width, const unsigned int p_height, Core::InputsManager* p_inputsManager, const std::string& p_path)
	{
		inputsManager = p_inputsManager;
		Menu::Init(p_width, p_height);
	}


	void Setting::Update(const Core::Inputs& p_Inputs, const double& p_deltaTime)
	{
		if (p_Inputs.quit)
			Scene::ReturnToMenu();
	}

	void Setting::Draw(const Core::Inputs& p_Inputs, std::chrono::duration<double>& elapsedMono, std::chrono::duration<double>& elapsedMulti)
	{
		StartImGui();

		ImGui::Begin("Setting");

		ImVec2 size = ImVec2(width, height);
		ImGui::SetWindowPos("Setting", ImVec2());
		ImGui::SetWindowSize("Setting", size);

		ImGui::SetCursorPos(ImVec2(width / 2, height / 2 + -150));
		ImGui::Text("Command");

		DrawButton("Forward", -100.f, Core::ModifyInput::Forward);
		DrawButton("Backward", -50.f, Core::ModifyInput::Backward);
		DrawButton("Left",		 0.f, Core::ModifyInput::Left);
		DrawButton("Right",		50.f, Core::ModifyInput::Right);
		DrawButton("Jump",     100.f, Core::ModifyInput::Jump);

		if (inputSelected != Core::ModifyInput::None)
			ChangeInput();

		ShowQuit();

		ImGui::End();

		EndImGui();
	}

	std::string Setting::GetInput(Core::ModifyInput p_input)
	{
		int input = -1; 
		std::string inputChar;

		switch (p_input)
		{
		case Core::ModifyInput::Forward:
			input = inputsManager->GetForward();
			break;

		case Core::ModifyInput::Backward:
			input = inputsManager->GetBackward();
			break;

		case Core::ModifyInput::Left:
			input = inputsManager->GetLeft();
			break;

		case Core::ModifyInput::Right:
			input = inputsManager->GetRight();
			break;

		case Core::ModifyInput::Jump:
			input = inputsManager->GetJump();
			break;

		default:
			break;
		}

		if (input == 32)
			inputChar = "SPACE";
		else
			inputChar = char(input);

		return inputChar;
	}

	int Setting::GetLastInput()
	{
		GLFWwindow* window = inputsManager->GetWindow();
		for (int i = 0; i < GLFW_KEY_END; i++)
		{
			if (glfwGetKey(window, i) == GLFW_PRESS)
				return i;
		}
		return -1;
	}

	void Setting::ChangeInput()
	{
		int input = GetLastInput();
		if (input == -1 || InputAlreadyUse(input))
			return;

		inputsManager->ChangeInput(input, inputSelected);
		inputSelected = Core::ModifyInput::None;
	}

	void Setting::DrawButton(const std::string& p_name, float p_yPos, Core::ModifyInput p_input)
	{
		ImGui::SetCursorPos(ImVec2(width / 2 - 110, height / 2 + p_yPos));
		ImGui::Text(p_name.c_str());
		ImGui::SetCursorPos(ImVec2(width / 2 + 110, height / 2 + p_yPos));
		if (ImGui::Button(GetInput(p_input).c_str(), ImVec2(200, 50)))
			inputSelected = p_input;

		if (inputSelected == p_input)
		{
			ImGui::SetCursorPos(ImVec2(width / 2 + 350, height / 2 + p_yPos + 15));
			ImGui::Text("Enter input");
		}
	}

	bool Setting::InputAlreadyUse(const int p_input)
	{
		if (inputsManager->GetForward()	 == p_input
		 || inputsManager->GetBackward() == p_input
		 || inputsManager->GetLeft()	 == p_input
		 || inputsManager->GetRight()	 == p_input
		 || inputsManager->GetJump()	 == p_input)
			return true;
		return false;
	}

}