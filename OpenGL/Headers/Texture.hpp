#pragma once

#include "IResource.hpp"

namespace Resources
{
	class Texture : public IResource
	{
		// Attribute
	private:
		unsigned int texture;
		unsigned int sampler;

		// Init
		unsigned char* data;
		int width, height, nrChannels;

		// Methode
	public:
		Texture(const std::string& p_name, const std::string& p_path1, const std::string& p_path2, const unsigned int p_id);
		~Texture();

		void Init() override;
		void InitOpenGL() override;
		void Draw(const unsigned int p_shaderProgram);
	};
}