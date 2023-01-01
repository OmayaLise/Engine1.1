#include "Rigidbody.hpp"

namespace Physics
{


	Rigidbody::Rigidbody( Transform* p_transform, bool p_enable)
		: m_transform(p_transform)
	{
		isEnable = p_enable;
	}

	Rigidbody::~Rigidbody()
	{
	}

	void Rigidbody::SetGravity(const Core::Maths::Vec3& p_gravity)
	{
		m_gravityForce = p_gravity;
		gravityVelocity =  {0, 0, 0};

	}
	void Rigidbody::AddForceImpulse(const Core::Maths::Vec3& p_force)
	{
		velocity += p_force;
	}
	void Rigidbody::AddAngularForceImpulse(const Core::Maths::Vec3& p_force)
	{
		angularVelocity += p_force;
	}
	void Rigidbody::UpdateForce(const double& deltaTime)
	{
		if (!isEnable) return;

		if (useGravity)
		{
			gravityVelocity += m_gravityForce * deltaTime;
		}
	}
	void Rigidbody::Update(const double& deltaTime)
	{
		if (!isEnable) return;

		m_transform->translation += velocity * deltaTime;
		m_transform->translation += gravityVelocity * deltaTime;
		m_transform->rotation += angularVelocity * deltaTime;

		VelocityDecrease(deltaTime);
	}

	void Rigidbody::VelocityDecrease(const double& deltaTime)
	{
		float gravity = 9.81f * deltaTime;

		if (velocity.x < 0.f)
		{
			if(velocity.x + gravity > 0.f)
				velocity.x = 0.f;
			else
				velocity.x += gravity;
		}
		else if( velocity.x > 0.f)
		{
			if (velocity.x - gravity < 0.f)
				velocity.x = 0.f;
			else
				velocity.x -= gravity;
		}

		if (velocity.y < 0.f)
		{
			if (velocity.y + gravity > 0.f)
				velocity.y = 0.f;
			else
				velocity.y += gravity;
		}
		else if (velocity.y > 0.f)
		{
			if (velocity.y - gravity < 0.f)
				velocity.y = 0.f;
			else
				velocity.y -= gravity;
		}

		if (velocity.z < 0.f)
		{
			if (velocity.z + gravity > 0.f)
				velocity.z = 0.f;
			else
				velocity.z += gravity;
		}
		else if (velocity.z > 0.f)
		{
			if (velocity.z - gravity < 0.f)
				velocity.z = 0.f;
			else
				velocity.z -= gravity;
		}
	}
}