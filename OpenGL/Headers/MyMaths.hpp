#pragma once

#include <iostream>
#include <cmath>
#include <corecrt_math_defines.h>

namespace Core::Maths
{
    const float RAD2DEG = 180.f / M_PI;
    const float DEG2RAD = M_PI / 180.f;

    float Clamp(const float value, const float min, const float max);

    template <typename T>
    T Min(const T& a, const T& b);

    template <typename T>
    T Max(const T& a, const T& b);

    template <typename T>
    T Abs(const T& a);

    template <typename T>
    T Lerp(const float t, const T& a, const T& b);

    // ----------------------------------------------------------------------------------
    // -------------------------------------- Vec2 --------------------------------------
    // ----------------------------------------------------------------------------------

    class Vec2
    {
    public:
        float x;
        float y;

        Vec2(const float x = 0.f, const float y = 0.f);
        Vec2(const Vec2& copy);

        float DotProduct(const Vec2& Vec2) const;
        float Magnitude() const;
        float CrossProduct(const Vec2& Vec2) const;
        Vec2& Normalize();

        void Display() const;
        std::string ToString() const;

        friend Vec2 operator+(const Vec2& left, const Vec2& right);
        friend Vec2 operator-(const Vec2& left, const Vec2& right);
        friend Vec2 operator*(const Vec2& left, const float multiplier);
        friend Vec2 operator/(const Vec2& left, const float divider);

        friend Vec2& operator+=(Vec2& left, const Vec2& right);
        friend Vec2& operator-=(Vec2& left, const Vec2& right);
        friend Vec2& operator*=(Vec2& left, const float multipler);
        friend Vec2& operator/=(Vec2& left, const float divider);

        friend bool operator==(const Vec2& left, const Vec2& right);
        friend bool operator!=(const Vec2& left, const Vec2& right);

        friend bool operator<(const Vec2& left, const Vec2& right);
        friend bool operator<=(const Vec2& left, const Vec2& right);
        friend bool operator>(const Vec2& left, const Vec2& right);
        friend bool operator>=(const Vec2& left, const Vec2& right);
    };
    // Friends Vec4
    Vec2 operator+(const Vec2& left, const Vec2& right);
    Vec2 operator-(const Vec2& left, const Vec2& right);
    Vec2 operator*(const Vec2& Vec2, const float multiplier);
    Vec2 operator/(const Vec2& left, const float divider);

    Vec2& operator+=(Vec2& left, const Vec2& right);
    Vec2& operator-=(Vec2& left, const Vec2& right);
    Vec2& operator*=(Vec2& left, const float multipler);
    Vec2& operator/=(Vec2& left, const float divider);

    bool operator==(const Vec2& left, const Vec2& right);
    bool operator!=(const Vec2& left, const Vec2& right);

    bool operator<(const Vec2& left, const Vec2& right);
    bool operator<=(const Vec2& left, const Vec2& right);
    bool operator>(const Vec2& left, const Vec2& right);
    bool operator>=(const Vec2& left, const Vec2& right);

    // ----------------------------------------------------------------------------------
    // -------------------------------------- Vec3 --------------------------------------
    // ----------------------------------------------------------------------------------

    class Vec3
    {
    public:
        union 
        {
            struct 
            {
            float x;
            float y;
            float z;

            };

            float coord[3];

        };

        Vec3(const float x = 0.f, const float y = 0.f, const float z = 0.f);
        Vec3(const Vec3& copy);

        float DotProduct(const Vec3& vec3) const;
        float Magnitude() const;
        Vec3 CrossProduct(const Vec3& vec3) const;
        Vec3& Normalize();

        void Display() const;
        std::string ToString() const;

        friend Vec3 operator+(const Vec3& left, const Vec3& right);
        friend Vec3 operator-(const Vec3& left, const Vec3& right);
        friend Vec3 operator-(const Vec3 right);
        friend Vec3 operator*(const Vec3& left, const float multiplier);
        friend Vec3 operator/(const Vec3& left, const float divider);

        friend Vec3& operator+=(Vec3& left, const Vec3& right);
        friend Vec3& operator-=(Vec3& left, const Vec3& right);
        friend Vec3& operator*=(Vec3& left, const float multipler);
        friend Vec3& operator/=(Vec3& left, const float divider);

        friend bool operator==(const Vec3& left, const Vec3& right);
        friend bool operator!=(const Vec3& left, const Vec3& right);

        friend bool operator<(const Vec3& left, const Vec3& right);
        friend bool operator<=(const Vec3& left, const Vec3& right);
        friend bool operator>(const Vec3& left, const Vec3& right);
        friend bool operator>=(const Vec3& left, const Vec3& right);
    };

    // Friends Vec3
    Vec3 operator+(const Vec3& left, const Vec3& right);
    Vec3 operator-(const Vec3& left, const Vec3& right);
    Vec3 operator-(const Vec3 right);
    Vec3 operator*(const Vec3& Vec3, const float multiplier);
    Vec3 operator/(const Vec3& left, const float divider);

    Vec3& operator+=(Vec3& left, const Vec3& right);
    Vec3& operator-=(Vec3& left, const Vec3& right);
    Vec3& operator*=(Vec3& left, const float multipler);
    Vec3& operator/=(Vec3& left, const float divider);

