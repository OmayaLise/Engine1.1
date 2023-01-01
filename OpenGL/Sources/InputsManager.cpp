#include "InputsManager.hpp"

namespace Core
{
	InputsManager::InputsManager(GLFWwindow* p_window)
		: mouseX(0.0)
		, mouseY(0.0)
		, mouseDeltaX(0.f)
		, mouseDeltaY(0.f)
		, mouseCaptured(false)
		, timeMouseCaptured(0)
		, window(p_window)
		, speed(0.05f)
	{
		isEnable = false;
	}

	const Inputs& InputsManager::Update()
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		Inputs inputs;

		// Camera inputs (keyboard)
		inputs.moveForward  = glfwGetKey(window, forward) == GLFW_PRESS;
		inputs.moveBackward = glfwGetKey(window, backward) == GLFW_PRESS;
		inputs.moveLeft		= glfwGetKey(window, left) == GLFW_PRESS;
		inputs.moveRight	= glfwGetKey(window, right) == GLFW_PRESS;
		inputs.moveDown		= glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS;
		inputs.moveUp		= glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS;
		inputs.jump			= glfwGetKey(window, jump) == GLFW_PRESS;
		inputs.quit			= glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS;

		glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
		// Editor activation 
		int state = (glfwGetKey(window, GLFW_KEY_F1));
			inputs.editor = editorState;
		if (state == GLFW_PRESS)
		{
			editorState = editorNextState;
		}
		else
		{
			editorNextState = !editorState;
		}

		
		// Camera inputs (mouse)
		if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
			mouseCaptured = false;

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
		{
			mouseCaptured = true;
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			timeMouseCaptured++;
		}
		else
		{
			mouseCaptured = false;
			timeMouseCaptured = 0;
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}

		if (mouseCaptured)
		{
			double newMouseX, newMouseY;
			glfwGetCursorPos(window, &newMouseX, &newMouseY);
			mouseDeltaX = (float)(newMouseX - mouseX);
			mouseDeltaY = (float)(mouseY - newMouseY);
			mouseX = newMouseX;
			mouseY = newMouseY;

			if (timeMouseCaptured == 1) // firstFrame
			{
				inputs.deltaX = 0.f;
				inputs.deltaY = 0.f;
			}
			else
			{
				inputs.deltaX = mouseDeltaX;
				inputs.deltaY = mouseDeltaY;
			}
		}
		else
		{
			inputs.deltaX = 0.f;
			inputs.deltaY = 0.f;
		}

		return inputs;
	}

	void InputsManager::ChangeInput(int p_input, ModifyInput p_modifyInput)
	{
		switch (p_modifyInput)
		{
		case Core::ModifyInput::Forward:
			forward = p_input;
			break;

		case Core::ModifyInput::Backward:
			backward = p_input;
			break;

		case Core::ModifyInput::Left:
			left = p_input;
			break;

		case Core::ModifyInput::Right:
			right = p_input;
			break;

		case Core::ModifyInput::Jump:
			jump = p_input;
			break;

		default:
			break;
		}
	}
}