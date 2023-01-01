#pragma once
#include "Mesh.hpp"

namespace LowRenderer
{
	class Renderer
	{
	public:
		Renderer();
		~Renderer();

		Resources::Mesh CreateCubePrimitif() ;
		Resources::Mesh CreateSpherePrimitif();
		Resources::Mesh CreateCapsulePrimitif();
		void CreatePrimitifsMeshs();


		//Attribute
	private:
		
		Resources::Mesh m_capsulePrimitif = Resources::Mesh("Primitif Capsule", "", "", - 1);;
		Resources::Mesh m_cubePrimitif = Resources::Mesh("Primitif Cube", "", "", -1);;
		Resources::Mesh m_spherePrimitif = Resources::Mesh("Primitif Sphere", "", "", -1);;

		//Methods
		void CreateCapsule(std::vector<Resources::Vertex>& vertexBuffer, std::vector<unsigned int>& indexBuffer);
		void CreateCube(std::vector<Resources::Vertex>& vertexBuffer, std::vector<unsigned int>& indexBuffer);
		void CreateSphere(std::vector<Resources::Vertex>& vertexBuffer, std::vector<unsigned int>& indexBuffer);
		void CreateQuad(std::vector<Resources::Vertex>& vertexBuffer, std::vector<unsigned int>& indexBuffer , const Core::Maths::Vec3 points[4]);
		void CreateTriangle(const Core::Maths::Vec3 point1, const Core::Maths::Vec3  point2, const Core::Maths::Vec3  point3, const bool up, std::vector<Resources::Vertex>& vertexBuffer, std::vector<unsigned int>& indexBuffer);
		Core::Maths::Vec3 CreateNormal(Core::Maths::Vec3 p_point1, Core::Maths::Vec3 p_point2, Core::Maths::Vec3 p_point3);
		void SetQuadPoints(Core::Maths::Vec3* p_pointsOut, const Core::Maths::Vec3* p_points, const unsigned int p_index1, const unsigned int p_index2, const unsigned int p_index3, const unsigned int p_index4);
		Core::Maths::Vec3 GetSphericalCoords(float r, float theta, float phi);
		
	};

	

}