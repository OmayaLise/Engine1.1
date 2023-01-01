#pragma once
#include "Collider.hpp"
#include "Collision.hpp"
#include "Log.hpp"

namespace Physics
{

	enum class ColliderTypes
	{
		Box,
		Collider,
		Sphere,
		Capsule,
	};
	class PhysicsManager
	{
	public:
		PhysicsManager();
		~PhysicsManager();

		std::vector<Collider*> colliders;

		Collider* CreateCollider(Resources::Mesh* p_mesh, Resources::Shader* p_shader, ColliderTypes p_types, bool p_kinematic);
		void UpdateCollision(const double p_deltaTime);
		void DrawColliders( Core::Maths::Mat4& p_vp);

	private:
		
		template<class T,class I> bool TestCollision(T a,I b) { Core::Debug::Log::Print("This collision setuo isn't possible"); return false; };
		template<> bool TestCollision < SphereCollider,SphereCollider>(SphereCollider a,SphereCollider b) { return Collisions::CollisionSphereSphere(a,b); }
		template<> bool TestCollision < SphereCollider,BoxCollider>(SphereCollider a,BoxCollider b) { return Collisions::CollisionSphereBox(a,b); }
		template<> bool TestCollision < BoxCollider,SphereCollider>(BoxCollider a,SphereCollider b) { return Collisions::CollisionSphereBox(b,a); }
		template<> bool TestCollision < BoxCollider,BoxCollider>(BoxCollider a,BoxCollider b) { return Collisions::CollisionBoxBox(a,b); }
		
		template<class T,class I> void TestCollider(Collider& a,Collider& b);
	};
	
#include "PhysicsManager.inl"


}
