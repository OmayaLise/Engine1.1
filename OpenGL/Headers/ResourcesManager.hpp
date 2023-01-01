#pragma once

#include <string>
#include <unordered_map>
#include <iostream>
#include <memory>

#include "Assertion.hpp"
#include "IResource.hpp"

namespace Resources
{
	class ResourceManager
	{
		// Attribute
	private:
		std::unordered_map<std::string, std::unique_ptr<IResource>> resources;

		// Methode
	public:
		ResourceManager();

		template <typename T>
		T* Create(const std::string p_name, const std::string p_path1, const std::string p_path2 = "");

		void Delete(const std::string p_name);
		void DeleteResources();

		const bool CheckAllResourcesLoaded();
		
		// Get and Set
		template <typename T>
		T* GetResource(const std::string p_name) const;
	};

	template <typename T>
	T* ResourceManager::Create(const std::string p_name, const std::string p_path1, const std::string p_path2)
	{
		static_assert(std::is_base_of<IResource, T>::value, "T is not a compatible resource");
		
		const unsigned int id = resources.size();
		auto [it, _] = resources.insert_or_assign(p_name, std::make_unique<T>(p_name, p_path1, p_path2, id));
		
		Core::Debug::Log::Print("Add element " + p_name + " in resources\n", Core::Debug::LogLevel::Notification);
		return static_cast<T*>(it->second.get());
	}

	template <typename T>
	T* ResourceManager::GetResource(const std::string p_name) const
	{
		T* resource = static_cast<T*>(resources.find(p_name)->second.get());
		Assertion(resource, p_name + " is not in resources");
		return resource;
	}
}