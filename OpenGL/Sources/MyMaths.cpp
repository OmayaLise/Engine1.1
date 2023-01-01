#include "MyMaths.hpp"

#include <string> // ToString methode

namespace Core::Maths
{
	float Clamp(const float value, const float min, const float max)
	{
		if (value < min)
			return min;
		if (value > max)
			return max;
		return value;
	}

	template <typename T>
	T Min(const T& a, const T& b)
	{
		return a < b ? a : b;
	}

	template <typename T>
	T Max(const T& a, const T& b)
	{
		return a > b ? a : b;
	}

	template <typename T>
	T Abs(const T& a)
	{
		return a < 0 ? -a : a;
	}

	template <typename T>
	T Lerp(const float t, const T& a, const T& b)
	{
		return t * a + (1 - t) * b;
	}

	// ----------------------------------------------------------------------------------
	// -------------------------------------- Vec2 --------------------------------------
	// ----------------------------------------------------------------------------------

	Vec2::Vec2(const float x, const float y)
		: x(x), y(y)
	{
	}

	Vec2::Vec2(const Vec2& copy)
		: x(copy.x), y(copy.y)
	{
	}

	float Vec2::DotProduct(const Vec2& vec2) const
	{
		return x * vec2.x + y * vec2.y;
	}

	float Vec2::Magnitude() const
	{
		return sqrtf(powf(x, 2) + powf(y, 2));
	}

	float Vec2::CrossProduct(const Vec2& vec2) const
	{
		return x * vec2.y - y * vec2.x;
	}

	Vec2& Vec2::Normalize()
	{
		float magnitude = Magnitude();
		x *= (1 / magnitude);
		y *= (1 / magnitude);
		return *this;
	}

	void Vec2::Display() const
	{
		std::cout << "[ " << x << ", " << y << " ]" << std::endl;
	}

	std::string Vec2::ToString() const
	{
		return "[ " + std::to_string(x) + ", " + std::to_string(y) + " ]";
	}

	// Friend Vec2
	Vec2 operator+(const Vec2& left, const Vec2& right)
	{
		return { left.x + right.x, left.y + right.y };
	}

	Vec2 operator-(const Vec2& left, const Vec2& right)
	{
		return { left.x - right.x, left.y - right.y };
	}

	Vec2 operator*(const Vec2& left, const float multiplier)
	{
		return { left.x * multiplier, left.y * multiplier };
	}

	Vec2 operator/(const Vec2& left, const float divider)
	{
		return { left.x / divider, left.y / divider };
	}

	Vec2& operator+=(Vec2& left, const Vec2& right)
	{
		left = left + right;
		return left;
	}

	Vec2& operator-=(Vec2& left, const Vec2& right)
	{
		left = left - right;
		return left;
	}

	Vec2& operator*=(Vec2& left, const float multipler)
	{
		left = left * multipler;
		return left;
	}

	Vec2& operator/=(Vec2& left, const float divider)
	{
		left = left / divider;
		return left;
	}

	bool operator==(const Vec2& left, const Vec2& right)
	{
		if (left.x <= right.x + 0.001f && left.x >= right.x - 0.001f && left.y <= right.y + 0.001f && left.y >= right.y - 0.001f)
			return true;
		else
			return false;
	}

	bool operator!=(const Vec2& left, const Vec2& right)
	{
		if (left.x <= right.x + 0.001f && left.x >= right.x - 0.001f && left.y <= right.y + 0.001f && left.y >= right.y - 0.001f)
			return false;
		else
			return true;
	}

	bool operator<(const Vec2& left, const Vec2& right)
	{
		if (left.x < right.x && left.y < right.y)
			return true;
		else
			return false;
	}

	bool operator<=(const Vec2& left, const Vec2& right)
	{
		if (left.x <= right.x && left.y <= right.y)
			return true;
		else
			return false;
	}

	bool operator>(const Vec2& left, const Vec2& right)
	{
		if (left.x > right.x && left.y > right.y)
			return true;
		else
			return false;
	}

	bool operator>=(const Vec2& left, const Vec2& right)
	{
		if (left.x >= right.x && left.y >= right.y)
			return true;
		else
			return false;
	}

	// ----------------------------------------------------------------------------------
	// -------------------------------------- Vec3 --------------------------------------
	// ----------------------------------------------------------------------------------



	Vec3::Vec3(const float x, const float y, const float z)
		: x(x), y(y), z(z)
	{
	}

	Vec3::Vec3(const Vec3& copy)
		: x(copy.x), y(copy.y), z(copy.z)
	{
	}

	float Vec3::DotProduct(const Vec3& vec3) const
	{
		return x * vec3.x + y * vec3.y + z * vec3.z;
	}

	float Vec3::Magnitude() const
	{
		return sqrtf(powf(x, 2) + powf(y, 2) + powf(z, 2));
	}

	Vec3 Vec3::CrossProduct(const Vec3& vec3) const
	{
		return { (y * vec3.z) - (z * vec3.y), (z * vec3.x) - (x * vec3.z), (x * vec3.y) - (y * vec3.x) };
	}

	Vec3& Vec3::Normalize()
	{
		float magnitude = Magnitude();
		if (magnitude != 0.0f && magnitude != NAN)
		{
			x *= (1 / magnitude);
			y *= (1 / magnitude);
			z *= (1 / magnitude);
		}
		return *this;
	}

	void Vec3::Display() const
	{
		std::cout << "[ " << x << ", " << y << ", " << z << " ]" << std::endl;
	}

	std::string Vec3::ToString() const
	{
		return "[ " + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + " ]";
	}

