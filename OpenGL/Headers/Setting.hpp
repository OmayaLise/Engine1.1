#pragma once

#include "Menu.hpp"

namespace Resources 
{
	class Setting : public Menu
	{
		// Attribute
	private:
		Core::InputsManager* inputsManager;

		Core::ModifyInput inputSelected = Core::ModifyInput::None;

		// Methode
	public:
		Setting(const std::string& p_name, const std::string& p_path1, const std::string& p_path2, const unsigned int p_id);

		void Init(const unsigned int p_width, const unsigned int p_height, Core::InputsManager* p_inputsManager,const std::string& p_path = "");
		void Update(const Core::Inputs& p_Inputs, const double& p_deltaTime) override;
		void Draw(const Core::Inputs& p_Inputs, std::chrono::duration<double>& elapsedMono, std::chrono::duration<double>& elapsedMulti) override;

	private:
		std::string GetInput(Core::ModifyInput p_input);
		int GetLastInput();
		void ChangeInput();
		void DrawButton(const std::string& p_name, float p_yPos, Core::ModifyInput p_input);
		bool InputAlreadyUse(const int input);
	};
}