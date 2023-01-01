#pragma once

#include <vector>

#include "Light.hpp"

namespace LowRenderer
{
	const unsigned int MAX_DIRECTION_LIGHT = 5;
	const unsigned int MAX_POINT_LIGHT = 5;
	const unsigned int MAX_SPOT_LIGHT = 5;

	class LightManager
	{
		// Attribute
	private:
		std::vector<DirectionLight> directionLights;
		std::vector<PointLight>		pointLights;
		std::vector<SpotLight>		spotLights;

		// Methode
	public:
		LightManager();

		void Draw(const int p_shaderProgram, const Core::Maths::Vec3& p_camPosition);
		void DrawImGui();

		void AddDirectionLight(const DirectionLight& p_light);
		void AddPointLight(const PointLight& p_light);
		void AddSpotLight(const SpotLight& p_light);
	};
}