	// Friend Vec3
	Vec3 operator+(const Vec3& left, const Vec3& right)
	{
		return { left.x + right.x, left.y + right.y, left.z + right.z };
	}

	Vec3 operator-(const Vec3& left, const Vec3& right)
	{
		return { left.x - right.x, left.y - right.y, left.z - right.z };
	}

	Vec3 operator-(const Vec3 right)
	{
		return { -right.x, -right.y, -right.z };
	}

	Vec3 operator*(const Vec3& left, const float multiplier)
	{
		return { left.x * multiplier, left.y * multiplier, left.z * multiplier };
	}

	Vec3 operator/(const Vec3& left, const float divider)
	{
		return { left.x / divider, left.y / divider, left.z / divider };
	}

	Vec3& operator+=(Vec3& left, const Vec3& right)
	{
		left = left + right;
		return left;
	}

	Vec3& operator-=(Vec3& left, const Vec3& right)
	{
		left = left - right;
		return left;
	}

	Vec3& operator*=(Vec3& left, const float multipler)
	{
		left = left * multipler;
		return left;
	}

	Vec3& operator/=(Vec3& left, const float divider)
	{
		left = left / divider;
		return left;
	}

	bool operator==(const Vec3& left, const Vec3& right)
	{
		if (left.x <= right.x + 0.001f && left.x >= right.x - 0.001f && left.y <= right.y + 0.001f && left.y >= right.y - 0.001f && left.z <= right.z + 0.001f && left.z >= right.z - 0.001f)
			return true;
		else
			return false;
	}

	bool operator!=(const Vec3& left, const Vec3& right)
	{
		if (left.x <= right.x + 0.001f && left.x >= right.x - 0.001f && left.y <= right.y + 0.001f && left.y >= right.y - 0.001f && left.z <= right.z + 0.001f && left.z >= right.z - 0.001f)
			return false;
		else
			return true;
	}

	bool operator<(const Vec3& left, const Vec3& right)
	{
		if (left.x < right.x && left.y < right.y && left.z < right.z)
			return true;
		else
			return false;
	}

	bool operator<=(const Vec3& left, const Vec3& right)
	{
		if (left.x <= right.x && left.y <= right.y && left.z <= right.z)
			return true;
		else
			return false;
	}

	bool operator>(const Vec3& left, const Vec3& right)
	{
		if (left.x > right.x && left.y > right.y && left.z > right.z)
			return true;
		else
			return false;
	}

	bool operator>=(const Vec3& left, const Vec3& right)
	{
		if (left.x >= right.x && left.y >= right.y && left.z >= right.z)
			return true;
		else
			return false;
	}

	// ----------------------------------------------------------------------------------
	// -------------------------------------- Vec4 --------------------------------------
	// ----------------------------------------------------------------------------------

	Vec4::Vec4(const float x, const float y, const float z, const float w)
		: x(x), y(y), z(z), w(w)
	{
	}

	Vec4::Vec4(const Vec3 v3, const float w)
		: x(v3.x), y(v3.y), z(v3.z), w(w)
	{
	}

	Vec4::Vec4(const Vec4& copy)
		: x(copy.x), y(copy.y), z(copy.z), w(copy.w)
	{
	}

	float Vec4::DotProduct(const Vec4& vec4) const
	{
		return x * vec4.x + y * vec4.y + z * vec4.z + w * vec4.w;
	}

	float Vec4::Magnitude()
	{
		return sqrtf(powf(x, 2) + powf(y, 2) + powf(z, 2) + powf(w, 2));
	}

	float Vec4::CrossProduct(const Vec4& vec4) const
	{
		return ((x * vec4.x + x * vec4.y + x * vec4.z + x * vec4.w) + (y * vec4.x + y * vec4.y + y * vec4.z + y * vec4.w) + (z * vec4.x + z * vec4.y + z * vec4.z + z * vec4.w) + (w * vec4.x + w * vec4.y + w * vec4.z + w * vec4.w));
	}

	Vec4& Vec4::Normalize()
	{
		float magnitude = Magnitude();
		x *= (1 / magnitude);
		y *= (1 / magnitude);
		z *= (1 / magnitude);
		w *= (1 / magnitude);
		return *this;
	}

	void Vec4::Homogenize()
	{
		if (w != 0)
		{
			x /= w;
			y /= w;
			z /= w;
			w /= w;
		}
	}

	Vec3 Vec4::ToVec3()
	{
		return { x, y, z };
	}

	void Vec4::Display() const
	{
		std::cout << "[ " << x << ", " << y << ", " << z << ", " << w << " ]" << std::endl;
	}

	std::string Vec4::ToString() const
	{
		return "[ " + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ", " + std::to_string(w) + " ]";
	}

	// Friend Vec4
	Vec4 operator+(const Vec4& left, const Vec4& right)
	{
		return { left.x + right.x, left.y + right.y, left.z + right.z, left.w + right.w };
	}

	Vec4 operator-(const Vec4& left, const Vec4& right)
	{
		return { left.x - right.x, left.y - right.y, left.z - right.z, left.w - right.w };
	}

	Vec4 operator*(const Vec4& left, const float multiplier)
	{
		return { left.x * multiplier, left.y * multiplier, left.z * multiplier, left.w * multiplier };
	}

	Vec4 operator/(const Vec4& left, const float divider)
	{
		return { left.x / divider, left.y / divider, left.z / divider, left.w / divider };
	}

	Vec4& operator+=(Vec4& left, const Vec4& right)
	{
		left = left + right;
		return left;
	}

