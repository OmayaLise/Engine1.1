#pragma once

#include "MyMaths.hpp"

namespace Physics
{
	class Transform
	{
		// Attribute
	public:
		Core::Maths::Mat4 matrix;

		// Local Matrix
		Core::Maths::Vec3 translation;
		Core::Maths::Vec3 scale;
		Core::Maths::Vec3 rotation;

		// Methode
	public:
		Transform(const Core::Maths::Vec3& p_translate = Core::Maths::Vec3(0.f, 0.f, 0.f), const Core::Maths::Vec3& p_scale = Core::Maths::Vec3(1.f, 1.f, 1.f), const Core::Maths::Vec3 & p_rotation = Core::Maths::Vec3(0.f, 0.f, 0.f));

		// Get and Set
		const Core::Maths::Mat4& GetLocalTransform();
	};
}
