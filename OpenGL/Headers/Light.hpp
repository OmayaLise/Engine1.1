#pragma once

#include "MyMaths.hpp"

namespace LowRenderer
{
	struct InitLight
	{
		Core::Maths::Vec3 position;

		Core::Maths::Vec4 ambientColor;
		Core::Maths::Vec4 diffuseColor;
		Core::Maths::Vec4 specularColor;
	};

	class Light
	{
		// Attribute
	protected:
		Core::Maths::Vec3 position;

		Core::Maths::Vec4 ambientColor;
		Core::Maths::Vec4 diffuseColor;
		Core::Maths::Vec4 specularColor;

		// Methode
	public:
		virtual void Update(const int p_shaderProgram, const Core::Maths::Vec3& p_camPosition, std::string& p_array);

		// Get and Set
		Core::Maths::Vec4& GetDiffuseColor() { return diffuseColor; };
		Core::Maths::Vec4& GetAmbientColor() { return ambientColor; };
		Core::Maths::Vec4& GetSpecularColor() { return specularColor; };
		Core::Maths::Vec3& GetPosition() { return position; };
	};

	class DirectionLight : public Light
	{
		// Attribute
	private:
		Core::Maths::Vec3 direction;

		// Methode
	public:
		DirectionLight(const InitLight& p_initLight, const Core::Maths::Vec3& p_diretion);

		void Update(const int p_shaderProgram, const Core::Maths::Vec3& p_camPosition, const unsigned int p_index);
	
		Core::Maths::Vec3& GetDirection() { return direction; };
	};

	class PointLight : public Light
	{
		// Attribute
	private:
		float constant;
		float linear;
		float quadratic;

		// Methode
	public:
		PointLight(const InitLight& p_initLight, const float p_constant, const float p_linear, const float p_quadratic);

		void Update(const int p_shaderProgram, const Core::Maths::Vec3& p_camPosition, const unsigned int p_index);
	
		float& GetConstant() { return constant; };
		float& GetLinear() { return linear; };
		float& GetQuadratic() { return quadratic; };
	};

	class SpotLight : public Light
	{
		// Attribute
	private:
		Core::Maths::Vec3 direction;
		float cutOff;
		float outerCutOff;

		// Methode
	public:
		SpotLight(const InitLight& p_initLight, const Core::Maths::Vec3& p_direction, const float p_cutOff, const float p_outerCutOff);

		void Update(const int p_shaderProgram, const Core::Maths::Vec3& p_camPosition, const unsigned int p_index);
	
		Core::Maths::Vec3& GetDirection() { return direction; };
		float& GetCutOff() { return cutOff; };
		float& GetOuterCutOff() { return outerCutOff; };

	};
}