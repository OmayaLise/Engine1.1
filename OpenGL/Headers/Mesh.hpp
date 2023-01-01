#pragma once

#include <vector>

#include "IResource.hpp"
#include "MyMaths.hpp"

namespace Resources
{
	struct Vertex
	{
		Core::Maths::Vec3 position;
		Core::Maths::Vec3 normal;
		Core::Maths::Vec2 uv;
	};

	class Mesh : public IResource
	{
		// Attribute
	private:
		unsigned int VBO, VAO, EBO;
		std::vector<Vertex> vertexBuffer;
		std::vector<unsigned int> indexBuffer;


		// Methode
	public:
		Mesh(const std::string& p_name, const std::string& p_path1, const std::string& p_path2, const unsigned int p_id);
		~Mesh();

		void Init() override;
		void InitOpenGL() override;
		void Draw() const;

		// Get and Set
		std::vector<Vertex>& GetVertexBuffer() { return vertexBuffer; }
		std::vector<unsigned int>& GetIndexBuffer() { return indexBuffer; }

		void LoadMesh();
	private:
	};
}