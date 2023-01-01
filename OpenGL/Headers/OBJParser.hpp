#pragma once

#include <string>
#include <sstream>
#include <fstream>

#include "Mesh.hpp"
#include "MyMaths.hpp"
#include "Assertion.hpp"

namespace Resources::OBJ
{
	struct index
	{
		unsigned int vertice;
		unsigned int uv;
		unsigned int normal;
	};

	struct tempOBJ
	{
		std::vector<Core::Maths::Vec3> vertices;
		std::vector<Core::Maths::Vec2> UVs;
		std::vector<Core::Maths::Vec3> normals;
		std::vector<index> vertexAlreadySaved;
	};

	inline void Open(std::ifstream& p_file, const std::string& p_path)
	{
		p_file.open(p_path, std::ios::in);
		Assertion(p_file, "Fail to open obj " + p_path);
		Core::Debug::Log::Print("Open obj " + p_path + "\n", Core::Debug::LogLevel::Notification);
	}

	inline void Close(std::ifstream& p_file)
	{
		p_file.close();
		Core::Debug::Log::Print("Close obj\n", Core::Debug::LogLevel::Notification);
	}

	inline void Add(tempOBJ& p_temp, const index p_index, std::vector<Vertex>& p_vertices, std::vector<unsigned int>& p_indices)
	{
		unsigned int indice;
		bool isAlreadyIn = false;

		for (unsigned int i = 0; i < p_temp.vertexAlreadySaved.size(); i++)
		{
			if (p_temp.vertexAlreadySaved[i].vertice == p_index.vertice
				&& p_temp.vertexAlreadySaved[i].uv == p_index.uv
				&& p_temp.vertexAlreadySaved[i].normal == p_index.normal
				&& !isAlreadyIn)
			{
				indice = i;
				isAlreadyIn = true;
			}
		}

		if (isAlreadyIn)
		{
			p_indices.push_back(indice);
		}
		else
		{
			Vertex vertex;
			vertex.position = p_temp.vertices[p_index.vertice - 1];
			vertex.normal = p_temp.normals[p_index.normal - 1];
			vertex.uv = p_temp.UVs[p_index.uv - 1];

			p_indices.push_back(p_vertices.size());
			p_vertices.push_back(vertex);
			p_temp.vertexAlreadySaved.push_back(p_index);
		}
	}

	inline void Parse(const std::string& p_path, std::vector<Vertex>& p_vertices, std::vector<unsigned int>& p_indices)
	{
		std::ifstream obj;

		Open(obj, p_path);

		tempOBJ	temp;
		std::string line;
		std::string prefix;
		std::stringstream ss;
		

		while (std::getline(obj, line))
		{
			ss.clear();
			ss.str(line);
			ss >> prefix;

			if (prefix == "v")
			{
				Core::Maths::Vec3 vertex;
				ss >> vertex.x >> vertex.y >> vertex.z;
				temp.vertices.push_back(vertex);
			}
			else if (prefix == "vt")
			{
				Core::Maths::Vec2 uv;
				ss >> uv.x >> uv.y;
				temp.UVs.push_back(uv);
			}
			else if (prefix == "vn")
			{
				Core::Maths::Vec3 normal;
				ss >> normal.x >> normal.y >> normal.z;
				temp.normals.push_back(normal);
			}
			else if (prefix == "f")
			{
				char slash;
				index index[3];
				ss >> index[0].vertice >> slash >> index[0].uv >> slash >> index[0].normal
				   >> index[1].vertice >> slash >> index[1].uv >> slash >> index[1].normal
				   >> index[2].vertice >> slash >> index[2].uv >> slash >> index[2].normal;

				for (unsigned int i = 0; i < 3; i++)
					Add(temp, index[i], p_vertices, p_indices);
			}
		}
		Close(obj);
	}
}