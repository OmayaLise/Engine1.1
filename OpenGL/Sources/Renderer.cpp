#include "Renderer.hpp"

namespace LowRenderer
{
	Renderer::Renderer()
	{

	}

	Renderer::~Renderer()
	{
	}

	Resources::Mesh Renderer::CreateCubePrimitif()
	{
		return m_cubePrimitif;
	}
	Resources::Mesh Renderer::CreateSpherePrimitif()
	{
		return m_spherePrimitif;
	}

	Resources::Mesh Renderer::CreateCapsulePrimitif()
	{
		return m_capsulePrimitif;
	}

	void Renderer::CreatePrimitifsMeshs()
	{
		CreateCube(m_cubePrimitif.GetVertexBuffer(), m_cubePrimitif.GetIndexBuffer());
		CreateSphere(m_spherePrimitif.GetVertexBuffer(), m_spherePrimitif.GetIndexBuffer());
		CreateCapsule(m_capsulePrimitif.GetVertexBuffer(), m_capsulePrimitif.GetIndexBuffer());
	}

	void Renderer::CreateCapsule(std::vector<Resources::Vertex>& vertexBuffer, std::vector<unsigned int>& indexBuffer)
	{
		const int lat = 25, lon = 25;
		const int cylinderSize = -3;
		float r = 1.0f;
		Core::Maths::Vec3 top(0, r, 0);
		Core::Maths::Vec3 bottom(0, -r + cylinderSize, 0);

		for (int a = 0; a < lat; a++) {
			float ty0 = M_PI / lon;
			float r0 = sin(ty0);

			float th0 = M_PI * 2 * a / lat;
			float th1 = M_PI * 2 * (a + 1) / lat;
			Core::Maths::Vec3  p0(cos(th0), 0, sin(th0));
			Core::Maths::Vec3  p1(cos(th1), 0, sin(th1));

			Core::Maths::Vec3  v0 = p0 * r * r0;
			Core::Maths::Vec3  v1 = p1 * r * r0;
			v0.y = v1.y =  cos(ty0);

			CreateTriangle(v0, top, v1, false, vertexBuffer, indexBuffer);

		}

		int y = 1;
		for (y ; y < (lon - 1) /2; y++)
		{
			float ty0 = M_PI * y / lon;
			float ty1 = M_PI * (y + 1) / lon;

			float r0 = sin(ty0);
			float r1 = sin(ty1);

			for (int a = 0; a < lat; a++)
			{
				float th0 = M_PI * 2 * a / lat;
				float th1 = M_PI * 2 * (a + 1) / lat;

				Core::Maths::Vec3 p0(cos(th0), 0, sin(th0));
				Core::Maths::Vec3 p1(cos(th1), 0, sin(th1));

				Core::Maths::Vec3 v0 = p0 * r * r0;
				Core::Maths::Vec3 v1 = p1 * r * r0;

				Core::Maths::Vec3 v2 = p0 * r * r1;
				Core::Maths::Vec3 v3 = p1 * r * r1;

				v0.y = v1.y = cos(ty0);
				v2.y = v3.y = cos(ty1);

				CreateTriangle(v0, v1, v3, true, vertexBuffer, indexBuffer);
				CreateTriangle(v0, v3, v2, false, vertexBuffer, indexBuffer);

			}


		}

		for (y; y < ((lon - 1) / 2) +1; y++)
		{
			float ty0 = M_PI * y / lon;
			float ty1 = M_PI * (y) / lon;

			float r0 = sin(ty0);
			float r1 = sin(ty1);

			for (int a = 0; a < lat; a++)
			{
				float th0 = M_PI * 2 * a / lat;
				float th1 = M_PI * 2 * (a+1) / lat;

				Core::Maths::Vec3 p0(cos(th0), 0, sin(th0));
				Core::Maths::Vec3 p1(cos(th1), 0, sin(th1));

				Core::Maths::Vec3 v0 = p0 * r * r0;
				Core::Maths::Vec3 v1 = p1 * r * r0;

				Core::Maths::Vec3 v2 = p0 * r * r1;
				Core::Maths::Vec3 v3 = p1 * r * r1;

				v0.y = v1.y = cos(ty0);
				v2.y = v3.y = cos(ty1) + cylinderSize;

				CreateTriangle(v0, v1, v3, true, vertexBuffer, indexBuffer);
				CreateTriangle(v0, v3, v2, false, vertexBuffer, indexBuffer);

			}


		}

		for (--y ; y < (lon - 1); y++)
		{
			float ty0 = M_PI * y / lon;
			float ty1 = M_PI * (y + 1) / lon;

			float r0 = sin(ty0);
			float r1 = sin(ty1);

			for (int a = 0; a < lat; a++)
			{
				float th0 = M_PI * 2 * a / lat;
				float th1 = M_PI * 2 * (a + 1) / lat;

				Core::Maths::Vec3 p0(cos(th0), 0, sin(th0));
				Core::Maths::Vec3 p1(cos(th1), 0, sin(th1));

				Core::Maths::Vec3 v0 = p0 * r * r0;
				Core::Maths::Vec3 v1 = p1 * r * r0;

				Core::Maths::Vec3 v2 = p0 * r * r1;
				Core::Maths::Vec3 v3 = p1 * r * r1;

				v0.y = v1.y = cos(ty0) + cylinderSize;
				v2.y = v3.y = cos(ty1) + cylinderSize;

				CreateTriangle(v0, v1, v3, true, vertexBuffer, indexBuffer);
				CreateTriangle(v0, v3, v2, false, vertexBuffer, indexBuffer);

			}


		}

		for (int a = 0; a < lat; a++)
		{
			float ty0 = M_PI * (lon - 1) / lon;
			float r0 = sin(ty0);

			float th0 = M_PI * 2 * a / lat;
			float th1 = M_PI * 2 * (a + 1) / lat;
			Core::Maths::Vec3 p0(cos(th0), 0, sin(th0));
			Core::Maths::Vec3 p1(cos(th1), 0, sin(th1));

			Core::Maths::Vec3 v0 = p0 * r * r0;
			Core::Maths::Vec3 v1 = p1 * r * r0;
			v0.y = v1.y = cos(ty0) + cylinderSize;

			CreateTriangle(bottom, v0, v1, false, vertexBuffer, indexBuffer);
		}
	}

