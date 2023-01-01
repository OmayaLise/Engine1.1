#include "Light.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <string>

namespace LowRenderer
{
	// --------------------
	//        Light
	// --------------------

	void Light::Update(const int p_shaderProgram, const Core::Maths::Vec3& p_camPosition, std::string& p_array)
	{
		p_array += "lightData.";

		glUniform4f(glGetUniformLocation(p_shaderProgram, (p_array + "ambientColor").c_str()), ambientColor.x, ambientColor.y, ambientColor.z, ambientColor.w);
		glUniform4f(glGetUniformLocation(p_shaderProgram, (p_array + "diffuseColor").c_str()), diffuseColor.x, diffuseColor.y, diffuseColor.z, diffuseColor.w);
		glUniform4f(glGetUniformLocation(p_shaderProgram, (p_array + "specularColor").c_str()), specularColor.x, specularColor.y, specularColor.z, specularColor.w);
		glUniform3f(glGetUniformLocation(p_shaderProgram, (p_array + "lightPos").c_str()), position.x, position.y, position.z);
		glUniform3f(glGetUniformLocation(p_shaderProgram, (p_array + "viewPos").c_str()), p_camPosition.x, p_camPosition.y, p_camPosition.z);
	}

	// --------------------
	//   Direction Light
	// --------------------

	DirectionLight::DirectionLight(const InitLight& p_initLight, const Core::Maths::Vec3& p_diretion)
		: direction(p_diretion)
	{
		ambientColor = p_initLight.ambientColor;
		diffuseColor = p_initLight.diffuseColor;
		specularColor = p_initLight.specularColor;
		position = p_initLight.position;
	}

	void DirectionLight::Update(const int p_shaderProgram, const Core::Maths::Vec3& p_camPosition, const unsigned int p_index)
	{
		std::string array = "directionLights[" + std::to_string(p_index) + "].";

		glUniform3f(glGetUniformLocation(p_shaderProgram, (array + "direction").c_str()), direction.x, direction.y, direction.z);

		Light::Update(p_shaderProgram, p_camPosition, array);
	}

	// --------------------
	//     Point Light
	// --------------------

	PointLight::PointLight(const InitLight& p_initLight, const float p_constant, const float p_linear, const float p_quadratic)
		: constant(p_constant)
		, linear(p_linear)
		, quadratic(p_quadratic)
	{
		ambientColor = p_initLight.ambientColor;
		diffuseColor = p_initLight.diffuseColor;
		specularColor = p_initLight.specularColor;
		position = p_initLight.position;
	}

	void PointLight::Update(const int p_shaderProgram, const Core::Maths::Vec3& p_camPosition, const unsigned int p_index)
	{
		std::string array = "pointLights[" + std::to_string(p_index) + "].";

		glUniform1f(glGetUniformLocation(p_shaderProgram, (array + "constant").c_str()), constant);
		glUniform1f(glGetUniformLocation(p_shaderProgram, (array + "linear").c_str()), linear);
		glUniform1f(glGetUniformLocation(p_shaderProgram, (array + "quadratic").c_str()), quadratic);

		Light::Update(p_shaderProgram, p_camPosition, array);
	}

	// --------------------
	//      Spot Light
	// --------------------

	SpotLight::SpotLight(const InitLight& p_initLight, const Core::Maths::Vec3& p_direction, const float p_cutOff, const float p_outerCutOff)
		: direction(p_direction)
		, cutOff(p_cutOff)
		, outerCutOff(p_outerCutOff)
	{
		ambientColor = p_initLight.ambientColor;
		diffuseColor = p_initLight.diffuseColor;
		specularColor = p_initLight.specularColor;
		position = p_initLight.position;
	}

	void SpotLight::Update(const int p_shaderProgram, const Core::Maths::Vec3& p_camPosition, const unsigned int p_index)
	{
		std::string array = "spotLights[" + std::to_string(p_index) + "].";

		glUniform3f(glGetUniformLocation(p_shaderProgram, (array+ "direction").c_str()), direction.x, direction.y, direction.z);
		glUniform1f(glGetUniformLocation(p_shaderProgram, (array + "cutOff").c_str()), cosf(Core::Maths::DEG2RAD * cutOff));
		glUniform1f(glGetUniformLocation(p_shaderProgram, (array + "outerCutOff").c_str()), outerCutOff);

		Light::Update(p_shaderProgram, p_camPosition, array);
	}
}