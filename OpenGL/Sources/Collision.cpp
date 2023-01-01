#include "Collision.hpp"

namespace Physics
{
	Collisions::Collisions()
	{
	}

	Collisions::~Collisions()
	{
	}


	bool Collisions::CollisionSphereSphere(SphereCollider& p_sphere1, SphereCollider& p_sphere2)
	{
		float dist = (p_sphere1.GetWorldCenter() - p_sphere2.GetWorldCenter()).Magnitude();
		float radDist = (p_sphere1.GetRadius() + p_sphere2.GetRadius());


		if (dist <= radDist)
		{
			float value = radDist - dist;
			Core::Maths::Vec3 dir = (p_sphere1.GetWorldCenter() - p_sphere2.GetWorldCenter()).Normalize();

			KinematicState kinematicState = TestKinematicState(p_sphere1, p_sphere2);
			switch (kinematicState)
			{
			case Physics::Both:

				return true;

				break;

			case Physics::Collider1:

				p_sphere2.ptransform->translation += -dir * value;
				return true;

				break;

			case Physics::Collider2:

				p_sphere1.ptransform->translation += dir * value;
				return true;

				break;

			case Physics::None:

				p_sphere2.ptransform->translation += -dir * (value / 2);
				p_sphere1.ptransform->translation += dir * (value / 2);
				return true;

				break;

			default:
				break;
			}


		}
		return false;
	}

	bool Collisions::CompareCubeColliderDirection(BoxCollider& p_box, const Core::Maths::Vec3& p_axeDirection, const unsigned int p_index, Core::Maths::Vec3 p_positionCollider)
	{
		Core::Maths::Vec3 boxCenter = p_box.GetWorldCenter();
		Core::Maths::Vec3 boxExtents = p_box.GetExtents();
		Core::Maths::Vec3 pos = boxCenter + p_axeDirection * boxExtents.coord[p_index];
		Core::Maths::Vec3 dirTest = (p_positionCollider - pos).Normalize();

		float distance = (p_positionCollider - pos).Magnitude();
		float dot = p_axeDirection.DotProduct(dirTest);

		return (dot > 0);
	}

	Core::Maths::Vec3 Collisions::GetBoxResolutionDirection(BoxCollider& p_box, const Core::Maths::Vec3& p_positionCollider)
	{
		Core::Maths::Vec3 direction = { 0,0,0 };
		for (int i = 0; i < 3; i++)
		{
			Core::Maths::Vec3 axeDirection;
			axeDirection.coord[i] = p_box.extents.coord[i];
			axeDirection.Normalize();

			if (CompareCubeColliderDirection(p_box, axeDirection, i, p_positionCollider))
			{
				direction.coord[i] = axeDirection.coord[i];

			}
			if (CompareCubeColliderDirection(p_box, -axeDirection, i, p_positionCollider))
			{
				direction.coord[i] += axeDirection.coord[i];
			}
		}
		return direction;

	}

	Core::Maths::Vec3 Collisions::GetNearestPoint(SphereCollider& p_sphere, BoxCollider& p_box)
	{
		Core::Maths::Vec3 nearestPoint;
		for (size_t i = 0; i < 3; i++)
		{
			nearestPoint.coord[i] = Core::Maths::Max(p_box.GetMinPos().coord[i], Core::Maths::Min(p_sphere.GetWorldCenter().coord[i], p_box.GetMaxPos().coord[i]));
		}
		return nearestPoint;
	}

	bool Collisions::TestCollisionsSphereBox(SphereCollider& p_sphere, BoxCollider& p_box, float& p_distance, float& p_radius, Core::Maths::Vec3& p_neareastPoint)
	{
		Core::Maths::Vec3 center = p_sphere.GetWorldCenter();
		p_neareastPoint = GetNearestPoint(p_sphere, p_box);
		p_distance = (p_neareastPoint - center).Magnitude();
		p_radius = p_sphere.GetRadius();

		return (p_distance < p_radius);
	}

