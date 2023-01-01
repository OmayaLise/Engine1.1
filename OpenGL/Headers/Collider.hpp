#pragma once

#include "Model.hpp"
#include "IComponent.hpp"
#include "Transform.hpp"
#include "Rigidbody.hpp"
namespace Physics
{
	class Collider : public Core::DataStructure::IComponent
	{
	public:

		// Attributes
		Core::Maths::Vec3 center;
		Rigidbody* rbLink;
		Physics::Transform* ptransform = nullptr;
		Physics::Transform colliderTransform;
		LowRenderer::Model m_meshCollider = {};
	
		bool isTrigger = false;
		bool kinematic = false;
		
		// Methods
		Collider(Transform* p_tranform, bool p_enable);
		Collider(Resources::Mesh* p_mesh, Resources::Shader* p_shader, bool p_isStatic);
		~Collider();


		Core::Maths::Vec3 GetWorldCenter();
		virtual void DrawCollider(const Core::Maths::Mat4& p_mvp);
		virtual bool HasCollide();
		virtual void SetCollide(const bool p_state);
		virtual Core::Maths::Mat4 GetColliderMatrix();

		const bool GetHasCollide() const { return m_hasCollide; };

		// Attributes
	protected:
		Core::Maths::Mat4 m_matrixCollider;
		bool m_hasCollide;
	};


	class BoxCollider : public Collider
	{
	public:
		//Attribute
		Core::Maths::Vec3 extents = { 1,1,1 };
		Core::Maths::Vec3 normals[3] = { {1.0f,0,0}, {0,1.0f,0}, {0,0,1.0f} };

		
		//Methods
		BoxCollider(Resources::Mesh* p_mesh, Resources::Shader* p_shader,bool p_isStatic);
		~BoxCollider();
		
		void DrawCollider(const Core::Maths::Mat4& p_mvp) override;

		Core::Maths::Mat4 GetColliderMatrix();
		Core::Maths::Vec3 GetExtents();
		Core::Maths::Vec3 GetMinPos();
		Core::Maths::Vec3 GetMaxPos();
	};

	class SphereCollider : public Collider
	{
	public:
		// Attributes
		float radius = 1;

		//  Methods
		SphereCollider(Resources::Mesh* p_mesh, Resources::Shader* p_shader, bool p_isStatic);
		~SphereCollider();

		float GetRadius();
		void DrawCollider(const Core::Maths::Mat4& p_mvp) override;
		Core::Maths::Mat4 GetColliderMatrix() override; 
	};

	class CapsuleCollider : public Collider
	{
	public:
		//Attibutes
		Core::Maths::Vec3 extents = { 1,1,1 };
		//Methods
		CapsuleCollider(Resources::Mesh* p_mesh, Resources::Shader* p_shader, bool p_isStatic);
		~CapsuleCollider();
		void DrawCollider(const Core::Maths::Mat4& p_mvp) override;
	};

}