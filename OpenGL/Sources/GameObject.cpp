#include "GameObject.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Imgui/imgui.h"
#include "Imgui/imgui_impl_glfw.h"
#include "Imgui/imgui_impl_opengl3.h"

#include "Assertion.hpp"

#include "Camera.hpp"

namespace LowRenderer
{
	GameObject::GameObject(const LowRenderer::Model& p_model, const Physics::Transform& p_transform, const std::string& p_name)
		: model(p_model)
		, playerControler()
		, transform(p_transform)
		, name(p_name)
		, collider(nullptr)
		, rigidbody( &transform,false)
	{
	}

	GameObject::GameObject(const std::string& p_name, const Physics::Transform& p_transform)
		: model		()
		, playerControler()
		, transform (p_transform)
		, name		(p_name)
		, collider(nullptr)
		, rigidbody( &transform, false)
	{
	}

	GameObject::GameObject(const GameObject& p_gameObject)
		: model(p_gameObject.model)
		, transform(p_gameObject.transform)
		, name(p_gameObject.name)
		, collider(nullptr)
		, rigidbody( &transform, false)
	{
	}

	void GameObject::Update(const Core::Inputs& p_Inputs, const double p_deltaTime,const Physics::Transform& p_transformParent)
	{
		if (playerControler.isEnable)
			playerControler.Update(p_Inputs, rigidbody, *collider,transform.translation,p_deltaTime);

		transform.matrix = p_transformParent.matrix * transform.GetLocalTransform();
	}

	void GameObject::Draw(Core::Maths::Mat4& p_vp, Core::Maths::Vec3 p_camPos, LightManager& p_lightManager, Core::Maths::Mat4 p_transformParent)
	{
		if (model.isEnable)
		{
			const int shaderProgram = GetShaderProgram();
			glUseProgram(shaderProgram);

			p_lightManager.Draw(shaderProgram, p_camPos);

			model.Draw(transform.matrix, (p_vp * transform.matrix));
		}

		//DrawImGui();
	}

	void GameObject::Translate(const Core::Maths::Vec3& p_translation)
	{
		transform.translation += p_translation;
	}

	void GameObject::Scale(const Core::Maths::Vec3& p_scale)
	{
		transform.scale += p_scale;
	}

	void GameObject::Rotate(const Core::Maths::Vec3& p_rotation)
	{
		transform.rotation += p_rotation;
		if (transform.rotation.x > 360)
			transform.rotation.x = 0;
		else if (transform.rotation.x < -360)
			transform.rotation.x = 0;

		if (transform.rotation.y > 360)
			transform.rotation.y = 0;
		else if (transform.rotation.y < -360)
			transform.rotation.y = 0;

		if (transform.rotation.z > 360)
			transform.rotation.z = 0;
		else if (transform.rotation.z < -360)
			transform.rotation.z = 0;
	}

	void GameObject::SetCollider(Physics::Collider* p_collider)
	{ 
		collider = p_collider; 
		collider->ptransform = &transform; 
		collider->rbLink = &rigidbody;
		rigidbody.isEnable = true;
	}

	Physics::Collider* GameObject::GetCollider()
	{
		return collider;
	}
}