	bool Collisions::IsSphereCenterInsideBox(SphereCollider& p_sphere, BoxCollider& p_box, const Core::Maths::Vec3& p_neareastPoint, Core::Maths::Vec3& p_direction)
	{
		Core::Maths::Vec3 dirCenter = p_box.GetWorldCenter() - p_sphere.GetWorldCenter();
		Core::Maths::Vec3 dirPoint = (p_neareastPoint - p_sphere.GetWorldCenter()).Normalize();

		dirCenter.Normalize();
		p_direction = dirPoint;

		return	dirCenter.DotProduct(dirPoint) > 0;
	}

	void Collisions::GetRepulsionVector(SphereCollider& p_sphere, BoxCollider& p_box, float& p_power, Core::Maths::Vec3& p_repulseDirection, const float& p_distance, const Core::Maths::Vec3& p_nearestPoint)
	{
		if (IsSphereCenterInsideBox(p_sphere, p_box, p_nearestPoint, p_repulseDirection))
		{
			p_repulseDirection = -(p_nearestPoint - p_sphere.GetWorldCenter()).Normalize();
			p_power = p_sphere.GetRadius() - p_distance;
		}
		else
		{
			p_repulseDirection = (p_nearestPoint - p_box.GetWorldCenter()).Normalize();
			p_power = (p_sphere.GetRadius() + p_sphere.GetRadius()) - p_distance;

		}
	}

	KinematicState Collisions::TestKinematicState(const Collider& p_collider1, const Collider& p_collider2)
	{
		if (p_collider1.kinematic && p_collider2.kinematic) return KinematicState::Both;
		if (p_collider1.kinematic) return KinematicState::Collider1;
		if (p_collider2.kinematic) return KinematicState::Collider2;
		return KinematicState::None;
	}

	void Collisions::ResolvePhycicsInteraction(Collider& p_collider, const Core::Maths::Vec3& p_resolveDirection, const float p_power)
	{

		Core::Maths::Vec3 vel = p_collider.rbLink->velocity;
		Core::Maths::Vec3 vel2 = p_collider.rbLink->gravityVelocity;
		float dot = p_resolveDirection.DotProduct(vel.Normalize());
		float dot2 = p_resolveDirection.DotProduct(vel2.Normalize());

		p_collider.ptransform->translation += p_resolveDirection * p_power;
		p_collider.rbLink->gravityVelocity = p_collider.rbLink->gravityVelocity * (1 - fabs(dot2));
		p_collider.rbLink->velocity = p_collider.rbLink->velocity * (1 - fabs(dot));
	}

	bool Collisions::CollisionSphereBox(SphereCollider& p_sphere, BoxCollider& p_box)
	{

		Core::Maths::Vec3 nearestPoint;
		float distance;
		float radius;

		// If collision is true
		if (TestCollisionsSphereBox(p_sphere, p_box, distance, radius, nearestPoint))
		{
			// Resulsion Force Calcul
			float power = radius - distance;
			Core::Maths::Vec3 repulseDirection;
			GetRepulsionVector(p_sphere, p_box, power, repulseDirection, distance, nearestPoint);

			KinematicState kinematicState = TestKinematicState(p_sphere, p_box);

			switch (kinematicState)
			{
			case Physics::Both:
				return true;
				break;
			case Physics::Collider1:

				ResolvePhycicsInteraction(p_box, repulseDirection, power);
				return true;

				break;
			case Physics::Collider2:

				ResolvePhycicsInteraction(p_sphere, repulseDirection, power);
				return true;

				break;
			case Physics::None:

				ResolvePhycicsInteraction(p_sphere, repulseDirection, power);
				ResolvePhycicsInteraction(p_box, repulseDirection, power);
				return true;

				break;
			default:
				break;
			}

			return true;
		}
		return false;
	}


	Core::Maths::Vec3 Collisions::GetBoxBoxDir(BoxCollider& box1, BoxCollider& box2)
	{
		Core::Maths::Vec3 dirVeloticy = GetBoxResolutionDirection(box1, box2.GetWorldCenter());
		return dirVeloticy.Normalize();
	}

