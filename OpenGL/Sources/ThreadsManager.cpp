#include "ThreadsManager.hpp"
#include <iostream>

namespace Core
{
	ThreadsManager::ThreadsManager(const unsigned int p_size)
		: resourcesToInitEnabled (0)
		, resourcesToLoadEnabled (0)
		, nbThreadResources(p_size)
	{
		for (unsigned int i = 0; i < nbThreadResources; i++)
		{
			threadpool.push_back(std::thread());
		}
	}

	ThreadsManager::~ThreadsManager()
	{
		for (unsigned int i = 0; i < threadpool.size(); i++)
		{
			if(threadpool.at(i).joinable())
				threadpool.at(i).join();
		}
	}

	void ThreadsManager::Init()
	{
		if (multithread)
		{
			for (unsigned int i = 0; i < nbThreadResources; i++)
			{
				threadpool.at(i) = std::thread(&ThreadsManager::InitResources, this);
			}
		}
		else
		{
			InitResources();
		}
	}

	void ThreadsManager::Wait(std::atomic<unsigned int>& p_token)
	{
		while(p_token != 0)
		{
		}
	}

	void ThreadsManager::InitResources()
	{
		while (resourcesToInit.size() != 0)
		{
			Wait(resourcesToInitEnabled);
			unsigned int test = ++resourcesToInitEnabled;

			if (test == 1)
			{
				Resources::IResource* resource = resourcesToInit.front();
				resourcesToInit.pop();
				resourcesToInitEnabled.store(0);

				resource->Init();

				bool addedToQueue = false;

				while (!addedToQueue)
				{
					Wait(resourcesToLoadEnabled);
					test = ++resourcesToLoadEnabled;
				
					if (test == 1)
					{
						resourcesToLoad.push(resource);
						resourcesToLoadEnabled.store(0);
						addedToQueue = true;
					}
				}
			}
		}
	}

	void ThreadsManager::Update()
	{
		while (resourcesToLoad.size() != 0)
		{
			Wait(resourcesToLoadEnabled);
			unsigned int test = ++resourcesToLoadEnabled;

			if (test == 1)
			{
				resourcesToLoad.front()->InitOpenGL();
				resourcesToLoad.pop();
				resourcesToLoadEnabled.store(0);
			}
		}
	}

	void ThreadsManager::DeleteThreads()
	{
		for (unsigned int i = 0; i < threadpool.size(); i++)
		{
			if (threadpool.at(i).joinable())
			{
				threadpool.at(i).join();
				std::cout << " Thread unused is destroyed \n";
			}
		}
	}
}