    bool operator==(const Vec3& left, const Vec3& right);
    bool operator!=(const Vec3& left, const Vec3& right);

    bool operator<(const Vec3& left, const Vec3& right);
    bool operator<=(const Vec3& left, const Vec3& right);
    bool operator>(const Vec3& left, const Vec3& right);
    bool operator>=(const Vec3& left, const Vec3& right);

    // ----------------------------------------------------------------------------------
    // -------------------------------------- Vec4 --------------------------------------
    // ----------------------------------------------------------------------------------

    class Vec4
    {
    public:
        float x;
        float y;
        float z;
        float w;

        Vec4(const float x = 0.f, const float y = 0.f, const float z = 0.f, const float w = 0.f);
        Vec4(const Vec3 v3, const float w = 0.f);
        Vec4(const Vec4& copy);

        float DotProduct(const Vec4& Vec4) const;
        float Magnitude();
        float CrossProduct(const Vec4& Vec4) const;
        Vec4& Normalize();
        void Homogenize();
        Vec3 ToVec3();

        void Display() const;
        std::string ToString() const;

        friend Vec4 operator+(const Vec4& left, const Vec4& right);
        friend Vec4 operator-(const Vec4& left, const Vec4& right);
        friend Vec4 operator*(const Vec4& left, const float multiplier);
        friend Vec4 operator/(const Vec4& left, const float divider);

        friend Vec4& operator+=(Vec4& left, const Vec4& right);
        friend Vec4& operator-=(Vec4& left, const Vec4& right);
        friend Vec4& operator*=(Vec4& left, const float multipler);
        friend Vec4& operator/=(Vec4& left, const float divider);

        friend bool operator==(const Vec4& left, const Vec4& right);
        friend bool operator!=(const Vec4& left, const Vec4& right);

        friend bool operator<(const Vec4& left, const Vec4& right);
        friend bool operator<=(const Vec4& left, const Vec4& right);
        friend bool operator>(const Vec4& left, const Vec4& right);
        friend bool operator>=(const Vec4& left, const Vec4& right);
        
    };
    // Friends Vec4
    Vec4 operator+(const Vec4& left, const Vec4& right);
    Vec4 operator-(const Vec4& left, const Vec4& right);
    Vec4 operator*(const Vec4& Vec4, const float multiplier);
    Vec4 operator/(const Vec4& left, const float divider);

    Vec4& operator+=(Vec4& left, const Vec4& right);
    Vec4& operator-=(Vec4& left, const Vec4& right);
    Vec4& operator*=(Vec4& left, const float multipler);
    Vec4& operator/=(Vec4& left, const float divider);

    bool operator==(const Vec4& left, const Vec4& right);
    bool operator!=(const Vec4& left, const Vec4& right);

    bool operator<(const Vec4& left, const Vec4& right);
    bool operator<=(const Vec4& left, const Vec4& right);
    bool operator>(const Vec4& left, const Vec4& right);
    bool operator>=(const Vec4& left, const Vec4& right);

    // ----------------------------------------------------------------------------------
    // -------------------------------------- Mat4 --------------------------------------
    // ----------------------------------------------------------------------------------

    class Mat4 //Rows then Columns
    {
    public:
        float mat[4][4];

        Mat4(const float p_value = 0.f);
        Mat4(const Mat4& p_other);
        Mat4(const float p_f1, const float p_f2, const float p_f3, const float p_f4,
            const float p_f5, const float p_f6, const float p_f7, const float p_f8,
            const float p_f9, const float p_f10, const float p_f11, const float p_f12,
            const float p_f13, const float p_f14, const float p_f15, const float p_f16);
        ~Mat4() {}

        static Mat4 Identity();

        Mat4 Transpose();
        Mat4 GetInverse() const;

        float Determinant() const;
        Mat4 CofactorMatrix() const;

        void Display() const;
        const std::string& ToString() const;

        Mat4 operator+(const Mat4& other);
        Mat4 operator-(const Mat4& other);
        const Mat4 operator*(const Mat4& other) const;
        Vec4 operator*(const Vec4& other);
        Mat4 operator*(const float other);

        static Mat4 CreateTranslationMatrix(const Vec3& translation);
        static Mat4 CreateScaleMatrix(const Vec3& scale);
        static Mat4 CreateXRotationMatrix(float angle);
        static Mat4 CreateYRotationMatrix(float angle);
        static Mat4 CreateZRotationMatrix(float angle);
        static Mat4 CreateRotationMatrix(const Vec3& angle);

        static Mat4 CreateTransformationMatrix(const Vec3& translation, const Vec3& scale, const Vec3& rotation);

        static Vec3 GetPositionFromMatrix(const Mat4& matrix);
        static Vec3 GetRotationFromMatrix(const Mat4& matrix);
        static Vec3 GetScaleFromMatrix(Mat4 matrix);
    };

    bool operator==(const Mat4& left, const Mat4& right);


    // ---------------------------- Methods ---------------------

    Vec3 CrossProduct(const Vec3& v1, const Vec3& v2) ;
    float Max(const float& a, const float& b);
    float Min(const float& a, const float& b);
}