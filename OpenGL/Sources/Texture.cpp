#include "Texture.hpp"

#include "Assertion.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <STB_Image/stb_image.h>
#include <iostream>

namespace Resources
{
	Texture::Texture(const std::string& p_name, const std::string& p_path1, const std::string& p_path2, const unsigned int p_id)
		: texture(0)
		, sampler(0)
	{
		name = p_name;
		path1 = p_path1;
		path2 = p_path2;
		id = p_id;
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &texture);
		glDeleteSamplers(1, &sampler);
	}

	void Texture::Init()
	{
		// generate the texture data
		stbi_set_flip_vertically_on_load(true);
		data = stbi_load(path1.c_str(), &width, &height, &nrChannels, 0);
		stat = StatResource::INITIALIZED;
	}

	void Texture::InitOpenGL()
	{
		bool isPng = true;
		if (path1.find(".jpg") != std::string::npos)
			isPng = false;

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		if (isPng)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		else
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);

		// create a sampler and parameterize it
		glGenSamplers(1, &sampler);
		glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glSamplerParameterf(sampler, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4.f);

		GLint max = 0;
		glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &max);

		glBindTextureUnit(id, texture);
		glBindSampler(id, sampler);
		stat = StatResource::LOADED;
	}

	void Texture::Draw(const unsigned int p_shaderProgram)
	{
		GLint location = glGetUniformLocation(p_shaderProgram, "texture1");
		if(location!= -1) glUniform1i(location, id);
	}
}