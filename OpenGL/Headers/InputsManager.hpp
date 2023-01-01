#pragma once

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "IComponent.hpp"

namespace Core
{
	enum class ModifyInput
	{
		Forward,
		Backward,
		Left,
		Right,
		Jump,
		None,
	};

	struct Inputs
	{
		float deltaX = 0.f;
		float deltaY = 0.f;
		bool moveForward	= true;
		bool moveBackward	= true;
		bool moveRight		= true;
		bool moveLeft		= true;
		bool moveUp			= true;
		bool moveDown		= true;
		bool jump			= true;
		bool quit			= false;
		bool editor			= false;
	};

	class InputsManager : public DataStructure::IComponent
	{
		// Attribute
	private:
		double mouseX, mouseY;
		float mouseDeltaX, mouseDeltaY;
		bool mouseCaptured;
		unsigned int timeMouseCaptured;
		GLFWwindow* window;
		float speed;

		int forward  = GLFW_KEY_W;
		int backward = GLFW_KEY_S;
		int left	 = GLFW_KEY_A;
		int right	 = GLFW_KEY_D;
		int jump	 = GLFW_KEY_SPACE;

		bool editorState = false;
		bool editorNextState = true;

		// Methode
	public:
		InputsManager(GLFWwindow* p_window = nullptr);

		const Inputs& Update();

		void ChangeInput(int p_input, ModifyInput p_modifyInput);
		int GetForward() { return forward; };
		int GetBackward() { return backward; };
		int GetLeft() { return left; };
		int GetRight() { return right; };
		int GetJump() { return jump; };

		// Get and Set
		const float GetSpeed() const { return speed; };
		void SetWindow(GLFWwindow* p_window) { window = p_window; };
		GLFWwindow* GetWindow() { return window; };
	};
}