	void Renderer::CreateCube(std::vector<Resources::Vertex>& vertexBuffer, std::vector<unsigned int>& indexBuffer)
	{
		Core::Maths::Vec3 points[8];
		points[0] = { -1.f, -1.f, 1.f };
		points[1] = { 1.f, -1.f, 1.f };
		points[2] = { 1.f, 1.f, 1.f };
		points[3] = { -1.f, 1.f, 1.f };

		points[4] = { -1.f, -1.f, -1.f };
		points[5] = { 1.f, -1.f, -1.f };
		points[6] = { 1.f, 1.f, -1.f };
		points[7] = { -1.f,1.f, -1.f };



		Core::Maths::Vec3 quadsPoints[4] = { { -0.5f, -0.5f, 0.5f } };
		SetQuadPoints(quadsPoints, points, 1, 0, 3, 2);
		CreateQuad(vertexBuffer, indexBuffer, quadsPoints);
		SetQuadPoints(quadsPoints, points, 4, 5, 6, 7);
		CreateQuad(vertexBuffer, indexBuffer, quadsPoints);

		SetQuadPoints(quadsPoints, points, 0, 4, 7, 3);
		CreateQuad(vertexBuffer, indexBuffer, quadsPoints);
		SetQuadPoints(quadsPoints, points, 5, 1, 2, 6);
		CreateQuad(vertexBuffer, indexBuffer, quadsPoints);

		SetQuadPoints(quadsPoints, points, 2, 3, 7, 6);
		CreateQuad(vertexBuffer, indexBuffer, quadsPoints);
		SetQuadPoints(quadsPoints, points, 5, 4, 0, 1);
		CreateQuad(vertexBuffer, indexBuffer, quadsPoints);
	}

