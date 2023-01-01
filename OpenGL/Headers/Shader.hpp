#pragma once

#include "IResource.hpp"
#include "MyMaths.hpp"
#include "Light.hpp"

namespace Resources
{
	class Shader : public IResource
	{
		// Attribute
	private:
		int vertexShader;
		int fragmentShader;
		int shaderProgram;
		// path1 = path VertexShader
		// path2 = path FragmentShader
		const char* sourceVertex;
		const char* sourceFragment;
		std::string tempSourceV;
		std::string tempSourceF;

		// Methodes
	public:
		Shader(const std::string& p_name, const std::string& p_path1, const std::string& p_path2, const unsigned int p_id);

		void Init() override;
		void InitOpenGL() override;
		void Draw(const Core::Maths::Mat4& p_transform, const Core::Maths::Mat4& p_mvp);

		const int GetShaderProgram() const { return shaderProgram; }

	private:
		bool SetVertexShader();
		bool SetFragmentShader();
		bool Link();

		void OpenShader(const std::string& p_path, std::ifstream& p_source);
		void CloseShader(const std::string& p_path, std::ifstream& p_source);
	};

}