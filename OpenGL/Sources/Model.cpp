#include "Model.hpp"

namespace LowRenderer
{

	Model::Model(Resources::Mesh* p_mesh, Resources::Shader* p_shader)
		: mesh(p_mesh)
		, shader(p_shader)
		, texture(nullptr)
	{
	}

	Model::Model(Resources::Mesh* p_mesh, Resources::Shader* p_shader, Resources::Texture* p_texture)
		: mesh(p_mesh)
		, shader(p_shader)
		, texture(p_texture)
	{
		isEnable = true;
	}

	Model::Model()
		: mesh(nullptr)
		, shader(nullptr)
		, texture(nullptr)
	{
		isEnable = false;
	}


	void Model::Draw(const Core::Maths::Mat4& p_transform, const Core::Maths::Mat4& p_mvp) const
	{
		texture->Draw(shader->GetShaderProgram());
		shader->Draw(p_transform, p_mvp);
		mesh->Draw();
	}

	bool Model::InitCheck()const
	{
		if ( texture && shader && mesh && texture->GetStat() == Resources::StatResource::LOADED
			&& shader->GetStat() == Resources::StatResource::LOADED && mesh->GetStat() == Resources::StatResource::LOADED)
			return true;
		return false;
	}
}