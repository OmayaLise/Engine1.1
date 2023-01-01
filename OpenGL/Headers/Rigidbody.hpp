#pragma once

#include "Transform.hpp"
#include "IComponent.hpp"
namespace Physics
{

	// TODO 
	// + Is to set as a component
	//

	class Rigidbody : public Core::DataStructure::IComponent
	{
	public:
		// Attributes
		Core::Maths::Vec3 velocity;
		Core::Maths::Vec3 gravityVelocity;
		Core::Maths::Vec3 angularVelocity;

		bool useGravity = true;
		bool isKinematic = false;

		// Methods
		Rigidbody( Transform* p_transform, bool p_enable = true);
		~Rigidbody();
		
		void SetGravity(const Core::Maths::Vec3& p_gravity);
		void AddForceImpulse(const Core::Maths::Vec3& p_force);
		void AddAngularForceImpulse(const Core::Maths::Vec3& p_force);
		void UpdateForce(const double& deltaTime);
		void Update(const double& deltaTime);

		Transform* GetTransform() { return m_transform; };
		const Core::Maths::Vec3& GetGravityForce() { return m_gravityForce; };

	private:

		// Attibutes
		Core::Maths::Vec3 m_gravityForce = { 0.0f, -9.81f,0.f };
		Transform* m_transform;

		// Methode
		void VelocityDecrease(const double& deltaTime);
	};


}