	Vec4& operator-=(Vec4& left, const Vec4& right)
	{
		left = left - right;
		return left;
	}

	Vec4& operator*=(Vec4& left, const float multipler)
	{
		left = left * multipler;
		return left;
	}

	Vec4& operator/=(Vec4& left, const float divider)
	{
		left = left / divider;
		return left;
	}

	bool operator==(const Vec4& left, const Vec4& right)
	{
		if (left.x <= right.x + 0.001f && left.x >= right.x - 0.001f && left.y <= right.y + 0.001f && left.y >= right.y - 0.001f && left.z <= right.z + 0.001f && left.z >= right.z - 0.001f && left.w <= right.w + 0.001f && left.w >= right.w - 0.001f)
			return true;
		else
			return false;
	}

	bool operator!=(const Vec4& left, const Vec4& right)
	{
		if (left.x <= right.x + 0.001f && left.x >= right.x - 0.001f && left.y <= right.y + 0.001f && left.y >= right.y - 0.001f && left.z <= right.z + 0.001f && left.z >= right.z - 0.001f && left.w <= right.w + 0.001f && left.w >= right.w - 0.001f)
			return false;
		else
			return true;
	}

	bool operator<(const Vec4& left, const Vec4& right)
	{
		if (left.x < right.x && left.y < right.y && left.z < right.z && left.w < right.w)
			return true;
		else
			return false;
	}

	bool operator<=(const Vec4& left, const Vec4& right)
	{
		if (left.x <= right.x && left.y <= right.y && left.z <= right.z && left.w <= right.w)
			return true;
		else
			return false;
	}

	bool operator>(const Vec4& left, const Vec4& right)
	{
		if (left.x > right.x && left.y > right.y && left.z > right.z && left.w > right.w)
			return true;
		else
			return false;
	}

	bool operator>=(const Vec4& left, const Vec4& right)
	{
		if (left.x >= right.x && left.y >= right.y && left.z >= right.z && left.w >= right.w)
			return true;
		else
			return false;
	}

	// -------------------------------------- Mat4 --------------------------------------

