#include "TestMyMaths.hpp"

// glm lib
#include<glm/matrix.hpp>
#include<glm/gtc/matrix_transform.hpp>
// my lib
#include "MyMaths.hpp"

#include "Assertion.hpp"

using namespace Core::Maths;

namespace Core::Debug
{
    void display(glm::mat4 matrix)
    {
        for (int i = 0; i < 4; i++)
        {
            std::cout << "| ";
            for (int j = 0; j < 4; j++)
            {
                std::cout << matrix[i][j] << " ";
            }
            std::cout << "|" << std::endl;
        }
        std::cout << std::endl;
    }

    Mat4 GlmMatToMat(const glm::mat4x4& mat)
    {
        return Mat4(
            mat[0][0], mat[1][0], mat[2][0], mat[3][0],
            mat[0][1], mat[1][1], mat[2][1], mat[3][1],
            mat[0][2], mat[1][2], mat[2][2], mat[3][2],
            mat[0][3], mat[1][3], mat[2][3], mat[3][3]);
    }

    Vec4 GlmVecToVec(const glm::vec4& vec)
    {
        return Vec4(vec.x, vec.y, vec.z, vec.w);
    }

    Vec3 GlmVecToVec(const glm::vec3& vec)
    {
        return Vec3(vec.x, vec.y, vec.z);
    }

	void TestMyMaths()
	{
        TestVec2();
        TestVec3();
        TestVec4();
        TestMat4();
	}

    // ----------------------------------------------------------------------------------
    // -------------------------------------- Vec2 --------------------------------------
    // ----------------------------------------------------------------------------------

    void TestVec2()
    {
        TestOperatorVec2();
        TestDotProductVec2();
        TestMagnitudeVec2();
        TestCrossProductVec2();
        TestNormalizeVec2();
        Log::Print("Vec2 : OK\n", Core::Debug::LogLevel::Test);
    }

    void TestOperatorVec2()
    {
        Vec2 v1(1.f, 1.f);
        Vec2 v2(1.f, 1.f);

        // Operator +
        Assertion(!(v1 + v2 != Vec2(2.f, 2.f)), "fail on operator + : " + v1.ToString() + " + " + v2.ToString());

        // Operator +=
        v1 += v2;
        Assertion(!(v1 != Vec2(2.f, 2.f)), "fail on operator += : " + v1.ToString() + " " + v2.ToString());

        // Operator -
        Assertion(!(v1 - v2 != Vec2(1.f, 1.f)), "fail on operator - : " + v1.ToString() + " - " + v2.ToString());

        // Operator -=
        v1 -= v2;
        Assertion(!(v1 != Vec2(1.f, 1.f)), "fail on operator -= : " + v1.ToString() + " " + v2.ToString());

        // Operator *
        Assertion(!(v1 * 2 != Vec2(2.f, 2.f)), "fail on operator * : " + v1.ToString() + " * " + v2.ToString());

        // Operator *=
        v1 *= 2;
        Assertion(!(v1 != Vec2(2.f, 2.f)), "fail on operator *= : " + v1.ToString() + " " + v2.ToString());

        // Operator /
        Assertion(!(v1 / 2 != Vec2(1.f, 1.f)), "fail on operator / : " + v1.ToString() + " / " + v2.ToString());

        // Operator /=
        v1 /= 2;
        Assertion(!(v1 != Vec2(1.f, 1.f)), "fail on operator /= : " + v1.ToString() + " " + v2.ToString());

        // Operator <
        Assertion(!(v1 < Vec2(0.9f, 0.9f)), "fail on operator < : " + v1.ToString() + " < Vec2(0.9f, 0.9f)");

        // Operator >
        Assertion(!(v1 > Vec2(1.1f, 1.1f)), "fail on operator > : " + v1.ToString() + " > Vec2(1.1f, 1.1f)");

        // Operator <=
        Assertion(v1 <= Vec2(1.f, 1.f), "fail on operator <= : " + v1.ToString() + " <= Vec2(1.f, 1.f)");

        // Operator >=
        Assertion(v1 >= Vec2(1.f, 1.f), "fail on operator >= : " + v1.ToString() + " >= Vec2(1.f, 1.f)");

        // Operator ==
        Assertion(v1 == v2, "fail on operator == : " + v1.ToString() + "==" + v2.ToString());
    }

