#pragma once
#include "Collider.hpp"
#include <array>
namespace Physics
{
	enum KinematicState
	{
		None,
		Collider1,
		Collider2,
		Both
	};

	class Collisions
	{
	public:
		Collisions();
		~Collisions();
		static bool CollisionSphereSphere(SphereCollider& p_sphere1, SphereCollider& p_sphere2);
		static bool CollisionSphereBox(SphereCollider& p_sphere, BoxCollider& p_box);
		static bool CollisionBoxBox(BoxCollider& p_box1, BoxCollider& p_box2);

	private:
		static Core::Maths::Vec3 GetBoxBoxDir(BoxCollider& p_box1, BoxCollider& p_box2);
		static float GetBoxBoxDistance(BoxCollider& p_box1, BoxCollider& p_box2, const Core::Maths::Vec3& p_dir);
		static Core::Maths::Vec3 GetBoxResolutionDirection(BoxCollider& p_box, const Core::Maths::Vec3& p_positionObj);
		static bool CompareCubeColliderDirection(BoxCollider& p_box, const Core::Maths::Vec3& p_axeDirection, const unsigned int p_index, Core::Maths::Vec3 p_positionCollider);
		static Core::Maths::Vec3 GetNearestPoint(SphereCollider& p_sphere, BoxCollider& p_box);
		static bool TestCollisionsSphereBox(SphereCollider& p_sphere, BoxCollider& p_box, float& p_distance, float& p_radius, Core::Maths::Vec3& p_neareastPoint);
		static bool IsSphereCenterInsideBox(SphereCollider& p_sphere, BoxCollider& p_box, const Core::Maths::Vec3& p_neareastPoint, Core::Maths::Vec3& p_direction);
		static void GetRepulsionVector(SphereCollider& p_sphere, BoxCollider& p_box, float& p_power, Core::Maths::Vec3& p_repulseDirection, const float& p_distance, const Core::Maths::Vec3& p_nearestPoint);
		static KinematicState TestKinematicState(const Collider& p_collider1, const Collider& p_collider2);
		static void ResolvePhycicsInteraction(Collider& p_collider, const Core::Maths::Vec3& p_resolveDirection, const float p_power);
		static bool IsBoxBoxCollisioning(BoxCollider& p_box1,BoxCollider& p_box2);
	};





}