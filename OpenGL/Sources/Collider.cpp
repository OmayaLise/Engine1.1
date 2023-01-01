
#include "Collider.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Physics
{




	Collider::Collider(Transform* p_tranform, bool p_enable)
		: ptransform(p_tranform)
	{
		isEnable = p_enable;
	}

	Collider::Collider(Resources::Mesh* p_mesh, Resources::Shader* p_shader, bool p_isStatic)
		: m_meshCollider(p_mesh, p_shader), kinematic(p_isStatic)
	{

	}

	Collider::~Collider()
	{
	}

	Core::Maths::Vec3 Collider::GetWorldCenter()
	{
		return  (Core::Maths::Mat4::GetPositionFromMatrix(ptransform->GetLocalTransform()) + center);
	}

	void Collider::DrawCollider(const Core::Maths::Mat4& p_mvp)
	{
		if (!isEnable) return;
		glUseProgram(m_meshCollider.GetShaderProgram());
		m_meshCollider.Draw(GetColliderMatrix(), p_mvp);
	}

	bool Collider::HasCollide()
	{
		return m_hasCollide;
	}

	void Collider::SetCollide(const bool p_state)
	{
		m_hasCollide = p_state;
	}

	Core::Maths::Mat4 Collider::GetColliderMatrix()
	{
		m_matrixCollider = Core::Maths::Mat4::CreateTransformationMatrix(center, { 1,1,1 }, { 0,0,0 });
		m_matrixCollider = ptransform->GetLocalTransform() * m_matrixCollider;
		return m_matrixCollider;
	}

	BoxCollider::BoxCollider(Resources::Mesh* p_mesh, Resources::Shader* p_shader, bool p_isStatic)
		:Collider(p_mesh, p_shader, p_isStatic)
	{

	}


	BoxCollider::~BoxCollider()
	{
	}

	void BoxCollider::DrawCollider(const Core::Maths::Mat4& p_mvp)
	{
		if (isEnable)
		{
			glUseProgram(m_meshCollider.GetShaderProgram());
			m_meshCollider.Draw(GetColliderMatrix(), p_mvp);
		}
	}

	Core::Maths::Mat4 BoxCollider::GetColliderMatrix()
	{
		m_matrixCollider = Core::Maths::Mat4::CreateTransformationMatrix(center, extents, { 0,0,0 });
		m_matrixCollider = ptransform->GetLocalTransform() * m_matrixCollider;
		return m_matrixCollider;
	}

	Core::Maths::Vec3 BoxCollider::GetExtents()
	{
		Core::Maths::Mat4 mat = Core::Maths::Mat4::CreateScaleMatrix(extents);
		mat = Core::Maths::Mat4::CreateTransformationMatrix(ptransform->translation, ptransform->scale, ptransform->rotation) * mat;
		Core::Maths::Vec3 val = Core::Maths::Mat4::GetScaleFromMatrix(mat);

		return val;
	}

	Core::Maths::Vec3 BoxCollider::GetMaxPos()
	{
		return GetWorldCenter() + GetExtents();
	}

	Core::Maths::Vec3 BoxCollider::GetMinPos()
	{
		return GetWorldCenter() - GetExtents();
	}

	SphereCollider::SphereCollider(Resources::Mesh* p_mesh, Resources::Shader* p_shader, bool p_isStatic)
		:Collider(p_mesh, p_shader,p_isStatic)
	{

	}

	SphereCollider::~SphereCollider()
	{
		
	}


	Core::Maths::Mat4 SphereCollider::GetColliderMatrix()
	{
		Core::Maths::Mat4 mat = Core::Maths::Mat4::CreateTransformationMatrix(center, { radius,radius,radius }, { 0,0,0 });
		mat = ptransform->GetLocalTransform() * mat;
		return mat;
	}

	float SphereCollider::GetRadius()
	{
		Core::Maths::Mat4 mat = Core::Maths::Mat4::CreateScaleMatrix({ radius,radius,radius });
		mat =  Core::Maths::Mat4::CreateScaleMatrix(ptransform->scale) * mat;
		float val = Core::Maths::Mat4::GetScaleFromMatrix(mat).x;
		return val;
	}
			
	void SphereCollider::DrawCollider(const Core::Maths::Mat4& p_mvp)
	{
		if (isEnable)
		{
			glUseProgram(m_meshCollider.GetShaderProgram());
			
			m_meshCollider.Draw(GetColliderMatrix(), p_mvp);
		}
	}

	CapsuleCollider::CapsuleCollider(Resources::Mesh* p_mesh, Resources::Shader* p_shader, bool p_isStatic)
		:Collider(p_mesh, p_shader, p_isStatic)
	{

	}

	CapsuleCollider::~CapsuleCollider()
	{
	}

	void CapsuleCollider::DrawCollider(const Core::Maths::Mat4& p_mvp)
	{
		if (isEnable)
		{
			glUseProgram(m_meshCollider.GetShaderProgram());
			m_meshCollider.Draw(ptransform->GetLocalTransform(), p_mvp);
		}
	}
}