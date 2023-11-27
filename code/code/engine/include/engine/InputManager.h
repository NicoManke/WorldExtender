#pragma once

#include <glad/glad.h>
#include "GLFW/glfw3.h"

namespace ChunkMapEngine {
	/// the Inputmanager class functions as an Interface for monitoring key inputs and simple synchronization of caused actions. The implementation follows the Template Method design pattern.
	class InputManager {
	public:
		InputManager() { };
		InputManager(GLFWwindow* window);
		/// monitors key inputs and calls the associated virtual function if the corresponding key is pressed.
		void manageKeyInputs(GLFWwindow* currentWindow);
	protected:
		/// override to define unique behavior caused by pressing the SPACE key.
		virtual void onKeyDownSPACE() { }
		/// override to define unique behavior caused by pressing the left SHIFT key.
		virtual void onKeyDownSHIFT() { }
		/// override to define unique behavior caused by pressing the ESCAPE key.
		virtual void onKeyDownESC() { }
		/// override to define unique behavior caused by pressing the TAB key.
		virtual void onKeyDownTAB() { }
		/// override to define unique behavior caused by pressing the W key.
		virtual void onKeyDownW() { }
		/// override to define unique behavior caused by pressing the A key.
		virtual void onKeyDownA() { }
		/// override to define unique behavior caused by pressing the S key.
		virtual void onKeyDownS() { }
		/// override to define unique behavior caused by pressing the D key.
		virtual void onKeyDownD() { }
		/// override to define unique behavior caused by pressing the Q key.
		virtual void onKeyDownQ() { }
		/// override to define unique behavior caused by pressing the E key.
		virtual void onKeyDownE() { }
		/// override to define unique behavior caused by pressing the R key.
		virtual void onKeyDownR() { }
		/// override to define unique behavior caused by pressing the F key.
		virtual void onKeyDownF() { }
	protected:
		GLFWwindow* window;
	private:
		bool isPressedSPACE = false;
		bool isPressedSHIFT = false;
		bool isPressedESC = false;
		bool isPressedTAB = false;
		bool isPressedW = false;
		bool isPressedA = false;
		bool isPressedS = false;
		bool isPressedD = false;
		bool isPressedQ = false;
		bool isPressedE = false;
		bool isPressedR = false;
		bool isPressedF = false;
	};
}