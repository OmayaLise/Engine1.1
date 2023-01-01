#include "Transform.hpp"

namespace Physics
{
	Transform::Transform(const Core::Maths::Vec3& p_translate, const Core::Maths::Vec3& p_scale, const Core::Maths::Vec3& p_rotation)
		: matrix(Core::Maths::Mat4::Identity())
		, translation(p_translate)
		, scale (p_scale)
		, rotation(p_rotation)
	{
	}

	const Core::Maths::Mat4& Transform::GetLocalTransform()
	{
		return Core::Maths::Mat4::CreateTransformationMatrix(translation, scale, rotation);
	}
}