	/*Mat4::Mat4(const float p_value)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				mat[i][j] = p_value;
			}
		}
	}

	Mat4::Mat4(const Mat4& p_other)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				mat[i][j] = p_other.mat[i][j];
			}
		}
	}

	Mat4::Mat4(const float p_f1, const float p_f2, const float p_f3, const float p_f4,
		const float p_f5,  const float p_f6,  const float p_f7,  const float p_f8,
		const float p_f9,  const float p_f10, const float p_f11, const float p_f12,
		const float p_f13, const float p_f14, const float p_f15, const float p_f16)
	{
		mat[0][0] = p_f1;  mat[0][1] = p_f2;  mat[0][2] = p_f3;  mat[0][3] = p_f4;
		mat[1][0] = p_f5;  mat[1][1] = p_f6;  mat[1][2] = p_f7;  mat[1][3] = p_f8;
		mat[2][0] = p_f9;  mat[2][1] = p_f10; mat[2][2] = p_f11; mat[2][3] = p_f12;
		mat[3][0] = p_f13; mat[3][1] = p_f14; mat[3][2] = p_f15; mat[3][3] = p_f16;
	}

	Mat4 Mat4::Identity()
	{
		Mat4 identity;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (i == j)
					identity.mat[i][j] = 1.f;
			}
		}
		return identity;
	}

	void Mat4::Transpose()
	{
		float tmp;
		for (int i = 0; i < 4; i++)
		{
			for (int j = i + 1; j < 4; j++)
			{
				tmp = mat[i][j];
				mat[i][j] = mat[j][i];
				mat[j][i] = tmp;
			}
		}
	}

	Mat4 Mat4::GetInverse() const
	{
		Mat4 inverse;
		float determinant = Determinant();

		if (determinant == 0)
			return Mat4::Identity();

		Mat4 cofactorMatrix = CofactorMatrix();
		cofactorMatrix.Transpose();
		cofactorMatrix = cofactorMatrix * (1.f / determinant);
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				inverse.mat[j][i] = cofactorMatrix.mat[j][i];
			}
		}
		return inverse;
	}

	float Mat4::Determinant() const
	{
		return mat[0][0] * (mat[1][1] * (mat[2][2] * mat[3][3] - mat[2][3] * mat[3][2]) - mat[1][2] * (mat[2][1] * mat[3][3] - mat[3][1] * mat[2][3]) + mat[1][3] * (mat[2][1] * mat[3][2] - mat[2][2] * mat[3][1]))
			- mat[0][1] * (mat[1][0] * (mat[2][2] * mat[3][3] - mat[2][3] * mat[3][2]) - mat[1][2] * (mat[2][0] * mat[3][3] - mat[3][0] * mat[2][3]) + mat[1][3] * (mat[2][0] * mat[3][2] - mat[2][2] * mat[3][0]))
			+ mat[0][2] * (mat[1][0] * (mat[2][1] * mat[3][3] - mat[2][3] * mat[3][1]) - mat[1][1] * (mat[2][0] * mat[3][3] - mat[3][0] * mat[2][3]) + mat[1][3] * (mat[2][0] * mat[3][1] - mat[2][1] * mat[3][0]))
			- mat[0][3] * (mat[1][0] * (mat[2][1] * mat[3][2] - mat[2][2] * mat[3][1]) - mat[1][1] * (mat[2][0] * mat[3][2] - mat[3][0] * mat[2][2]) + mat[1][2] * (mat[2][0] * mat[3][1] - mat[2][1] * mat[3][0]));
	}

	Mat4 Mat4::CofactorMatrix() const
	{
		Mat4 Cof;

		Cof.mat[0][0] = mat[1][1] * (mat[2][2] * mat[3][3] - mat[3][2] * mat[2][3]) - mat[1][2] * (mat[2][1] * mat[3][3] - mat[3][1] * mat[2][3]) + mat[1][3] * (mat[2][1] * mat[3][2] - mat[2][2] * mat[3][1]);
		Cof.mat[0][1] = -(mat[1][0] * (mat[2][2] * mat[3][3] - mat[2][3] * mat[3][2]) - mat[1][2] * (mat[2][0] * mat[3][3] - mat[3][0] * mat[2][3]) + mat[1][3] * (mat[2][0] * mat[3][2] - mat[2][2] * mat[3][0]));
		Cof.mat[0][2] = mat[1][0] * (mat[2][1] * mat[3][3] - mat[2][3] * mat[3][1]) - mat[1][1] * (mat[2][0] * mat[3][3] - mat[3][0] * mat[2][3]) + mat[1][3] * (mat[2][0] * mat[3][1] - mat[2][1] * mat[3][0]);
		Cof.mat[0][3] = -(mat[1][0] * (mat[2][1] * mat[3][2] - mat[2][2] * mat[3][1]) - mat[1][1] * (mat[2][0] * mat[3][2] - mat[3][0] * mat[2][2]) + mat[1][2] * (mat[2][0] * mat[3][1] - mat[2][1] * mat[3][0]));

		Cof.mat[1][0] = -(mat[0][1] * (mat[2][2] * mat[3][3] - mat[3][2] * mat[2][3]) - mat[0][2] * (mat[2][1] * mat[3][3] - mat[3][1] * mat[2][3]) + mat[0][3] * (mat[2][1] * mat[3][2] - mat[2][2] * mat[3][1]));
		Cof.mat[1][1] = mat[0][0] * (mat[2][2] * mat[3][3] - mat[2][3] * mat[3][2]) - mat[0][2] * (mat[2][0] * mat[3][3] - mat[3][0] * mat[2][3]) + mat[0][3] * (mat[2][0] * mat[3][2] - mat[2][2] * mat[3][0]);
		Cof.mat[1][2] = -(mat[0][0] * (mat[2][1] * mat[3][3] - mat[2][3] * mat[3][1]) - mat[0][1] * (mat[2][0] * mat[3][3] - mat[3][0] * mat[2][3]) + mat[0][3] * (mat[2][0] * mat[3][1] - mat[2][1] * mat[3][0]));
		Cof.mat[1][3] = mat[0][0] * (mat[2][1] * mat[3][2] - mat[2][2] * mat[3][1]) - mat[0][1] * (mat[2][0] * mat[3][2] - mat[3][0] * mat[2][2]) + mat[0][2] * (mat[2][0] * mat[3][1] - mat[2][1] * mat[3][0]);

		Cof.mat[2][0] = mat[0][1] * (mat[1][2] * mat[3][3] - mat[3][2] * mat[1][3]) - mat[0][2] * (mat[1][1] * mat[3][3] - mat[3][1] * mat[1][3]) + mat[0][3] * (mat[1][1] * mat[3][2] - mat[1][2] * mat[3][1]);
		Cof.mat[2][1] = -(mat[0][0] * (mat[1][2] * mat[3][3] - mat[1][3] * mat[3][2]) - mat[0][2] * (mat[1][0] * mat[3][3] - mat[3][0] * mat[1][3]) + mat[0][3] * (mat[1][0] * mat[3][2] - mat[1][2] * mat[3][0]));
		Cof.mat[2][2] = mat[0][0] * (mat[1][1] * mat[3][3] - mat[1][3] * mat[3][1]) - mat[0][1] * (mat[1][0] * mat[3][3] - mat[3][0] * mat[1][3]) + mat[0][3] * (mat[1][0] * mat[3][1] - mat[1][1] * mat[3][0]);
		Cof.mat[2][3] = -(mat[0][0] * (mat[1][1] * mat[3][2] - mat[1][2] * mat[3][1]) - mat[0][1] * (mat[1][0] * mat[3][2] - mat[3][0] * mat[1][2]) + mat[0][2] * (mat[1][0] * mat[3][1] - mat[1][1] * mat[3][0]));

		Cof.mat[3][0] = -(mat[0][1] * (mat[1][2] * mat[2][3] - mat[2][2] * mat[1][3]) - mat[0][2] * (mat[1][1] * mat[2][3] - mat[2][1] * mat[1][3]) + mat[0][3] * (mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1]));
		Cof.mat[3][1] = mat[0][0] * (mat[1][2] * mat[2][3] - mat[1][3] * mat[2][2]) - mat[0][2] * (mat[1][0] * mat[2][3] - mat[2][0] * mat[1][3]) + mat[0][3] * (mat[1][0] * mat[2][2] - mat[1][2] * mat[2][0]);
		Cof.mat[3][2] = -(mat[0][0] * (mat[1][1] * mat[2][3] - mat[1][3] * mat[2][1]) - mat[0][1] * (mat[1][0] * mat[2][3] - mat[2][0] * mat[1][3]) + mat[0][3] * (mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0]));
		Cof.mat[3][3] = mat[0][0] * (mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1]) - mat[0][1] * (mat[1][0] * mat[2][2] - mat[2][0] * mat[1][2]) + mat[0][2] * (mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0]);

		return Cof;
	}

	Mat4 Mat4::CreateTranslationMatrix(const Vec3& translation)
	{
		Mat4 translationMatrix = Mat4::Identity();
		if (translation.x != 0.f)
			translationMatrix.mat[0][3] = translation.x;
		if (translation.y != 0.f)
			translationMatrix.mat[1][3] = translation.y;
		if (translation.z != 0.f)
			translationMatrix.mat[2][3] = translation.z;
		return translationMatrix;
	}

	Mat4 Mat4::CreateScaleMatrix(const Vec3& scale)
	{
		Mat4 scaleMatrix;
		scaleMatrix.mat[0][0] = scale.x;
		scaleMatrix.mat[1][1] = scale.y;
		scaleMatrix.mat[2][2] = scale.z;
		scaleMatrix.mat[3][3] = 1.f;
		return scaleMatrix;
	}

	Mat4 Mat4::CreateXRotationMatrix(float angle)
	{
		angle *= M_PI / 180.f;
		Mat4 xRotationMatrix = xRotationMatrix.Identity();
		xRotationMatrix.mat[1][1] = cosf(angle);
		xRotationMatrix.mat[1][2] = -sinf(angle);
		xRotationMatrix.mat[2][1] = sinf(angle);
		xRotationMatrix.mat[2][2] = cosf(angle);
		return xRotationMatrix;
	}

	Mat4 Mat4::CreateYRotationMatrix(float angle)
	{
		angle *= M_PI / 180.f;
		Mat4 yRotationMatrix = Mat4::Identity();
		yRotationMatrix.mat[0][0] = cosf(angle);
		yRotationMatrix.mat[0][2] = sinf(angle);
		yRotationMatrix.mat[2][0] = -sinf(angle);
		yRotationMatrix.mat[2][2] = cosf(angle);
		return yRotationMatrix;
	}

	Mat4 Mat4::CreateZRotationMatrix(float angle)
	{
		angle *= M_PI / 180.f;
		Mat4 zRotationMatrix = Mat4::Identity();
		zRotationMatrix.mat[0][0] = cosf(angle);
		zRotationMatrix.mat[0][1] = -sinf(angle);
		zRotationMatrix.mat[1][0] = sinf(angle);
		zRotationMatrix.mat[1][1] = cosf(angle);
		return zRotationMatrix;
	}

	Mat4 Mat4::CreateTransformationMatrix(const Vec3& translation, const Vec3& scale, const Vec3& rotation)
	{
		return CreateTranslationMatrix(translation) * CreateYRotationMatrix(rotation.y) * CreateXRotationMatrix(rotation.x) * CreateZRotationMatrix(rotation.z) * CreateScaleMatrix(scale);
	}

	void Mat4::Display()
	{
		for (int i = 0; i < 4; i++)
		{
			std::cout << "| ";
			for (int j = 0; j < 4; j++)
			{
				std::cout << mat[i][j] << " ";
			}
			std::cout << "|" << std::endl;
		}
		std::cout << std::endl;
	}

	std::string Mat4::ToString()
	{
		std::string result;
		for (int i = 0; i < 4; i++)
		{
			result += "| ";
			for (int j = 0; j < 4; j++)
			{
				result += std::to_string(mat[i][j]) + " ";
			}
			result += "|\n";
		}
		return result;
	}

	Mat4 Mat4::operator+(const Mat4& other)
	{
		Mat4 result;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				result.mat[i][j] = mat[i][j] + other.mat[i][j];
			}
		}
		return result;
	}

	Mat4 Mat4::operator-(const Mat4& other)
	{
		Mat4 result;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				result.mat[i][j] = mat[i][j] - other.mat[i][j];
			}
		}
		return result;
	}

	Mat4 Mat4::operator*(const Mat4& other)
	{
		Mat4 res;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				for (int k = 0; k < 4; k++)
				{
					res.mat[i][j] += mat[i][k] * other.mat[k][j];
				}
			}
		}
		return res;
	}

	Vec4 Mat4::operator*(const Vec4& other)
	{
		Vec4 res;
		res.x = mat[0][0] * other.x + mat[0][1] * other.y + mat[0][2] * other.z + mat[0][3] * other.w;
		res.y = mat[1][0] * other.x + mat[1][1] * other.y + mat[1][2] * other.z + mat[1][3] * other.w;
		res.z = mat[2][0] * other.x + mat[2][1] * other.y + mat[2][2] * other.z + mat[2][3] * other.w;
		res.w = mat[3][0] * other.x + mat[3][1] * other.y + mat[3][2] * other.z + mat[3][3] * other.w;
		return res;
	}

	Mat4 Mat4::operator*(const float other)
	{
		Mat4 res;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				res.mat[i][j] = mat[i][j] * other;
			}
		}
		return res;
	}

	bool operator==(const Mat4& left, const Mat4& right)
	{
		if (   left.mat[0][0] <= right.mat[0][0] + 0.001f && left.mat[0][0] >= right.mat[0][0] - 0.001f
			&& left.mat[1][0] <= right.mat[1][0] + 0.001f && left.mat[1][0] >= right.mat[1][0] - 0.001f
			&& left.mat[2][0] <= right.mat[2][0] + 0.001f && left.mat[2][0] >= right.mat[2][0] - 0.001f
			&& left.mat[3][0] <= right.mat[3][0] + 0.001f && left.mat[3][0] >= right.mat[3][0] - 0.001f
			&& left.mat[0][1] <= right.mat[0][1] + 0.001f && left.mat[0][1] >= right.mat[0][1] - 0.001f
			&& left.mat[1][1] <= right.mat[1][1] + 0.001f && left.mat[1][1] >= right.mat[1][1] - 0.001f
			&& left.mat[2][1] <= right.mat[2][1] + 0.001f && left.mat[2][1] >= right.mat[2][1] - 0.001f
			&& left.mat[3][1] <= right.mat[3][1] + 0.001f && left.mat[3][1] >= right.mat[3][1] - 0.001f
			&& left.mat[0][2] <= right.mat[0][2] + 0.001f && left.mat[0][2] >= right.mat[0][2] - 0.001f
			&& left.mat[1][2] <= right.mat[1][2] + 0.001f && left.mat[1][2] >= right.mat[1][2] - 0.001f
			&& left.mat[2][2] <= right.mat[2][2] + 0.001f && left.mat[2][2] >= right.mat[2][2] - 0.001f
			&& left.mat[3][2] <= right.mat[3][2] + 0.001f && left.mat[3][2] >= right.mat[3][2] - 0.001f
			&& left.mat[0][3] <= right.mat[0][3] + 0.001f && left.mat[0][3] >= right.mat[0][3] - 0.001f
			&& left.mat[1][3] <= right.mat[1][3] + 0.001f && left.mat[1][3] >= right.mat[1][3] - 0.001f
			&& left.mat[2][3] <= right.mat[2][3] + 0.001f && left.mat[2][3] >= right.mat[2][3] - 0.001f
			&& left.mat[3][3] <= right.mat[3][3] + 0.001f && left.mat[3][3] >= right.mat[3][3] - 0.001f)
			return true;
		else
			return false;
	}*/