    void TestDotProductVec2()
    {
        Vec2 v1(1.f, 4.f);
        Vec2 v2(2.f, 3.f);
        glm::vec2 v3(1.f, 4.f);
        glm::vec2 v4(2.f, 3.f);

        const float myResult = v1.DotProduct(v2);
        const float resultWanted = glm::dot(v3, v4);

        Assertion(myResult == resultWanted, "fail on dot product : " + std::to_string(myResult) + " == " + std::to_string(resultWanted));
    }

    void TestMagnitudeVec2()
    {
        Vec2 v1(4.f, 4.f);
        glm::vec2 v2(4.f, 4.f);

        const float myResult = v1.Magnitude();
        const float resultWanted = glm::length(v2);

        Assertion(myResult == resultWanted, "fail on magnitude : " + std::to_string(myResult) + " == " + std::to_string(resultWanted));
    }

    void TestCrossProductVec2()
    {
        Vec2 v1(5.f, 4.f);
        Vec2 v2(2.f, 3.f);

        const float myResult = v1.CrossProduct(v2);
        const float resultWanted = 7.f;

        Assertion(myResult == resultWanted, "fail on cross product : " + std::to_string(myResult) + " == " + std::to_string(resultWanted));
    }

    void TestNormalizeVec2()
    {
        Vec2 v1(4.f, 4.f);
        glm::vec2 v2(4.f, 4.f);

        v1.Normalize();
        v2 = glm::normalize(v2);

        Assertion(v1.x == v2.x && v1.y == v2.y, "fail on normalize : " + v1.ToString() + " == " + std::to_string(v2.x) + " " + std::to_string(v2.y));
    }

    // ----------------------------------------------------------------------------------
    // -------------------------------------- Vec3 --------------------------------------
    // ----------------------------------------------------------------------------------

    void TestVec3()
    {
        TestOperatorVec3();
        TestDotProductVec3();
        TestMagnitudeVec3();
        TestCrossProductVec3();
        TestNormalizeVec3();
        Log::Print("Vec3 : OK\n", Core::Debug::LogLevel::Test);
    }

    void TestOperatorVec3()
    {
        Vec3 v1(1.f, 1.f, 1.f);
        Vec3 v2(1.f, 1.f, 1.f);

        // Operator +
        Assertion(!(v1 + v2 != Vec3(2.f, 2.f, 2.f)), "fail on operator + : " + v1.ToString() + " + " + v2.ToString());

        // Operator +=
        v1 += v2;
        Assertion(!(v1 != Vec3(2.f, 2.f, 2.f)), "fail on operator += : " + v1.ToString() + " " + v2.ToString());

        // Operator -
        Assertion(!(v1 - v2 != Vec3(1.f, 1.f, 1.f)), "fail on operator - : " + v1.ToString() + " - " + v2.ToString());

        // Operator -=
        v1 -= v2;
        Assertion(!(v1 != Vec3(1.f, 1.f, 1.f)), "fail on operator -= : " + v1.ToString() + " " + v2.ToString());

        // Operator *
        Assertion(!(v1 * 2 != Vec3(2.f, 2.f, 2.f)), "fail on operator * : " + v1.ToString() + " * " + v2.ToString());

        // Operator *=
        v1 *= 2;
        Assertion(!(v1 != Vec3(2.f, 2.f, 2.f)), "fail on operator *= : " + v1.ToString() + " " + v2.ToString());

        // Operator /
        Assertion(!(v1 / 2 != Vec3(1.f, 1.f, 1.f)), "fail on operator / : " + v1.ToString() + " / " + v2.ToString());

        // Operator /=
        v1 /= 2;
        Assertion(!(v1 != Vec3(1.f, 1.f, 1.f)), "fail on operator /= : " + v1.ToString() + " " + v2.ToString());

        // Operator <
        Assertion(!(v1 < Vec3(0.9f, 0.9f, 0.9f)), "fail on operator < : " + v1.ToString() + " < Vec3(0.9f, 0.9f, 0.9f)");

        // Operator >
        Assertion(!(v1 > Vec3(1.1f, 1.1f, 1.1f)), "fail on operator > : " + v1.ToString() + " > Vec3(1.1f, 1.1f, 1.1f)");

        // Operator <=
        Assertion(v1 <= Vec3(1.0f, 1.0f, 1.0f), "fail on operator <= : " + v1.ToString() + " <= Vec3(1.0f, 1.0f, 1.0f)");

        // Operator >=
        Assertion(v1 >= Vec3(1.0f, 1.0f, 1.0f), "fail on operator >= : " + v1.ToString() + " >= Vec3(1.0f, 1.0f, 1.0f)");

        // Operator ==
        Assertion(v1 == v2, "fail on operator == : " + v1.ToString() + " == " + v2.ToString());
    }

