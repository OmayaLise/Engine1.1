#include "ResourcesManager.hpp"

namespace Resources
{
	ResourceManager::ResourceManager()
		: resources()
	{
	}

	void ResourceManager::Delete(const std::string p_name)
	{
		resources.erase(p_name);
		Core::Debug::Log::Print("Delete element " + p_name + " from resources\n", Core::Debug::LogLevel::Notification);
	}

	void ResourceManager::DeleteResources()
	{
		std::unordered_map<std::string, std::unique_ptr<IResource>>::iterator it = resources.begin();
		std::vector<std::string> nameResourceToDelete;

		while (it != resources.end())
		{
			const std::string nameResource = it->first;
			
			if (nameResource != "Menu" && nameResource != "Credit" && nameResource != "Setting")
				nameResourceToDelete.push_back(nameResource);

			it++;
		}

		for (std::string name : nameResourceToDelete)
			Delete(name);
	}

	const bool ResourceManager::CheckAllResourcesLoaded()
	{
		std::unordered_map<std::string, std::unique_ptr<IResource>>::iterator it = resources.begin();

		while (it != resources.end())
		{
			if (it->second.get()->GetStat() != StatResource::LOADED)
				return false;

			it++;
		}

		return true;
	}
}