	void Renderer::CreateSphere(std::vector<Resources::Vertex>& vertexBuffer, std::vector<unsigned int>& indexBuffer)
	{
		const int lat = 25, lon = 12;
		float r = 1.0f;
		Core::Maths::Vec3 top(0, r, 0);
		Core::Maths::Vec3 bottom(0, -r, 0);

		for (int a = 0; a < lat; a++) {
			float ty0 = M_PI / lon;
			float r0 = sin(ty0);

			float th0 = M_PI * 2 * a / lat;
			float th1 = M_PI * 2 * (a + 1) / lat;
			Core::Maths::Vec3  p0(cos(th0), 0, sin(th0));
			Core::Maths::Vec3  p1(cos(th1), 0, sin(th1));

			Core::Maths::Vec3  v0 = p0 * r * r0;
			Core::Maths::Vec3  v1 = p1 * r * r0;
			v0.y = v1.y = cos(ty0);

			CreateTriangle(v0, top, v1, false, vertexBuffer, indexBuffer);

		}

		for (int y = 1; y < lon - 1; y++) {
			float ty0 = M_PI * y / lon;
			float ty1 = M_PI * (y + 1) / lon;

			float r0 = sin(ty0);
			float r1 = sin(ty1);

			for (int a = 0; a < lat; a++) {
				float th0 = M_PI * 2 * a / lat;
				float th1 = M_PI * 2 * (a + 1) / lat;

				Core::Maths::Vec3 p0(cos(th0), 0, sin(th0));
				Core::Maths::Vec3 p1(cos(th1), 0, sin(th1));

				Core::Maths::Vec3 v0 = p0 * r * r0;
				Core::Maths::Vec3 v1 = p1 * r * r0;

				Core::Maths::Vec3 v2 = p0 * r * r1;
				Core::Maths::Vec3 v3 = p1 * r * r1;

				v0.y = v1.y = cos(ty0);
				v2.y = v3.y = cos(ty1);

				CreateTriangle(v0, v1, v3, true, vertexBuffer, indexBuffer);
				CreateTriangle(v0, v3, v2, false, vertexBuffer, indexBuffer);

			}
		}

		for (int a = 0; a < lat; a++) {
			float ty0 = M_PI * (lon - 1) / lon;
			float r0 = sin(ty0);

			float th0 = M_PI * 2 * a / lat;
			float th1 = M_PI * 2 * (a + 1) / lat;
			Core::Maths::Vec3 p0(cos(th0), 0, sin(th0));
			Core::Maths::Vec3 p1(cos(th1), 0, sin(th1));

			Core::Maths::Vec3 v0 = p0 * r * r0;
			Core::Maths::Vec3 v1 = p1 * r * r0;
			v0.y = v1.y = cos(ty0);

			CreateTriangle(bottom, v0, v1, false, vertexBuffer, indexBuffer);
		}


	}



	void Renderer::CreateQuad(std::vector<Resources::Vertex>& vertexBuffer, std::vector<unsigned int>& indexBuffer, const Core::Maths::Vec3 points[4])
	{
		CreateTriangle(points[0], points[3], points[1], false, vertexBuffer, indexBuffer);
		CreateTriangle(points[3], points[2], points[1], true, vertexBuffer, indexBuffer);
	}

	void  Renderer::CreateTriangle(const Core::Maths::Vec3 point1, const Core::Maths::Vec3 point2, const Core::Maths::Vec3  point3, const bool up, std::vector<Resources::Vertex>& vertexBuffer, std::vector<unsigned int>& indexBuffer)
	{
		Resources::Vertex vertex_1;
		Resources::Vertex vertex_2;
		Resources::Vertex vertex_3;

		vertex_1.position = point1;
		vertex_2.position = point2;
		vertex_3.position = point3;

		if (up) vertex_1.uv = Core::Maths::Vec2(1, 1);
		else  vertex_1.uv = Core::Maths::Vec2(0, 0);

		if (up) vertex_2.uv = Core::Maths::Vec2(0, 1);
		else  vertex_2.uv = Core::Maths::Vec2(0, 1);

		if (up) vertex_3.uv = Core::Maths::Vec2(0, 1);
			else vertex_3.uv = Core::Maths::Vec2(1, 0);
		Core::Maths::Vec3 normal = CreateNormal(point1, point2, point3);

		vertex_1.normal = normal;
		vertex_2.normal = normal;
		vertex_3.normal = normal;

		vertexBuffer.push_back(vertex_1);
		vertexBuffer.push_back(vertex_2);
		vertexBuffer.push_back(vertex_3);

		indexBuffer.push_back(indexBuffer.size());
		indexBuffer.push_back(indexBuffer.size());
		indexBuffer.push_back(indexBuffer.size());
	}

	Core::Maths::Vec3 Renderer::CreateNormal(Core::Maths::Vec3 p_point1, Core::Maths::Vec3 p_point2, Core::Maths::Vec3 p_point3)
	{
		Core::Maths::Vec3 dir_1 = p_point2 - p_point1;
		Core::Maths::Vec3 dir_2 = p_point3 - p_point1;
		dir_1.CrossProduct(dir_2);
		return dir_1.Normalize();
	}


	void Renderer::SetQuadPoints(Core::Maths::Vec3* p_pointsOut, const Core::Maths::Vec3* p_points, const unsigned int p_index1, const unsigned int p_index2, const unsigned int p_index3, const unsigned int p_index4)
	{
		p_pointsOut[0] = p_points[p_index1];
		p_pointsOut[1] = p_points[p_index2];
		p_pointsOut[2] = p_points[p_index3];
		p_pointsOut[3] = p_points[p_index4];
	}


	Core::Maths::Vec3 Renderer::GetSphericalCoords(float r, float theta, float phi)
	{
		return { r * sinf(theta) * cosf(phi),
			r * cosf(theta),
			r * sinf(theta) * sinf(phi) };

	}

}