	float Collisions::GetBoxBoxDistance(BoxCollider& box1, BoxCollider& box2, const Core::Maths::Vec3& dir)
	{
		Core::Maths::Vec3 centerDir = box1.GetWorldCenter() - box2.GetWorldCenter();
		Core::Maths::Vec3 extentDir = box1.GetExtents() + box2.GetExtents();
		Core::Maths::Vec3 boxVelocity = box2.rbLink->velocity + box2.rbLink->gravityVelocity;

		for (size_t i = 0; i < 3; i++)
		{
			centerDir.coord[i] = centerDir.coord[i] * dir.coord[i];
			extentDir.coord[i] = extentDir.coord[i] * dir.coord[i];
		}
		return (extentDir.Magnitude() - centerDir.Magnitude());
	}

	bool Collisions::IsBoxBoxCollisioning(BoxCollider& p_box1,BoxCollider& p_box2)
	{
		Core::Maths::Vec3 c1 = p_box1.GetWorldCenter();
		Core::Maths::Vec3 c2 = p_box2.GetWorldCenter();

		Core::Maths::Vec3 e1 = p_box1.GetExtents();
		Core::Maths::Vec3 e2 = p_box2.GetExtents();

		if (!(c1.x - e1.x <= c2.x + e2.x &&
			c1.x + e1.x >= c2.x - e2.x))
			return false;

		if (!(c1.y - e1.y <= c2.y + e2.y &&
			c1.y + e1.y >= c2.y - e2.y))
			return false;

		if (!(c1.z - e1.z <= c2.z + e2.z &&
			c1.z + e1.z >= c2.z - e2.z))
			return false;

		return true;
	}

	bool Collisions::CollisionBoxBox(BoxCollider& p_box1, BoxCollider& p_box2)
	{
		if (!IsBoxBoxCollisioning(p_box1,p_box2)) return false;
		

		KinematicState kinematicState = TestKinematicState(p_box1,p_box2);


		if (kinematicState == KinematicState::Both)
		{
			p_box1.rbLink->gravityVelocity = { 0,0,0 };
			p_box1.rbLink->velocity = { 0,0,0 };
			p_box2.rbLink->gravityVelocity = { 0,0,0 };
			p_box2.rbLink->velocity = { 0,0,0 };
			return true;
		}
		if (kinematicState == KinematicState::Collider1)
		{
			Core::Maths::Vec3 dirVelocity = GetBoxBoxDir(p_box1, p_box2);
			float distance = GetBoxBoxDistance(p_box1, p_box2, dirVelocity);
			p_box2.ptransform->translation += dirVelocity * distance;
			p_box2.rbLink->gravityVelocity = { 0,0,0 };
			p_box2.rbLink->velocity = { 0,0,0 };
			return true;
		}
		if (kinematicState == KinematicState::Collider2)
		{
			Core::Maths::Vec3 dirVelocity = GetBoxBoxDir(p_box2, p_box1);
			float distance = GetBoxBoxDistance(p_box2, p_box1, dirVelocity);
			p_box1.ptransform->translation += dirVelocity * distance;
			p_box1.rbLink->gravityVelocity = { 0,0,0 };
			p_box1.rbLink->velocity = { 0,0,0 };
			return true;
		}

		Core::Maths::Vec3 dirVelocity1 = GetBoxBoxDir(p_box1, p_box2);
		float distance1 = GetBoxBoxDistance(p_box1, p_box2, dirVelocity1);

		Core::Maths::Vec3 dirVelocity2 = GetBoxBoxDir(p_box2, p_box1);
		float distance2 = GetBoxBoxDistance(p_box2, p_box1, dirVelocity2);
		

		p_box1.ptransform->translation += dirVelocity2 * (distance2 / 2);
		p_box1.rbLink->gravityVelocity = { 0,0,0 };
		p_box1.rbLink->velocity = { 0,0,0 };

		// Re-use Physics Resolution function

		p_box2.ptransform->translation += dirVelocity1 * (distance1 / 2);


		return true;
	}
}