#include "engine/InputManager.h"
#include "engine/BaseGame.h"

namespace ChunkMapEngine {
	InputManager::InputManager(GLFWwindow* window) : window(window) { }

	void InputManager::manageKeyInputs(GLFWwindow* window)
	{
		this->window = window;
		// pressed SPACE
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && isPressedSPACE == false) {
			onKeyDownSPACE();
			isPressedSPACE = true;
		}
		else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) {
			isPressedSPACE = false;
		}
		// pressed SHIFT
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS && isPressedSHIFT == false) {
			onKeyDownW();
			isPressedSHIFT = true;
		}
		else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
			isPressedSHIFT = false;
		}
		// pressed ESC
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS && isPressedESC == false) {
			onKeyDownESC();
			isPressedESC = true;
		}
		else if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE) {
			isPressedESC = false;
		}
		// pressed TAB
		if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS && isPressedTAB == false) {
			onKeyDownTAB();
			isPressedTAB = true;
		}
		else if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_RELEASE) {
			isPressedTAB = false;
		}
		// pressed W
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && isPressedW == false) {
			onKeyDownW();
			isPressedW = true;
		}
		else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE) {
			isPressedW = false;
		}
		// pressed A
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && isPressedA == false) {
			onKeyDownA();
			isPressedA = true;
		}
		else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE) {
			isPressedA = false;
		}
		// pressed S
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && isPressedS == false) {
			onKeyDownS();
			isPressedS = true;
		}
		else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE) {
			isPressedS = false;
		}
		// pressed D
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && isPressedD == false) {
			onKeyDownD();
			isPressedD = true;
		}
		else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE) {
			isPressedD = false;
		}
		// pressed Q
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS && isPressedQ == false) {
			onKeyDownQ();
			isPressedQ = true;
		}
		else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_RELEASE) {
			isPressedQ = false;
		}
		// pressed E
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS && isPressedE == false) {
			onKeyDownE();
			isPressedE = true;
		}
		else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_RELEASE) {
			isPressedE = false;
		}
		// pressed R
		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS && isPressedR == false) {
			onKeyDownR();
			isPressedR = true;
		}
		else if (glfwGetKey(window, GLFW_KEY_R) == GLFW_RELEASE) {
			isPressedR = false;
		}
		// pressed F
		if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS && isPressedF == false) {
			onKeyDownF();
			isPressedF = true;
		}
		else if (glfwGetKey(window, GLFW_KEY_F) == GLFW_RELEASE) {
			isPressedF = false;
		}
	}
}