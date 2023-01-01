#pragma once

namespace Core::Debug
{
	void TestMyMaths();

	// Vec2
	void TestVec2();
	void TestOperatorVec2();
	void TestDotProductVec2();
	void TestMagnitudeVec2();
	void TestCrossProductVec2();
	void TestNormalizeVec2();

	// Vec3
	void TestVec3();
	void TestOperatorVec3();
	void TestDotProductVec3();
	void TestMagnitudeVec3();
	void TestCrossProductVec3();
	void TestNormalizeVec3();

	// Vec4
	void TestVec4();
	void TestOperatorVec4();
	void TestDotProductVec4();
	void TestMagnitudeVec4();
	void TestNormalizeVec4();
	void TestHomogenizeVec4();

	// Mat4
	void TestMat4();
	void TestOperatorMat4();
	void TestTranslationMat4();
	void TestRotationXMat4();
	void TestRotationYMat4();
	void TestRotationZMat4();
	void TestScaleMat4();
}