    void TestDotProductVec3()
    {
        Vec3 v1(2.f, 2.f, 2.f);
        Vec3 v2(3.f, 3.f, 3.f);
        glm::vec3 v3(2.f, 2.f, 2.f);
        glm::vec3 v4(3.f, 3.f, 3.f);

        const float myResult = v1.DotProduct(v2);
        const float resultWanted = glm::dot(v3, v4);

        Assertion(myResult == resultWanted, "fail on dot product : " + std::to_string(myResult) + " == " + std::to_string(resultWanted));
    }

    void TestMagnitudeVec3()
    {
        Vec3 v1(2.f, 2.f, 2.f);
        glm::vec3 v2(2.f, 2.f, 2.f);

        const float myResult = v1.Magnitude();
        const float resultWanted = glm::length(v2);

        Assertion(myResult == resultWanted, "fail on dot product : " + std::to_string(myResult) + " == " + std::to_string(resultWanted));
    }

    void TestCrossProductVec3()
    {
        Vec3 v1(2.f, 2.f, 2.f);
        Vec3 v2(3.f, 3.f, 3.f);

        glm::vec3 v3(2.f, 2.f, 2.f);
        glm::vec3 v4(3.f, 3.f, 3.f);

        const Vec3 myResult = v1.CrossProduct(v2);
        const Vec3 resultWanted = Vec3(glm::cross(v3, v4).x, glm::cross(v3, v4).y, glm::cross(v3, v4).z);

        Assertion(myResult == resultWanted, "fail on dot product : " + myResult.ToString() + " == " + resultWanted.ToString());
    }

    void TestNormalizeVec3()
    {
        Vec3 v1(4.f, 4.f, 4.f);
        glm::vec3 v2(4.f, 4.f, 4.f);
        
        v1.Normalize();
        const Vec3 resultWanted = Vec3(glm::normalize(v2).x, glm::normalize(v2).y, glm::normalize(v2).z);

        Assertion(v1 == resultWanted, "fail on dot product : " + v1.ToString() + " == " + resultWanted.ToString());
    }

    
    // ----------------------------------------------------------------------------------
    // -------------------------------------- Vec4 --------------------------------------
    // ----------------------------------------------------------------------------------

    void TestVec4()
    {
        TestOperatorVec4();
        TestDotProductVec4();
        TestMagnitudeVec4();
        TestNormalizeVec4();
        TestHomogenizeVec4();
        Log::Print("Vec4 : OK\n", Core::Debug::LogLevel::Test);
    }

