#include "App.hpp"

#include <iostream>

#include "Imgui/imgui.h"
#include "Imgui/imgui_impl_glfw.h"
#include "Imgui/imgui_impl_opengl3.h"

#include "Log.hpp"

#include "Credit.hpp"
#include "Setting.hpp"

namespace Core
{
	Resources::NextScene App::nextScene = {"Menu", Resources::SceneType::ST_Menu};
	bool ThreadsManager::multithread = true;
	GLFWwindow* App::window = nullptr;
	bool App::stopGame = false;

	App::App()
		: width(0)
		, height(0)
		, inputsManager(window)
		, threadsManager(5)
		, currentScene(nullptr)
		, timer(width, height)
	{
	}

	App::~App()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		// glfw: terminate, clearing all previously allocated GLFW resources.
		glfwTerminate();
	}

	bool App::Init(const AppInit& p_appInit)
	{
		width = p_appInit.width;
		height = p_appInit.height;

		// glfw: initialize and configure
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, p_appInit.major);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, p_appInit.minor);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

		// glfw window creation
		window = glfwCreateWindow(p_appInit.width, p_appInit.height, p_appInit.name, NULL, NULL);
		if (window == NULL)
		{
			DEBUG_LOG("Failed to create GLFW window");
			glfwTerminate();
			return false;
		}
		glfwMakeContextCurrent(window);
		glfwSetFramebufferSizeCallback(window, p_appInit.framebuffer_size_callback);

		// glad: load all OpenGL function pointers
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			DEBUG_LOG("Failed to initialize GLAD");
			return false;
		}

		GLint flags = 0;
		glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
		if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
		{
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(p_appInit.glDebugOutput, nullptr);
			glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
		}

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);

		// Setup Dear ImGui
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGui::StyleColorsDark();
		ImGuiStyle& style = ImGui::GetStyle();

		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 130");

		CreateScenes();
		
		currentScene = resources.GetResource<Resources::Scene>("Menu");

		inputsManager.SetWindow(window);

		return true;
	}

	void App::InitRenderer()
	{
		m_renderer.CreatePrimitifsMeshs();
	}

	void App::Update()
	{
		Core::Inputs inputs;
		while (!stopGame)
		{
			// input
			glfwPollEvents();
			inputs = inputsManager.Update();

			// render
			glClearColor(0.06f, 0.01f, 0.34f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			glClear(GL_DEPTH_BUFFER_BIT);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			threadsManager.Update();

			ChangeScene();

			timer.Update();
			currentScene->Update(inputs,timer.GetDeltaTime());
			currentScene->Draw(inputs, timer.elapsedMono, timer.elapsedMulti);

			if (resources.CheckAllResourcesLoaded() && !timer.timerDone && timer.begin && threadsManager.multithread)
				timer.ChronoEnd(timer.elapsedMulti);
			else if (resources.CheckAllResourcesLoaded() && !timer.timerDone && timer.begin && !threadsManager.multithread)
				timer.ChronoEnd(timer.elapsedMono);

			glfwSwapBuffers(window);
		}
	}

	void App::ChangeScene()
	{

		if (nextScene.name == currentScene->GetName())
			return;

		switch (nextScene.sceneType)
		{
		case Resources::SceneType::ST_Game:
			timer.begin = true;
			timer.ChronoBegin();
			CreateResource();
			currentScene = resources.GetResource<Resources::Scene>(nextScene.name);
			Debug::Log::Print("Change scene " + nextScene.name + "\n", Debug::LogLevel::Notification);
			InitScene1();
			threadsManager.Init();
			break;

		case Resources::SceneType::ST_Menu:

			threadsManager.DeleteThreads();
			if (currentScene->GetName() == "Scene1" && !resources.CheckAllResourcesLoaded())
				break;

			currentScene = resources.GetResource<Resources::Menu>(nextScene.name);
			Debug::Log::Print("Change scene " + nextScene.name + "\n", Debug::LogLevel::Notification);
			resources.DeleteResources();
			timer.begin = false;
			timer.timerDone = false;

			break;

		case Resources::SceneType::ST_Setting:
			currentScene = resources.GetResource<Resources::Setting>(nextScene.name);
			Debug::Log::Print("Change scene " + nextScene.name + "\n", Debug::LogLevel::Notification);
			break;

		case Resources::SceneType::ST_Credit:
			currentScene = resources.GetResource<Resources::Credit>(nextScene.name);
			Debug::Log::Print("Change scene " + nextScene.name + "\n", Debug::LogLevel::Notification);
			break;

		default:
			break;
		}

	}

	void App::CreateResource()
	{
		Core::Debug::Log::Print("---------\n", Core::Debug::LogLevel::None);
		Core::Debug::Log::Print("Init resource\n", Core::Debug::LogLevel::Notification);

		std::string name = "BasicShader";
		std::string pathVert = "Resources/Shaders/VertexShaderSource.vert";
		std::string pathFrag = "Resources/Shaders/FragmentShaderSource.frag";
		threadsManager.AddResourceToInit(resources.Create<Resources::Shader>(name, pathVert, pathFrag));

		// Patrick
		name = "Patrick";
		std::string path = "Resources/Obj/patrick.obj";
		threadsManager.AddResourceToInit(resources.Create<Resources::Mesh>(name, path));

		name = "PatrickText";
		path = "Resources/Textures/patrick.png";
		threadsManager.AddResourceToInit(resources.Create<Resources::Texture>(name, path));

		name = "ColliderShader";
		pathVert = "Resources/Shaders/VertexShaderSource.vert";
		pathFrag = "Resources/Shaders/ColliderFrag.frag";
		threadsManager.AddResourceToInit(resources.Create<Resources::Shader>(name, pathVert, pathFrag));

		path = "Resources/Obj/cube.obj";
		name = "Cube";
		threadsManager.AddResourceToInit(resources.Create<Resources::Mesh>(name, path));

		name = "Sphere";
		path = "Resources/Obj/Sphere.obj";
		threadsManager.AddResourceToInit(resources.Create<Resources::Mesh>(name, path));

		name = "Wall";
		path = "Resources/Textures/wall.jpg";
		threadsManager.AddResourceToInit(resources.Create<Resources::Texture>(name, path));

		name = "Sample";
		path = "Resources/Textures/sample.png";
		threadsManager.AddResourceToInit(resources.Create<Resources::Texture>(name, path));

		// Slime
		name = "Slime";
		path = "Resources/Obj/Slime.obj";
		threadsManager.AddResourceToInit(resources.Create<Resources::Mesh>(name, path));

		name = "SlimeText";
		path = "Resources/Textures/Slime.png";
		threadsManager.AddResourceToInit(resources.Create<Resources::Texture>(name, path));

		// Frying_pan
		name = "FryingPan";
		path = "Resources/Obj/frying_pan.obj";
		threadsManager.AddResourceToInit(resources.Create<Resources::Mesh>(name, path));

		name = "FryingPanText";
		path = "Resources/Textures/frying_pan.png";
		threadsManager.AddResourceToInit(resources.Create<Resources::Texture>(name, path));

		// Pistol
		name = "Pistol";
		path = "Resources/Obj/c_pistol.obj";
		threadsManager.AddResourceToInit(resources.Create<Resources::Mesh>(name, path));

		name = "PistolText";
		path = "Resources/Textures/c_pistol.png";
		threadsManager.AddResourceToInit(resources.Create<Resources::Texture>(name, path));

		// Companion
		name = "Companion";
		path = "Resources/Obj/companion.obj";
		threadsManager.AddResourceToInit(resources.Create<Resources::Mesh>(name, path));

		name = "CompanionText";
		path = "Resources/Textures/companion.png";
		threadsManager.AddResourceToInit(resources.Create<Resources::Texture>(name, path));

		// PotatOS
		name = "PotatOS";
		path = "Resources/Obj/potatOS.obj";
		threadsManager.AddResourceToInit(resources.Create<Resources::Mesh>(name, path));

		name = "PotatOSText";
		path = "Resources/Textures/potatOS.png";
		threadsManager.AddResourceToInit(resources.Create<Resources::Texture>(name, path));

		// Chocobo
		name = "Chocobo";
		path = "Resources/Obj/chocobo.obj";
		threadsManager.AddResourceToInit(resources.Create<Resources::Mesh>(name, path));

		name = "ChocoboText";
		path = "Resources/Textures/chocobo.png";
		threadsManager.AddResourceToInit(resources.Create<Resources::Texture>(name, path));

		// Scene1
		name = "Scene1";
		resources.Create<Resources::Scene>(name, "")->Init(width, height);

		InitRenderer();
		name = "BoxCollider";
		Resources::Mesh* cube = resources.Create<Resources::Mesh>(name, "");
		*cube = m_renderer.CreateCubePrimitif();
		cube->LoadMesh();
		cube->SetStat(Resources::StatResource::LOADED);

		name = "SphereCollider";
		Resources::Mesh* sphere = resources.Create<Resources::Mesh>(name, "");
		*sphere = m_renderer.CreateSpherePrimitif();
		sphere->LoadMesh();
		sphere->SetStat(Resources::StatResource::LOADED);

		name = "CapsuleCollider";
		Resources::Mesh* capsule = resources.Create<Resources::Mesh>(name, "");
		*capsule = m_renderer.CreateCapsulePrimitif();
		capsule->LoadMesh();
		capsule->SetStat(Resources::StatResource::LOADED);
	}
	void App::CreateScenes()
	{
		// Menu
		std::string name = "Menu";
		resources.Create<Resources::Menu>(name, "")->Init(width, height);

		// Credit
		name = "Credit";
		resources.Create<Resources::Credit>(name, "")->Init(width, height);

		// Setting
		name = "Setting";
		resources.Create<Resources::Setting>(name, "")->Init(width, height, &inputsManager);
	}

	void App::InitScene1()
	{
		Core::Debug::Log::Print("---------\n", Core::Debug::LogLevel::None);
		Core::Debug::Log::Print("Init scene 1\n", Core::Debug::LogLevel::Notification);

		LowRenderer::Model basicSphere = LowRenderer::Model(
			resources.GetResource<Resources::Mesh>("Sphere"),
			resources.GetResource<Resources::Shader>("BasicShader"),
			resources.GetResource<Resources::Texture>("Wall"));

		LowRenderer::GameObject* sphere1 = new LowRenderer::GameObject(basicSphere, Physics::Transform(
			Core::Maths::Vec3(-21.f, 4.0f, -11.f),
			Core::Maths::Vec3(4.0f, 4.0f, 4.0f),
			Core::Maths::Vec3(0.f, 0.f, 0.f)), "Sphere1");

		currentScene->CreateCollider(resources.GetResource<Resources::Mesh>("SphereCollider"), resources.GetResource<Resources::Shader>("ColliderShader"), Physics::ColliderTypes::Sphere, true);
		currentScene->AddGameObject(sphere1);
		sphere1->SetCollider(currentScene->GetLastCollider());
		sphere1->GetRigidbody().useGravity = false;
		Physics::Collider* playerCollider = sphere1->GetCollider();
		Physics::SphereCollider* sphereCollider = dynamic_cast<Physics::SphereCollider*>(playerCollider);
		sphereCollider->radius = 1.46f;

		LowRenderer::Camera* camera = new LowRenderer::Camera();
		currentScene->AddGameObject(camera, LowRenderer::GOType::Camera);

		// Patrick (PLAYER)
		LowRenderer::GameObject* skipper = new LowRenderer::GameObject(LowRenderer::Model(
			resources.GetResource<Resources::Mesh>("Patrick"),
			resources.GetResource<Resources::Shader>("BasicShader"),
			resources.GetResource<Resources::Texture>("PatrickText")),
			Physics::Transform(
				Core::Maths::Vec3(7.f, 1.f, 0.f),
				Core::Maths::Vec3(2.f, 2.f, 2.f),
				Core::Maths::Vec3(0.f, 0.f, 0.f)), "Player");

		currentScene->CreateCollider(resources.GetResource<Resources::Mesh>("SphereCollider"), resources.GetResource<Resources::Shader>("ColliderShader"), Physics::ColliderTypes::Sphere, false);
		skipper->SetCollider(currentScene->GetLastCollider());	
		skipper->GetRigidbody().useGravity = true;
		skipper->SetEnablePlayerControler(true);
		playerCollider = skipper->GetCollider();
		sphereCollider = dynamic_cast<Physics::SphereCollider*>(playerCollider);
		sphereCollider->center = { 0,0.5f,0.0f };
		sphereCollider->radius = 0.5f;
		currentScene->AddGameObject(skipper, LowRenderer::GOType::Player);

		Assertion(currentScene->SetParent("Player", "Camera"), "Fail to set parent");

		LowRenderer::Model basicBox = LowRenderer::Model(
			resources.GetResource<Resources::Mesh>("Cube"),
			resources.GetResource<Resources::Shader>("BasicShader"),
			resources.GetResource<Resources::Texture>("Wall"));

		LowRenderer::GameObject* box1 = new LowRenderer::GameObject(basicBox, Physics::Transform(
			Core::Maths::Vec3(0.f, -5.f, 0.f),
			Core::Maths::Vec3(15.f, 1.f, 10.f),
			Core::Maths::Vec3(0.f, 0.f, 0.f)), "Box1");

		currentScene->AddGameObject(box1);
		currentScene->CreateCollider(resources.GetResource<Resources::Mesh>("BoxCollider"), resources.GetResource<Resources::Shader>("ColliderShader"),Physics::ColliderTypes::Box, true);
		box1->SetCollider(currentScene->GetLastCollider());
		box1->GetRigidbody().useGravity = false;

		LowRenderer::GameObject* box3 = new LowRenderer::GameObject(basicBox, Physics::Transform(
			Core::Maths::Vec3(0.f, -3.0f, 0.f),
			Core::Maths::Vec3(1.f, 1.f, 1.f),
			Core::Maths::Vec3(0.f, 0.f, 0.f)), "Box3");

		// ========= Phyics =========
		currentScene->CreateCollider(resources.GetResource<Resources::Mesh>("BoxCollider"), resources.GetResource<Resources::Shader>("ColliderShader"),Physics::ColliderTypes::Box, true);
		currentScene->AddGameObject(box3);
		box3->SetCollider(currentScene->GetLastCollider());
		// ========= ==================== =========

		LowRenderer::GameObject* box5 = new LowRenderer::GameObject(basicBox, Physics::Transform(
			Core::Maths::Vec3(-6.f, 0.f, 1.f),
			Core::Maths::Vec3(1.f, 1.f, 1.f),
			Core::Maths::Vec3(0.f, 0.f, 0.f)), "Box5");

		currentScene->CreateCollider(resources.GetResource<Resources::Mesh>("BoxCollider"), resources.GetResource<Resources::Shader>("ColliderShader"), Physics::ColliderTypes::Box,true);
		currentScene->AddGameObject(box5);
		box5->SetCollider(currentScene->GetLastCollider());
		box5->GetRigidbody().useGravity = false;

		LowRenderer::GameObject* box6 = new LowRenderer::GameObject(basicBox, Physics::Transform(
			Core::Maths::Vec3(-9.f, 2.f, -5.f),
			Core::Maths::Vec3(2.f, .5f, 3.f),
			Core::Maths::Vec3(0.f, 0.f, 0.f)), "Box6");

		currentScene->CreateCollider(resources.GetResource<Resources::Mesh>("BoxCollider"), resources.GetResource<Resources::Shader>("ColliderShader"), Physics::ColliderTypes::Box, true);
		currentScene->AddGameObject(box6);
		box6->SetCollider(currentScene->GetLastCollider());
		box6->GetRigidbody().useGravity = false;

		LowRenderer::GameObject* box7 = new LowRenderer::GameObject(basicBox, Physics::Transform(
			Core::Maths::Vec3(-15.f, 2.f, 6.f),
			Core::Maths::Vec3(2.f, .5f, 3.f),
			Core::Maths::Vec3(0.f, 0.f, 0.f)), "Box7");

		currentScene->CreateCollider(resources.GetResource<Resources::Mesh>("BoxCollider"), resources.GetResource<Resources::Shader>("ColliderShader"), Physics::ColliderTypes::Box, true);
		currentScene->AddGameObject(box7);
		box7->SetCollider(currentScene->GetLastCollider());
		box7->GetRigidbody().useGravity = false;

		LowRenderer::GameObject* box8 = new LowRenderer::GameObject(basicBox, Physics::Transform(
			Core::Maths::Vec3(-25.f, 2.f, 0.f),
			Core::Maths::Vec3(1.5f, .5f,1.5f),
			Core::Maths::Vec3(0.f, 0.f, 0.f)), "Box8");


		currentScene->CreateCollider(resources.GetResource<Resources::Mesh>("BoxCollider"), resources.GetResource<Resources::Shader>("ColliderShader"), Physics::ColliderTypes::Box, true);
		currentScene->AddGameObject(box8);
		box8->SetCollider(currentScene->GetLastCollider());
		box8->GetRigidbody().useGravity = false;


		LowRenderer::GameObject* box9 = new LowRenderer::GameObject(basicBox, Physics::Transform(
			Core::Maths::Vec3(-20.f, -2.f, 0.f),
			Core::Maths::Vec3(1.5f, .5f, 1.5f),
			Core::Maths::Vec3(0.f, 0.f, 0.f)), "Box9");


		currentScene->CreateCollider(resources.GetResource<Resources::Mesh>("BoxCollider"), resources.GetResource<Resources::Shader>("ColliderShader"), Physics::ColliderTypes::Box, true);
		currentScene->AddGameObject(box9);
		box9->SetCollider(currentScene->GetLastCollider());
		box9->GetRigidbody().useGravity = false;

		LowRenderer::GameObject* box10 = new LowRenderer::GameObject(basicBox, Physics::Transform(
			Core::Maths::Vec3(-20.f, -2.f, 4.f),
			Core::Maths::Vec3(1.5f, .5f, 1.5f),
			Core::Maths::Vec3(0.f, 0.f, 0.f)), "Box10");


		currentScene->CreateCollider(resources.GetResource<Resources::Mesh>("BoxCollider"), resources.GetResource<Resources::Shader>("ColliderShader"), Physics::ColliderTypes::Box, true);
		currentScene->AddGameObject(box10);
		box10->SetCollider(currentScene->GetLastCollider());
		box10->GetRigidbody().useGravity = false;
		
		// Pistol	
		LowRenderer::GameObject* pistol = new LowRenderer::GameObject(LowRenderer::Model(
			resources.GetResource<Resources::Mesh>("Pistol"),
			resources.GetResource<Resources::Shader>("BasicShader"),
			resources.GetResource<Resources::Texture>("PistolText")),
			Physics::Transform(
				Core::Maths::Vec3(.25f, .3f, -.1f),
				Core::Maths::Vec3(.1f, .1f, .1f),
				Core::Maths::Vec3(0.f, 0.f, -35.f)), "Pistol");

		currentScene->AddGameObject(pistol);

		Assertion(currentScene->SetParent("Player", "Pistol"), "Fail to set parent");

		// Slime	
		LowRenderer::GameObject* slime = new LowRenderer::GameObject(LowRenderer::Model(
			resources.GetResource<Resources::Mesh>("Slime"),
			resources.GetResource<Resources::Shader>("BasicShader"),
			resources.GetResource<Resources::Texture>("SlimeText")),
			Physics::Transform(
				Core::Maths::Vec3(-23.f, 4.f, 11.f),
				Core::Maths::Vec3(1.f, 1.f, 1.f),
				Core::Maths::Vec3(0.f, 25.f, -22.f)), "Slime");

		currentScene->AddGameObject(slime);

		// Companion
		LowRenderer::GameObject* companion = new LowRenderer::GameObject(LowRenderer::Model(
			resources.GetResource<Resources::Mesh>("Companion"),
			resources.GetResource<Resources::Shader>("BasicShader"),
			resources.GetResource<Resources::Texture>("CompanionText")), Physics::Transform(
			Core::Maths::Vec3(-5.f, 3.f, 6.f),
			Core::Maths::Vec3(0.1f, 0.1f, 0.1f),
			Core::Maths::Vec3(0.f, 0.f, 0.f)), "Companion");

		currentScene->AddGameObject(companion);

		// PotatOs
		LowRenderer::GameObject* potatOS = new LowRenderer::GameObject(LowRenderer::Model(
			resources.GetResource<Resources::Mesh>("PotatOS"),
			resources.GetResource<Resources::Shader>("BasicShader"),
			resources.GetResource<Resources::Texture>("PotatOSText")), Physics::Transform(
				Core::Maths::Vec3(-1.f, -2.f, -5.f),
				Core::Maths::Vec3(0.2f, 0.2f, 0.2f),
				Core::Maths::Vec3(0.f, 45.f, 0.f)), "PotatOs");

		currentScene->AddGameObject(potatOS);

		// Chocobo
		LowRenderer::GameObject* chocobo = new LowRenderer::GameObject(LowRenderer::Model(
			resources.GetResource<Resources::Mesh>("Chocobo"),
			resources.GetResource<Resources::Shader>("BasicShader"),
			resources.GetResource<Resources::Texture>("ChocoboText")), Physics::Transform(
				Core::Maths::Vec3(6.f, -4.f, 4.f),
				Core::Maths::Vec3(0.02f, 0.02f, 0.02f),
				Core::Maths::Vec3(0.f, 150.f, -180.f)), "Chocobo");

		currentScene->AddGameObject(chocobo);

		// FryingPan
		LowRenderer::GameObject* pan = new LowRenderer::GameObject(LowRenderer::Model(
			resources.GetResource<Resources::Mesh>("FryingPan"),
			resources.GetResource<Resources::Shader>("BasicShader"),
			resources.GetResource<Resources::Texture>("FryingPanText")), Physics::Transform(
				Core::Maths::Vec3(-0.35f, 0.45f, -0.1f),
				Core::Maths::Vec3(0.025f, 0.025f, 0.025f),
				Core::Maths::Vec3(45.f, 90.f, 135.f)), "FryingPan");

		currentScene->AddGameObject(pan);
		Assertion(currentScene->SetParent("Player", "FryingPan"), "Fail to set parent");

		LowRenderer::InitLight initLight
		{
			Core::Maths::Vec3(2.f, 1.f, 0.f),	   // position
			Core::Maths::Vec4(.3f, .3f, .3f, 1.0f), // ambientColor
			Core::Maths::Vec4(1.f, 0.f, 0.f, 1.0f), // diffuseColor
			Core::Maths::Vec4(.9f, .9f, .9f, 1.f)  // specularColor 
		};


		currentScene->AddDirectionLight(LowRenderer::DirectionLight(initLight, Core::Maths::Vec3(0.f, 0.f, 1.f)));

		currentScene->AddPointLight(LowRenderer::PointLight(initLight, 1.f, 0.09f, 0.032f));

		initLight.position = Core::Maths::Vec3(-2.f, 8.f, 0.f);
		currentScene->AddSpotLight(LowRenderer::SpotLight(initLight, Core::Maths::Vec3(0.f, -1.f, 0.f), 12.5f, 0.82f));
	}


}