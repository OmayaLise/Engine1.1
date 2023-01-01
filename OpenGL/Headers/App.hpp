#pragma once

#include <GLFW/glfw3.h>
#include <glad/glad.h>

// Resources
#include "ResourcesManager.hpp"
#include "Scene.hpp"
#include "Menu.hpp"
// LowRenderer
#include "Camera.hpp"
#include "GameObject.hpp"
#include "LightManager.hpp"
#include "Renderer.hpp"
// Core
#include "InputsManager.hpp"
#include "Timer.hpp"
#include "ThreadsManager.hpp"

namespace Core
{
	struct AppInit
	{
		unsigned int width;
		unsigned int height;
		unsigned int major;
		unsigned int minor;
		const char* name;
		void (*framebuffer_size_callback) (GLFWwindow* window, int width, int height);
		void (*glDebugOutput) (GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei lenght, const GLchar* message, const void* userParam);
	};

	class App
	{
		// Attribute
	private:

		static GLFWwindow* window;
		unsigned int width;
		unsigned int height;

		Time::Timer timer;
		Resources::ResourceManager resources;
		InputsManager inputsManager;
		 Resources::Scene* currentScene;
		LowRenderer::Renderer m_renderer;
		ThreadsManager threadsManager;

		static bool stopGame;


	public:
		static Resources::NextScene nextScene;
		
		// Methode
	public:
		App();
		~App();

		bool Init(const AppInit& p_appInit);
		void Update();

		// Get and Set
		GLFWwindow* GetWindow() { return window; };
		static void StopGame() { stopGame = true; };

	private:
		void ChangeScene();
		void InitRenderer();
		void CreateResource();
		void CreateScenes();
		void InitScene1();
	};
}