    void TestOperatorVec4()
    {
        Vec4 v1(1.f, 1.f, 1.f, 1.f);
        Vec4 v2(1.f, 1.f, 1.f, 1.f);

        // Operator +
        Assertion(!(v1 + v2 != Vec4(2.f, 2.f, 2.f, 2.f)), "fail on operator + : " + v1.ToString() + " + " + v2.ToString());

        // Operator +=
        v1 += v2;
        Assertion(!(v1 != Vec4(2.f, 2.f, 2.f, 2.f)), "fail on operator += : " + v1.ToString() + "  " + v2.ToString());

        // Operator -
        Assertion(!(v1 - v2 != Vec4(1.f, 1.f, 1.f, 1.f)), "fail on operator - : " + v1.ToString() + " - " + v2.ToString());

        // Operator -=
        v1 -= v2;
        Assertion(!(v1 != Vec4(1.f, 1.f, 1.f, 1.f)), "fail on operator -= : " + v1.ToString() + " Vec4(1.f, 1.f, 1.f, 1.f)");

        // Operator *
        Assertion(!(v1 * 2 != Vec4(2.f, 2.f, 2.f, 2.f)), "fail on operator * : " + v1.ToString() + " * 2 = Vec4(2.f, 2.f, 2.f, 2.f)");

        // Operator *=
        v1 *= 2;
        Assertion(!(v1 != Vec4(2.f, 2.f, 2.f, 2.f)), "fail on operator *= : " + v1.ToString() + " * 2 = Vec4(2.f, 2.f, 2.f, 2.f)");

        // Operator /
        Assertion(!(v1 / 2 != Vec4(1.f, 1.f, 1.f, 1.f)), "fail on operator / : " + v1.ToString() + " / 2 Vec4(1.f, 1.f, 1.f, 1.f)");

        // Operator /=
        v1 /= 2;
        Assertion(!(v1 != Vec4(1.f, 1.f, 1.f, 1.f)), "fail on operator + : " + v1.ToString() + " / 2 Vec4(1.f, 1.f, 1.f, 1.f)");

        // Operator <
        Assertion(!(v1 < Vec4(0.9f, 0.9f, 0.9f, 0.9f)), "fail on operator + : " + v1.ToString() + " < Vec4(0.9f, 0.9f, 0.9f, 0.9f)");

        // Operator >
        Assertion(!(v1 > Vec4(1.1f, 1.1f, 1.1f, 1.1f)), "fail on operator + : " + v1.ToString() + " > Vec4(1.1f, 1.1f, 1.1f, 1.1f)");

        // Operator <=
        Assertion(v1 <= Vec4(1.0f, 1.0f, 1.0f, 1.0f), "fail on operator + : " + v1.ToString() + " <= Vec4(1.0f, 1.0f, 1.0f, 1.0f)");

        // Operator >=
        Assertion(v1 >= Vec4(1.0f, 1.0f, 1.0f, 1.f), "fail on operator + : " + v1.ToString() + " >= Vec4(1.0f, 1.0f, 1.0f, 1.f)");

        // Operator ==
        Assertion(v1 == v2, "fail on operator + : " + v1.ToString() + " == " + v2.ToString());
    }

    void TestDotProductVec4()
    {
        Vec4 v1(2.f, 2.f, 2.f, 2.f);
        Vec4 v2(3.f, 3.f, 3.f, 3.f);
        glm::vec4 v3(2.f, 2.f, 2.f, 2.f);
        glm::vec4 v4(3.f, 3.f, 3.f, 3.f);

        const float myResult = v1.DotProduct(v2);
        const float resultWanted = glm::dot(v3, v4);

        Assertion(myResult == resultWanted, "fail on dot product : " + std::to_string(myResult) + " == " + std::to_string(resultWanted));
    }

    void TestMagnitudeVec4()
    {
        Vec4 v1(2.f, 2.f, 2.f, 2.f);
        glm::vec4 v2(2.f, 2.f, 2.f, 2.f);

        const float myResult = v1.Magnitude();
        const float resultWanted = glm::length(v2);

        Assertion(myResult == resultWanted, "fail on magnitude : " + std::to_string(myResult) + " == " + std::to_string(resultWanted));
    }

    void TestNormalizeVec4()
    {
        Vec4 v1(4.f, 4.f, 4.f, 4.f);
        glm::vec4 v2(4.f, 4.f, 4.f, 4.f);

        v1.Normalize();
        Vec4 resultWanted = Vec4(glm::normalize(v2).x, glm::normalize(v2).y, glm::normalize(v2).z, glm::normalize(v2).w);

        Assertion(v1 == resultWanted, "fail on magnitude : " + v1.ToString() + " == " + resultWanted.ToString());
    }

    void TestHomogenizeVec4()
    {
        Vec4 v1(4.f, 4.f, 4.f, 2.f);

        v1.Homogenize();
        Vec4 resultWanted(2.f, 2.f, 2.f, 1.f);

        Assertion(v1 == resultWanted, "fail on magnitude : " + v1.ToString() + " == " + resultWanted.ToString());
    }

    // ----------------------------------------------------------------------------------
    // -------------------------------------- Mat4 --------------------------------------
    // ----------------------------------------------------------------------------------

    void TestMat4()
    {
        TestOperatorMat4();
        TestTranslationMat4();
        TestRotationXMat4();
        TestRotationYMat4();
        TestRotationZMat4();
        TestScaleMat4();
        Log::Print("Mat4 : OK\n", Core::Debug::LogLevel::Test);
    }

