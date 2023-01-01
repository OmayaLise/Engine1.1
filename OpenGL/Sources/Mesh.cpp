#include "Mesh.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <sstream>

#include "Assertion.hpp"
#include "OBJParser.hpp"

namespace Resources
{
	Mesh::Mesh(const std::string& p_name, const std::string& p_path1, const std::string& p_path2, const unsigned int p_id)
		: EBO(0)
		, VBO(0)
		, VAO(0)
	{
		name = p_name;
		path1 = p_path1;
		path2 = p_path2;
		id = p_id;
	}

	Mesh::~Mesh()
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}

	void Mesh::Init()
	{
		if(path1.size() > 3)
			OBJ::Parse(path1, vertexBuffer, indexBuffer);
		stat = StatResource::INITIALIZED;
	}

	void Mesh::InitOpenGL()
	{
		LoadMesh();
		stat = StatResource::LOADED;
	}

	void Mesh::Draw() const
	{
		glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		glDrawElements(GL_TRIANGLES, indexBuffer.size(), GL_UNSIGNED_INT, 0);
	}

	void Mesh::LoadMesh()
	{
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		glGenVertexArrays(1, &VAO);

		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertexBuffer.size() * sizeof(Vertex), vertexBuffer.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBuffer.size() * sizeof(unsigned int), indexBuffer.data(), GL_STATIC_DRAW);

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		glEnableVertexAttribArray(0);
		// color attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Core::Maths::Vec3)));
		glEnableVertexAttribArray(1);
		// texture coord attribute
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(2 * sizeof(Core::Maths::Vec3)));
		glEnableVertexAttribArray(2);

		Core::Debug::Log::Print("Load Mesh (" + name + ")!\n", Core::Debug::LogLevel::Notification);
	}

}