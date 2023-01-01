#pragma once

#include "Scene.hpp"

namespace Resources
{
	class Menu : public Scene
	{
		// Methode
	public:
		Menu(const std::string& p_name, const std::string& p_path1, const std::string& p_path2, const unsigned int p_id);
	
		void Update(const Core::Inputs& p_Inputs, const double& p_deltaTime) override;
		void Draw(const Core::Inputs& p_Inputs, std::chrono::duration<double>& elapsedMono, std::chrono::duration<double>& elapsedMulti) override;

	private:
		void Quit();
	};
}