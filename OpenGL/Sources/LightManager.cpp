#include "LightManager.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Imgui/imgui.h"
#include "Imgui/imgui_impl_glfw.h"
#include "Imgui/imgui_impl_opengl3.h"

#include "Log.hpp"

namespace LowRenderer
{
	LightManager::LightManager()
		: directionLights()
		, pointLights()
		, spotLights()
	{
	}

	void LightManager::Draw(const int p_shaderProgram, const Core::Maths::Vec3& p_camPosition)
	{
		glUniform1f(glGetUniformLocation(p_shaderProgram, "nbDirectionLight"), directionLights.size());
		glUniform1f(glGetUniformLocation(p_shaderProgram, "nbPointLight"), pointLights.size());
		glUniform1f(glGetUniformLocation(p_shaderProgram, "nbSpotLight"), spotLights.size());

		for (unsigned int i = 0; i < directionLights.size(); i++)
			directionLights[i].Update(p_shaderProgram, p_camPosition, i);

		for (unsigned int i = 0; i < pointLights.size(); i++)
			pointLights[i].Update(p_shaderProgram, p_camPosition, i);

		for (unsigned int i = 0; i < spotLights.size(); i++)
			spotLights[i].Update(p_shaderProgram, p_camPosition, i);
	}

	void LightManager::DrawImGui()
	{
		ImGui::Begin("Light");
		for (unsigned int i = 0; i < directionLights.size(); i++)
		{
			if (ImGui::CollapsingHeader(("Direction light " + std::to_string(i)).c_str(), ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::ColorEdit3(("Ambient (d) " + std::to_string(i)).c_str(), &directionLights[i].GetAmbientColor().x);
				ImGui::ColorEdit3(("Diffuse (d) " + std::to_string(i)).c_str(), &directionLights[i].GetDiffuseColor().x);
				ImGui::ColorEdit3(("Specular (d) " + std::to_string(i)).c_str(), &directionLights[i].GetSpecularColor().x);
				ImGui::SliderFloat3(("Position (d) " + std::to_string(i)).c_str(), &directionLights[i].GetPosition().x, -10.f, 10.f, "%0.1f", 0);
				ImGui::SliderFloat3(("Direction (d) " + std::to_string(i)).c_str(), &directionLights[i].GetDirection().x, -1.f, 1.f, "%0.1f", 0);
			}
		}

		for (unsigned int i = 0; i < pointLights.size(); i++)
		{
			if (ImGui::CollapsingHeader(("Point light " + std::to_string(i)).c_str(), ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::ColorEdit3(("Ambient (P) " + std::to_string(i)).c_str(), &pointLights[i].GetAmbientColor().x);
				ImGui::ColorEdit3(("Diffuse (P) " + std::to_string(i)).c_str(), &pointLights[i].GetDiffuseColor().x);
				ImGui::ColorEdit3(("Specular (P) " + std::to_string(i)).c_str(), &pointLights[i].GetSpecularColor().x);
				ImGui::SliderFloat3(("Position (P) " + std::to_string(i)).c_str(), &pointLights[i].GetPosition().x, -10.f, 10.f, "%0.1f", 0);
				ImGui::SliderFloat(("Constant (P) " + std::to_string(i)).c_str(), &pointLights[i].GetConstant(), -1.f, 1.f, "%0.3f", 0);
				ImGui::SliderFloat(("Linear (P) " + std::to_string(i)).c_str(), &pointLights[i].GetLinear(), 0.f, 0.8f, "%0.3f", 0);
				ImGui::SliderFloat(("Quadratic (P) " + std::to_string(i)).c_str(), &pointLights[i].GetQuadratic(), 0.f, 2.f, "%0.3f", 0);
			}
		}

		for (unsigned int i = 0; i < spotLights.size(); i++)
		{
			if (ImGui::CollapsingHeader(("Spot light " + std::to_string(i)).c_str(), ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::ColorEdit3(("Ambient (S) " + std::to_string(i)).c_str(), &spotLights[i].GetAmbientColor().x);
				ImGui::ColorEdit3(("Diffuse (S) " + std::to_string(i)).c_str(), &spotLights[i].GetDiffuseColor().x);
				ImGui::ColorEdit3(("Specular (S) " + std::to_string(i)).c_str(), &spotLights[i].GetSpecularColor().x);
				ImGui::SliderFloat3(("Position (S) " + std::to_string(i)).c_str(), &spotLights[i].GetPosition().x, -10.f, 10.f, "%0.1f", 0);
				ImGui::SliderFloat3(("Direction (S) " + std::to_string(i)).c_str(), &spotLights[i].GetDirection().x, -1.f, 1.f, "%0.1f", 0);
				ImGui::SliderFloat(("Cut off (S) " + std::to_string(i)).c_str(), &spotLights[i].GetCutOff(), -50.f, 50.f, "%0.1f", 0);
				ImGui::SliderFloat(("Outer cut off (S) " + std::to_string(i)).c_str(), &spotLights[i].GetOuterCutOff(), -50.f, 50.f, "%0.1f", 0);
			}
		}
		ImGui::End();
	}

	void LightManager::AddDirectionLight(const DirectionLight& p_light)
	{
		if(directionLights.size() >= MAX_DIRECTION_LIGHT)
		{
			Core::Debug::Log::Print("Can't add more direction light, they have already " + std::to_string(MAX_DIRECTION_LIGHT) + "\n", Core::Debug::LogLevel::Warning);
			return;
		}
		directionLights.push_back(p_light);
		Core::Debug::Log::Print("Add direction light\n", Core::Debug::LogLevel::Notification);
	}

	void LightManager::AddPointLight(const PointLight& p_light)
	{
		if (pointLights.size() >= MAX_POINT_LIGHT)
		{
			Core::Debug::Log::Print("Can't add more point light, they have already " + std::to_string(MAX_POINT_LIGHT) + "\n", Core::Debug::LogLevel::Warning);
			return;
		}
		pointLights.push_back(LowRenderer::PointLight(p_light));
		Core::Debug::Log::Print("Add point light\n", Core::Debug::LogLevel::Notification);
	}

	void LightManager::AddSpotLight(const SpotLight& p_light)
	{
		if (spotLights.size() >= MAX_SPOT_LIGHT)
		{
			Core::Debug::Log::Print("Can't add more spot light, they have already " + std::to_string(MAX_SPOT_LIGHT) + "\n", Core::Debug::LogLevel::Warning);
			return;
		}
		spotLights.push_back(LowRenderer::SpotLight(p_light));
		Core::Debug::Log::Print("Add spot light\n", Core::Debug::LogLevel::Notification);
	}
}