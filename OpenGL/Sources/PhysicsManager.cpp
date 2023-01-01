#include "PhysicManager.hpp"


#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Physics
{


	PhysicsManager::PhysicsManager()
	{
	}

	PhysicsManager::~PhysicsManager()
	{
		for (unsigned int i = 0; i < colliders.size(); i++)
			delete colliders[i];
	}

	Collider* PhysicsManager::CreateCollider(Resources::Mesh* p_mesh,Resources::Shader* p_shader,ColliderTypes p_types,bool p_kinematic)
	{
		Collider* coll = nullptr;
		switch (p_types)
		{
		case Physics::ColliderTypes::Box:

			coll = new BoxCollider(p_mesh,p_shader,p_kinematic);
			colliders.push_back(coll);
			break;
		case Physics::ColliderTypes::Collider:
			coll = new Collider(p_mesh,p_shader,p_kinematic);
			colliders.push_back(coll);
			break;
		case Physics::ColliderTypes::Sphere:
			coll = new SphereCollider(p_mesh,p_shader,p_kinematic);
			colliders.push_back(coll);
			break;
		case Physics::ColliderTypes::Capsule:
			coll = new CapsuleCollider(p_mesh,p_shader,p_kinematic);
			colliders.push_back(coll);
			break;
		default:
			break;
		}
		return coll;
	}

	//TODO : 
	// Replace by deltaTime
	// Clean the collision Update 
	//


	void PhysicsManager::UpdateCollision(const double p_deltaTime)
	{
		for (size_t i = 0; i < colliders.size(); i++)
		{
			colliders[i]->rbLink->UpdateForce(p_deltaTime);
		}

		for (size_t i = 0; i < colliders.size(); i++)
			colliders[i]->SetCollide(false);

		for (size_t j = 0; j < colliders.size(); j++)
		{
			//colliders[j]->SetCollide(false);
			for (size_t i = 1 + j; i < colliders.size(); i++)
			{

				TestCollider<BoxCollider,BoxCollider>(*colliders[j],*colliders[i]);
				TestCollider<SphereCollider,SphereCollider>(*colliders[j],*colliders[i]);
				TestCollider<BoxCollider,SphereCollider>(*colliders[j],*colliders[i]);
			
			}
		}

		for (size_t i = 0; i < colliders.size(); i++)
		{
			//TODO : Replace by deltaTime
			colliders[i]->rbLink->Update(p_deltaTime);
		}

	}


	



	void PhysicsManager::DrawColliders(Core::Maths::Mat4& p_vp)
	{
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		for (size_t i = 0; i < colliders.size(); i++)
		{
			colliders[i]->DrawCollider((p_vp * colliders[i]->GetColliderMatrix()));
		}
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	}
}