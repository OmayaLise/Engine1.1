#pragma once

#include <vector>

#include "MyMaths.hpp"
#include "Model.hpp"
#include "LightManager.hpp"
#include "InputsManager.hpp"

// Physics
#include "Transform.hpp"
#include "Collider.hpp"
#include "Rigidbody.hpp"

// Gameplay::Player
#include "PlayerControler.hpp"

namespace LowRenderer
{
	enum class GOType
	{
		Player,
		Camera,
		None
	};

	class GameObject
	{
		// Attribute
	protected:
			// IComponent
		LowRenderer::Model model;
		Gameplay::Player::PlayerControler playerControler;

		Physics::Transform transform;
		std::string name;

		Physics::Rigidbody rigidbody;

		Physics::Collider* collider;
		// Methode
	public:
		GameObject(const LowRenderer::Model& p_model, const Physics::Transform& p_transform = Physics::Transform(), const std::string& p_name = "Default name");
		GameObject(const std::string& p_name, const Physics::Transform& p_transform = Physics::Transform());
		GameObject(const GameObject& p_gameObject);

		virtual void Update(const Core::Inputs& p_Inputs, const double p_deltaTime, const Physics::Transform& p_transformParent = Physics::Transform());
		void Draw(Core::Maths::Mat4& p_vp, Core::Maths::Vec3 p_camPos, LightManager& p_lightManager, Core::Maths::Mat4 p_transformParent = Core::Maths::Mat4::Identity());

		void Translate(const Core::Maths::Vec3& p_translation);
		void Scale(const Core::Maths::Vec3& p_scale);
		void Rotate(const Core::Maths::Vec3& p_rotation);

		// Get and Set
		const int GetShaderProgram() { return model.GetShaderProgram(); };
		Model GetModel() { return model; };
		std::string& GetName() { return name; };
		Physics::Transform* GetTransfrom() { return &transform; };

		Physics::Transform& GetTransform() { return transform; };
		Core::Maths::Vec3& GetTranslation() { return transform.translation; };
		virtual Core::Maths::Vec3& GetRotation() { return transform.rotation; };
		Core::Maths::Vec3& GetScale() { return transform.scale; };
		Core::Maths::Mat4& GetModelMatrix() { return transform.matrix; };

		void SetEnableModel(const bool p_isEnable) { model.isEnable = p_isEnable; };
		void SetEnablePlayerControler(const bool p_isEnable) { playerControler.isEnable = p_isEnable; };
		void SetCameraRotation(Core::Maths::Vec3& p_forward, Core::Maths::Vec3& p_right) { playerControler.SetCam(p_forward, p_right); };

		void SetCollider(Physics::Collider* p_collider);
		Physics::Collider* GetCollider();
		Physics::Rigidbody& GetRigidbody() { return rigidbody; };
	};
}