    void TestOperatorMat4()
    {
        glm::mat4 mat1(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f);
        glm::mat4 mat2(16.f, 15.f, 14.f, 13.f, 12.f, 11.f, 10.f, 9.f, 8.f, 7.f, 6.f, 5.f, 4.f, 3.f, 2.f, 1.f);

        glm::vec4 vec(2.f, 2.f, 2.f, 2.f);

        // Operator +
        Mat4 result = GlmMatToMat(mat1 + mat2);
        Assertion((GlmMatToMat(mat1) + GlmMatToMat(mat2)) == result, "fail on operator +\n" + GlmMatToMat(mat1).ToString() + "+\n" + GlmMatToMat(mat2).ToString() + "=\n" + result.ToString());

        // Operator -
        result = GlmMatToMat(mat1 - mat2);
        Assertion((GlmMatToMat(mat1) - GlmMatToMat(mat2)) == result, "fail on operator -\n" + GlmMatToMat(mat1).ToString() + "-\n" + GlmMatToMat(mat2).ToString() + "=\n" + (GlmMatToMat(mat1) - GlmMatToMat(mat2)).ToString() + "!=\n" + result.ToString());

        // Operator * mat4
        result = GlmMatToMat(mat1 * mat2);
        Assertion((GlmMatToMat(mat1) * GlmMatToMat(mat2)) == GlmMatToMat(mat1 * mat2), "fail on operator * mat4\n" + GlmMatToMat(mat1).ToString() + "*\n" + GlmMatToMat(mat2).ToString() + "=\n" + (GlmMatToMat(mat1) * GlmMatToMat(mat2)).ToString() + "!=\n" + result.ToString());

        // Operator * with vec
        Assertion((GlmMatToMat(mat1) * GlmVecToVec(vec)) == GlmVecToVec(mat1 * vec), "fail on operator * vec4\n" + GlmMatToMat(mat1).ToString() + "*\n" + GlmVecToVec(vec).ToString() + "\n=\n" + (GlmMatToMat(mat1) * GlmVecToVec(vec)).ToString() + "\n!=\n" + GlmVecToVec(mat1 * vec).ToString());
    }

    void TestTranslationMat4()
    {
        glm::mat4 mat(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f);
        glm::vec3 vec(1.f, 2.f, 3.f);

        Mat4 myResult = GlmMatToMat(mat) * Mat4::CreateTranslationMatrix(GlmVecToVec(vec));
        Mat4 glmResult = GlmMatToMat(glm::translate(mat, vec));

        Assertion(myResult == glmResult, "fail on translation : " + myResult.ToString() + "!=\n" + glmResult.ToString());
    }

    void TestRotationXMat4()
    {
        glm::mat4 mat(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f);

        Mat4 myResult = GlmMatToMat(mat) * Mat4::CreateXRotationMatrix(90.f);
        Mat4 glmResult = GlmMatToMat(glm::rotate(mat, glm::radians(90.f), { 1.f, 0.f, 0.f }));
        
        Assertion(myResult == glmResult, "fail on rotation X : " + myResult.ToString() + "!=\n" + glmResult.ToString());
    }

    void TestRotationYMat4()
    {
        glm::mat4 mat(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f);

        Mat4 myResult = GlmMatToMat(mat) * Mat4::CreateYRotationMatrix(90.f);
        Mat4 glmResult = GlmMatToMat(glm::rotate(mat, glm::radians(90.f), { 0.f, 1.f, 0.f }));

        Assertion(myResult == glmResult, "fail on rotation Y : " + myResult.ToString() + "!=\n" + glmResult.ToString());
    }

    void TestRotationZMat4()
    {
        glm::mat4 mat(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f);

        Mat4 myResult = GlmMatToMat(mat) * Mat4::CreateZRotationMatrix(90.f);
        Mat4 glmResult = GlmMatToMat(glm::rotate(mat, glm::radians(90.f), { 0.f, 0.f, 1.f }));

        Assertion(myResult == glmResult, "fail on rotation Z : " + myResult.ToString() + "!=\n" + glmResult.ToString());
    }

    void TestScaleMat4()
    {
        glm::mat4 mat(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f);
        glm::vec3 scale(1.f, 2.f, 3.f);

        Mat4 myResult = GlmMatToMat(mat) * Mat4::CreateScaleMatrix(GlmVecToVec(scale));
        Mat4 glmResult = GlmMatToMat(glm::scale(mat, scale));

        Assertion(myResult == glmResult, "fail on scale : " + myResult.ToString() + "!=\n" + glmResult.ToString());
    }
}