	Mat4::Mat4(const float p_value)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				mat[i][j] = p_value;
			}
		}
	}

	Mat4::Mat4(const Mat4& other)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				mat[i][j] = other.mat[i][j];
			}
		}
	}

	Mat4::Mat4(const float f1, const float f2, const float f3, const float f4,
		const float f5, const float f6, const float f7, const float f8,
		const float f9, const float f10, const float f11, const float f12,
		const float f13, const float f14, const float f15, const float f16)
	{
		mat[0][0] = f1;  mat[0][1] = f2;  mat[0][2] = f3;  mat[0][3] = f4;
		mat[1][0] = f5;  mat[1][1] = f6;  mat[1][2] = f7;  mat[1][3] = f8;
		mat[2][0] = f9;  mat[2][1] = f10; mat[2][2] = f11; mat[2][3] = f12;
		mat[3][0] = f13; mat[3][1] = f14; mat[3][2] = f15; mat[3][3] = f16;
	}

	Mat4 Mat4::Identity()
	{
		Mat4 identity;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (i == j)
					identity.mat[i][j] = 1.f;
			}
		}
		return identity;
	}

	Mat4 Mat4::Transpose()
	{
		Mat4 transpose;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				transpose.mat[i][j] = mat[j][i];
			}
		}
		return transpose;
	}

	Mat4 Mat4::GetInverse() const
	{
		Mat4 inverse;
		float determinant = Determinant();
		if (determinant == 0)
			return Mat4::Identity();
		Mat4 cofactorMatrix = CofactorMatrix();
		cofactorMatrix.Transpose();
		cofactorMatrix = cofactorMatrix * (1.f / determinant);
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				inverse.mat[i][j] = cofactorMatrix.mat[i][j];
			}
		}
		return inverse;
	}

	float Mat4::Determinant() const
	{
		return mat[0][0] * (mat[1][1] * (mat[2][2] * mat[3][3] - mat[2][3] * mat[3][2]) - mat[1][2] * (mat[2][1] * mat[3][3] - mat[3][1] * mat[2][3]) + mat[1][3] * (mat[2][1] * mat[3][2] - mat[2][2] * mat[3][1]))
			- mat[0][1] * (mat[1][0] * (mat[2][2] * mat[3][3] - mat[2][3] * mat[3][2]) - mat[1][2] * (mat[2][0] * mat[3][3] - mat[3][0] * mat[2][3]) + mat[1][3] * (mat[2][0] * mat[3][2] - mat[2][2] * mat[3][0]))
			+ mat[0][2] * (mat[1][0] * (mat[2][1] * mat[3][3] - mat[2][3] * mat[3][1]) - mat[1][1] * (mat[2][0] * mat[3][3] - mat[3][0] * mat[2][3]) + mat[1][3] * (mat[2][0] * mat[3][1] - mat[2][1] * mat[3][0]))
			- mat[0][3] * (mat[1][0] * (mat[2][1] * mat[3][2] - mat[2][2] * mat[3][1]) - mat[1][1] * (mat[2][0] * mat[3][2] - mat[3][0] * mat[2][2]) + mat[1][2] * (mat[2][0] * mat[3][1] - mat[2][1] * mat[3][0]));
	}

	Mat4 Mat4::CofactorMatrix() const
	{
		Mat4 Cof;

		Cof.mat[0][0] = mat[1][1] * (mat[2][2] * mat[3][3] - mat[3][2] * mat[2][3]) - mat[1][2] * (mat[2][1] * mat[3][3] - mat[3][1] * mat[2][3]) + mat[1][3] * (mat[2][1] * mat[3][2] - mat[2][2] * mat[3][1]);
		Cof.mat[0][1] = -(mat[1][0] * (mat[2][2] * mat[3][3] - mat[2][3] * mat[3][2]) - mat[1][2] * (mat[2][0] * mat[3][3] - mat[3][0] * mat[2][3]) + mat[1][3] * (mat[2][0] * mat[3][2] - mat[2][2] * mat[3][0]));
		Cof.mat[0][2] = mat[1][0] * (mat[2][1] * mat[3][3] - mat[2][3] * mat[3][1]) - mat[1][1] * (mat[2][0] * mat[3][3] - mat[3][0] * mat[2][3]) + mat[1][3] * (mat[2][0] * mat[3][1] - mat[2][1] * mat[3][0]);
		Cof.mat[0][3] = -(mat[1][0] * (mat[2][1] * mat[3][2] - mat[2][2] * mat[3][1]) - mat[1][1] * (mat[2][0] * mat[3][2] - mat[3][0] * mat[2][2]) + mat[1][2] * (mat[2][0] * mat[3][1] - mat[2][1] * mat[3][0]));

		Cof.mat[1][0] = -(mat[0][1] * (mat[2][2] * mat[3][3] - mat[3][2] * mat[2][3]) - mat[0][2] * (mat[2][1] * mat[3][3] - mat[3][1] * mat[2][3]) + mat[0][3] * (mat[2][1] * mat[3][2] - mat[2][2] * mat[3][1]));
		Cof.mat[1][1] = mat[0][0] * (mat[2][2] * mat[3][3] - mat[2][3] * mat[3][2]) - mat[0][2] * (mat[2][0] * mat[3][3] - mat[3][0] * mat[2][3]) + mat[0][3] * (mat[2][0] * mat[3][2] - mat[2][2] * mat[3][0]);
		Cof.mat[1][2] = -(mat[0][0] * (mat[2][1] * mat[3][3] - mat[2][3] * mat[3][1]) - mat[0][1] * (mat[2][0] * mat[3][3] - mat[3][0] * mat[2][3]) + mat[0][3] * (mat[2][0] * mat[3][1] - mat[2][1] * mat[3][0]));
		Cof.mat[1][3] = mat[0][0] * (mat[2][1] * mat[3][2] - mat[2][2] * mat[3][1]) - mat[0][1] * (mat[2][0] * mat[3][2] - mat[3][0] * mat[2][2]) + mat[0][2] * (mat[2][0] * mat[3][1] - mat[2][1] * mat[3][0]);
		Cof.mat[2][0] = mat[0][1] * (mat[1][2] * mat[3][3] - mat[3][2] * mat[1][3]) - mat[0][2] * (mat[1][1] * mat[3][3] - mat[3][1] * mat[1][3]) + mat[0][3] * (mat[1][1] * mat[3][2] - mat[1][2] * mat[3][1]);
		Cof.mat[2][1] = -(mat[0][0] * (mat[1][2] * mat[3][3] - mat[1][3] * mat[3][2]) - mat[0][2] * (mat[1][0] * mat[3][3] - mat[3][0] * mat[1][3]) + mat[0][3] * (mat[1][0] * mat[3][2] - mat[1][2] * mat[3][0]));
		Cof.mat[2][2] = mat[0][0] * (mat[1][1] * mat[3][3] - mat[1][3] * mat[3][1]) - mat[0][1] * (mat[1][0] * mat[3][3] - mat[3][0] * mat[1][3]) + mat[0][3] * (mat[1][0] * mat[3][1] - mat[1][1] * mat[3][0]);
		Cof.mat[2][3] = -(mat[0][0] * (mat[1][1] * mat[3][2] - mat[1][2] * mat[3][1]) - mat[0][1] * (mat[1][0] * mat[3][2] - mat[3][0] * mat[1][2]) + mat[0][2] * (mat[1][0] * mat[3][1] - mat[1][1] * mat[3][0]));

		Cof.mat[3][0] = -(mat[0][1] * (mat[1][2] * mat[2][3] - mat[2][2] * mat[1][3]) - mat[0][2] * (mat[1][1] * mat[2][3] - mat[2][1] * mat[1][3]) + mat[0][3] * (mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1]));
		Cof.mat[3][1] = mat[0][0] * (mat[1][2] * mat[2][3] - mat[1][3] * mat[2][2]) - mat[0][2] * (mat[1][0] * mat[2][3] - mat[2][0] * mat[1][3]) + mat[0][3] * (mat[1][0] * mat[2][2] - mat[1][2] * mat[2][0]);
		Cof.mat[3][2] = -(mat[0][0] * (mat[1][1] * mat[2][3] - mat[1][3] * mat[2][1]) - mat[0][1] * (mat[1][0] * mat[2][3] - mat[2][0] * mat[1][3]) + mat[0][3] * (mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0]));
		Cof.mat[3][3] = mat[0][0] * (mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1]) - mat[0][1] * (mat[1][0] * mat[2][2] - mat[2][0] * mat[1][2]) + mat[0][2] * (mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0]);

		return Cof;
	}

	Mat4 Mat4::CreateTranslationMatrix(const Vec3& translation)
	{
		Mat4 translationMatrix = Mat4::Identity();
		if (translation.x != 0.f)
			translationMatrix.mat[0][3] = translation.x;
		if (translation.y != 0.f)
			translationMatrix.mat[1][3] = translation.y;
		if (translation.z != 0.f)
			translationMatrix.mat[2][3] = translation.z;
		return translationMatrix;
	}

	Mat4 Mat4::CreateScaleMatrix(const Vec3& scale)
	{
		Mat4 scaleMatrix;
		scaleMatrix.mat[0][0] = scale.x;
		scaleMatrix.mat[1][1] = scale.y;
		scaleMatrix.mat[2][2] = scale.z;
		scaleMatrix.mat[3][3] = 1.f;
		return scaleMatrix;
	}

	Mat4 Mat4::CreateXRotationMatrix(float angle)
	{
		angle *= M_PI / 180.f;
		Mat4 xRotationMatrix = Mat4::Identity();
		xRotationMatrix.mat[1][1] = cosf(angle);
		xRotationMatrix.mat[1][2] = -sinf(angle);
		xRotationMatrix.mat[2][1] = sinf(angle);
		xRotationMatrix.mat[2][2] = cosf(angle);
		return xRotationMatrix;
	}

	Mat4 Mat4::CreateYRotationMatrix(float angle)
	{
		angle *= M_PI / 180.f;
		Mat4 yRotationMatrix = Mat4::Identity();
		yRotationMatrix.mat[0][0] = cosf(angle);
		yRotationMatrix.mat[0][2] = sinf(angle);
		yRotationMatrix.mat[2][0] = -sinf(angle);
		yRotationMatrix.mat[2][2] = cosf(angle);
		return yRotationMatrix;
	}

	Mat4 Mat4::CreateZRotationMatrix(float angle)
	{
		angle *= M_PI / 180.f;
		Mat4 zRotationMatrix = Mat4::Identity();
		zRotationMatrix.mat[0][0] = cosf(angle);
		zRotationMatrix.mat[0][1] = -sinf(angle);
		zRotationMatrix.mat[1][0] = sinf(angle);
		zRotationMatrix.mat[1][1] = cosf(angle);
		return zRotationMatrix;
	}

	Mat4 Mat4::CreateRotationMatrix(const Vec3& angle)
	{
		return CreateYRotationMatrix(angle.y) * CreateXRotationMatrix(angle.x) * CreateZRotationMatrix(angle.z);
	}


	Mat4 Mat4::CreateTransformationMatrix(const Vec3& translation, const Vec3& scale, const Vec3& rotation)
	{
		return CreateTranslationMatrix(translation) * CreateYRotationMatrix(rotation.y) * CreateXRotationMatrix(rotation.x) * CreateZRotationMatrix(rotation.z) * CreateScaleMatrix(scale);
	}


	Vec3 Mat4::GetPositionFromMatrix(const Mat4& matrix)
	{
		Vec3 position;

		position.x = matrix.mat[0][3];
		position.y = matrix.mat[1][3];
		position.z = matrix.mat[2][3];

		return position;
	}

	Vec3 Mat4::GetScaleFromMatrix(Mat4 matrix)
	{
		Vec3 scale;
		for (int i = 0; i < 3; i++)
		{
			Vec3 xScale = Vec3(matrix.mat[0][i], matrix.mat[1][i], matrix.mat[2][i]);
			float length = xScale.Magnitude();
			scale.coord[i] = xScale.Magnitude();
			matrix.mat[0][i] = matrix.mat[0][i] / length;
			matrix.mat[1][i] = matrix.mat[1][i] / length;
			matrix.mat[2][i] = matrix.mat[2][i] / length;

		}

		return scale;

	}



	void Mat4::Display() const
	{
		for (int i = 0; i < 4; i++)
		{
			std::cout << "| ";
			for (int j = 0; j < 4; j++)
			{
				std::cout << mat[i][j] << " ";
			}
			std::cout << "|" << std::endl;
		}
		std::cout << std::endl;
	}

	const std::string& Mat4::ToString() const
	{
		std::string result;
		for (int i = 0; i < 4; i++)
		{
			result += "| ";
			for (int j = 0; j < 4; j++)
			{
				result += std::to_string(mat[i][j]) + " ";
			}
			result += "|\n";
		}
		return result;
	}

	Mat4 Mat4::operator+(const Mat4& other)
	{
		Mat4 result;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				result.mat[i][j] = mat[i][j] + other.mat[i][j];
			}
		}
		return result;
	}

	Mat4 Mat4::operator-(const Mat4& other)
	{
		Mat4 result;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				result.mat[i][j] = mat[i][j] - other.mat[i][j];
			}
		}
		return result;
	}

	const Mat4 Mat4::operator*(const Mat4& other) const
	{
		Mat4 res;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				for (int k = 0; k < 4; k++)
				{
					res.mat[i][j] += mat[i][k] * other.mat[k][j];
				}
			}
		}
		return res;
	}

	Vec4 Mat4::operator*(const Vec4& other)
	{
		Vec4 res;
		res.x = mat[0][0] * other.x + mat[0][1] * other.y + mat[0][2] * other.z + mat[0][3] * other.w;
		res.y = mat[1][0] * other.x + mat[1][1] * other.y + mat[1][2] * other.z + mat[1][3] * other.w;
		res.z = mat[2][0] * other.x + mat[2][1] * other.y + mat[2][2] * other.z + mat[2][3] * other.w;
		res.w = mat[3][0] * other.x + mat[3][1] * other.y + mat[3][2] * other.z + mat[3][3] * other.w;
		return res;
	}

	Mat4 Mat4::operator*(const float other)
	{
		Mat4 res;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				res.mat[i][j] = mat[i][j] * other;
			}
		}
		return res;
	}

	bool operator==(const Mat4& left, const Mat4& right)
	{
		float margin = 0.000001f;
		bool res = true;

		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				if (left.mat[i][j] > right.mat[i][j] + margin || left.mat[i][j] < right.mat[i][j] - margin)
				{
					res = false;
					break;
				}
			}
			if (res == false)
				break;
		}
		return res;
	}

	Vec3 CrossProduct(const Vec3& v1, const Vec3& v2)
	{
		return  v1.x * v2.y - v1.y * v2.x;
	}

	float Max(const float& a, const float& b)
	{
		if (a > b) return a;
		else return b;
		
	}
	float Min(const float& a, const float& b)
	{
		if (a < b) return a;
		else return b;
	}
}