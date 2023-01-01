#include "Camera.hpp"

namespace LowRenderer
{
	Camera::Camera(const int p_width, const int p_height)
		: far(100.f)
		, near(0.1f)
		, FOV(100.f)
		, speed(0.1f)
		, aspect((float)p_width / (float)p_height)
		, player(nullptr)
		, up()
		, GameObject("Camera", Physics::Transform(-5.f, 0.f, 0.f))
	{
		CalculateProjectionMatrix();
	}

	void Camera::Update(const Core::Inputs& p_Inputs, const double p_deltaTime, const Physics::Transform& p_transformParent)
	{
		transform.translation = Core::Maths::Vec3(cosf(rotationAroundPlayer.y) * radiusPlayer, 4.f, sinf(rotationAroundPlayer.y) * radiusPlayer) + p_transformParent.translation;

		UpdateInputs(p_Inputs);

		CalculateViewMatrix();
	}

	Core::Maths::Mat4& Camera::GetViewProjection()
	{
		Core::Maths::Mat4 vp = projectionMatrix.matrix * viewMatrix.matrix;
		return vp;
	}

	void Camera::UpdateInputs(const Core::Inputs& p_inputs)
	{
		rotationAroundPlayer.y += p_inputs.deltaX / 500.f;
		rotationAroundPlayer.x += p_inputs.deltaY / 6.f;
		
		if (rotationAroundPlayer.y < -360.f)
			rotationAroundPlayer.y = 360.f;

		if (rotationAroundPlayer.y > 360.f)
			rotationAroundPlayer.y = -360.f;

		if (rotationAroundPlayer.x < -15.f)
			rotationAroundPlayer.x = -15.f;

		if (rotationAroundPlayer.x > 15.f)
			rotationAroundPlayer.x = 15.f;

		Core::Maths::Vec3 newFront = -(transform.translation - player->GetTranslation());
		front = newFront.Normalize(); 
		// also re-calculate the Right and Up vector
		right = front.CrossProduct({ 0,1,0 }).Normalize();  
		// normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		up = right.CrossProduct(front).Normalize();
	}

	Core::Maths::Mat4 Camera::LookAt(const Core::Maths::Vec3& eye, const Core::Maths::Vec3& center, const Core::Maths::Vec3& up)
	{
		Core::Maths::Vec3 f = (center - eye).Normalize();
		Core::Maths::Vec3 s = f.CrossProduct(up).Normalize();
		Core::Maths::Vec3 u = s.CrossProduct(f);

		Core::Maths::Mat4 Result = Core::Maths::Mat4::Identity();
		Result.mat[0][0] = s.x;
		Result.mat[1][0] = s.y;
		Result.mat[2][0] = s.z;
		Result.mat[0][1] = u.x;
		Result.mat[1][1] = u.y;
		Result.mat[2][1] = u.z;
		Result.mat[0][2] = -f.x;
		Result.mat[1][2] = -f.y;
		Result.mat[2][2] = -f.z;
		Result.mat[3][0] = -s.DotProduct(eye);
		Result.mat[3][1] = -u.DotProduct(eye);
		Result.mat[3][2] = f.DotProduct(eye);

		Result = Result.Transpose();
		return Result;
	}

	void Camera::CalculateViewMatrix()
	{
		viewMatrix.matrix = LookAt(transform.translation, transform.translation + front, up);
	}

	void Camera::CalculateProjectionMatrix()
	{
		float a = 1.f / tanf(Core::Maths::DEG2RAD * FOV / 2.f);

		Core::Maths::Mat4 projection(
			a / aspect, 0.f, 0.f,						   0.f,
			0.f,		a,	 0.f,						   0.f,
			0.f,		0.f, -(far + near) / (far - near), -(2 * far * near) / (far - near),
			0.f,		0.f, -1.f,						   0.f
		);
		projectionMatrix.matrix = projection;
	}
}