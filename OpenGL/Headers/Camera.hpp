#pragma once

#include "Transform.hpp"
#include "GameObject.hpp"
#include "InputsManager.hpp"

namespace LowRenderer
{
	class Camera : public GameObject
	{
		// Attribute
	private:
		float far;
		float near;

		float FOV;
		float speed;
		float aspect;

		Core::Maths::Vec2 rotationAroundPlayer;
		float radiusPlayer = 5.f;
		Core::Maths::Vec3 up;
		Core::Maths::Vec3 front;
		Core::Maths::Vec3 right;

		GameObject* player;

		Physics::Transform viewMatrix;
		Physics::Transform projectionMatrix;

		// Methode
	public:
		Camera(const int p_width = 1, const int p_height = 1);

		void Update(const Core::Inputs& p_Inputs, const double p_deltaTime,const Physics::Transform& p_transformParent = Physics::Transform()) override;

		// Get and Set
		Core::Maths::Mat4& GetViewProjection();
		void SetPlayer(GameObject* p_player) { player = p_player; };
		Core::Maths::Vec3& GetForward() { return front; };
		Core::Maths::Vec3& GetRight() { return right; };

	private:
		void UpdateInputs(const Core::Inputs& p_inputs);
		Core::Maths::Mat4 LookAt(const Core::Maths::Vec3& eye, const Core::Maths::Vec3& center, const Core::Maths::Vec3& up);
		void CalculateViewMatrix();
		void CalculateProjectionMatrix();
	};
}