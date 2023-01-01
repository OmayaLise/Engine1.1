#pragma once

// Core
#include "InputsManager.hpp"
// Core::DataStructure
#include "IComponent.hpp"
// Physics
#include "Rigidbody.hpp"
#include "Transform.hpp"
#include "Collider.hpp"

namespace Gameplay::Player
{
	class PlayerControler : public Core::DataStructure::IComponent
	{
		// Attribute
	private:
		Core::Maths::Vec3* forwardCam;
		Core::Maths::Vec3* rightCam;
		Core::Maths::Vec3 startPosition = { 7.0f,-3.0f,0.0f };
		
		float deathZoneHeightLimit = -15.0f;
		float speed;
		float jumpHeight;

		float coyoteTimer= 0.2f;
		float coyoteCountdown;
		bool canJump = false;

		// Methode
	public:
		PlayerControler(const float p_speed = 15.f, const float p_jumpHeight = 15.f);

		void Update(const Core::Inputs& p_inputs, Physics::Rigidbody& p_rb, const Physics::Collider& p_collider, Core::Maths::Vec3& p_position, const double p_deltaTime);

		// Get and Set
		void SetCam(Core::Maths::Vec3& p_forward, Core::Maths::Vec3& p_right) { forwardCam = &p_forward; rightCam = &p_right; };
		Core::Maths::Vec3* GetForwardCam() { return forwardCam; };
	private:
		void Move(const Core::Inputs& p_inputs, Physics::Rigidbody& p_rb);
		void Jump(const Core::Inputs& p_inputs, Physics::Rigidbody& p_rb, const Physics::Collider& p_collider, const double p_deltaTime);
		void DeathZone(Core::Maths::Vec3& p_position);
		bool CheckJumpCondition(const Physics::Collider& p_collider, const double p_deltaTime);
	};
}