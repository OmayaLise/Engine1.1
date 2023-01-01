#pragma once
#include <vector>
#include <thread>
#include <queue>
#include "IResource.hpp"
#include <atomic>

namespace Core
{
	class ThreadsManager
	{
		// Attribute
	private:
		std::queue<Resources::IResource*> resourcesToInit;
		std::queue<Resources::IResource*> resourcesToLoad;
		const unsigned int nbThreadResources;

	public:
		std::vector<std::thread> threadpool;
		std::atomic<unsigned int> resourcesToInitEnabled;
		std::atomic<unsigned int> resourcesToLoadEnabled;
		static bool multithread;

		// Methode
	public:
		ThreadsManager(const unsigned int p_size);
		~ThreadsManager();
		void Init();
		void Wait(std::atomic<unsigned int>& p_token);
		void AddResourceToInit(Resources::IResource* p_resource) { resourcesToInit.push(p_resource); };
		void Update();
		void DeleteThreads();

	private:
		void InitResources();
	};

}