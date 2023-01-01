#include "PlayerControler.hpp"

namespace Gameplay::Player
{
	PlayerControler::PlayerControler(const float p_speed, const float p_jumpHeight)
		: forwardCam(nullptr)
		, rightCam(nullptr)
		, speed(p_speed)
		, jumpHeight(p_jumpHeight)
	{
		isEnable = false;
	}

	void PlayerControler::Update(const Core::Inputs& p_inputs, Physics::Rigidbody& p_rb, const Physics::Collider& p_collider, Core::Maths::Vec3& p_position, const double p_deltaTime)
	{
		Move(p_inputs, p_rb);
		Jump(p_inputs, p_rb, p_collider, p_deltaTime);
		DeathZone(p_position);

	}

	void PlayerControler::Move(const Core::Inputs& p_inputs, Physics::Rigidbody& p_rb)
	{
		Physics::Transform* transform = p_rb.GetTransform();

		Core::Maths::Vec3 move = Core::Maths::Vec3(0.f, p_rb.velocity.y, 0.f);

		float YRotation;
		if (forwardCam->x > 0 && forwardCam->z >= 0)
			YRotation = atanf(forwardCam->z / forwardCam->x);
		else if (forwardCam->x > 0 && forwardCam->z < 0)
			YRotation = atanf(forwardCam->z / forwardCam->x) + 2 * M_PI;
		else if (forwardCam->x < 0)
			YRotation = atanf(forwardCam->z / forwardCam->x) + M_PI;
		else if (forwardCam->x == 0 && forwardCam->z > 0)
			YRotation = M_PI_2;
		else
			YRotation = -M_PI_2;

		if (p_inputs.moveForward)
		{
			move.x += speed * forwardCam->x;
			move.z += speed * forwardCam->z;
			p_rb.GetTransform()->rotation.y = -YRotation * Core::Maths::RAD2DEG + 90;
		}

		if (p_inputs.moveBackward)
		{
			move.x -= speed * forwardCam->x;
			move.z -= speed * forwardCam->z;
			p_rb.GetTransform()->rotation.y = YRotation * Core::Maths::RAD2DEG + 270;
		}

		if (p_inputs.moveLeft)
		{
			move.x -= speed * rightCam->x;
			move.z -= speed * rightCam->z;
			p_rb.GetTransform()->rotation.y = -YRotation * Core::Maths::RAD2DEG + 180;

		}

		if (p_inputs.moveRight)
		{
			move.x += speed * rightCam->x;
			move.z += speed * rightCam->z;
			p_rb.GetTransform()->rotation.y = -YRotation * Core::Maths::RAD2DEG;

		}

		if (p_inputs.moveUp)
			move.y += speed;

		if (p_inputs.moveDown)
			move.y -= speed;

		p_rb.velocity = move;
	}

	void PlayerControler::Jump(const Core::Inputs& p_inputs, Physics::Rigidbody& p_rb, const Physics::Collider& p_collider, const double p_deltaTime)
	{
		canJump = CheckJumpCondition(p_collider, p_deltaTime);

		if (p_inputs.jump && p_rb.velocity.y <= 0 && canJump)
		{

			p_rb.AddForceImpulse({ 0.f, jumpHeight, 0.f });
			p_rb.GetTransform()->translation += Core::Maths::Vec3(0.f, 0.1f, 0.f);
		}
	}

	void PlayerControler::DeathZone(Core::Maths::Vec3& p_position)
	{
		if (p_position.y <= deathZoneHeightLimit)
		{
			p_position = startPosition;
		}
	}

	bool PlayerControler::CheckJumpCondition(const Physics::Collider& p_collider, const double p_deltaTime)
	{
		if (p_collider.GetHasCollide())
		{
			coyoteCountdown = 0;
			return true;
		}
		else if(coyoteCountdown < coyoteTimer)
		{
			coyoteCountdown += p_deltaTime;
			return true;
		}
		return false;
	}
}