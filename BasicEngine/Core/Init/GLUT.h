#pragma once

#include "ContextInfo.h"
#include "FrameBufferInfo.h"
#include "WindowInfo.h"
#include <iostream>
#include "GLEW.h"
#include "IListener.h"
#include "DebugOutput.h"
#include "..\..\Managers\SceneManager.h"
#include "..\Camera.h"

namespace BasicEngine {
	namespace Core {
		namespace Init {
			class GLUT {
			public:
				static void init(const Core::WindowInfo& window,
					const Core::ContextInfo& context,
					const Core::FramebufferInfo& framebufferInfo);

			public:
				static void run();
				static void close();
				void enterFullscreen();
				void exitFullscreen();

				static void printOpenGLInfo(const Core::WindowInfo& windowInfo, const Core::ContextInfo& context);

			private:
				static void IdleCallback(void);
				static void DisplayCallback(void);
				static void ReshapeCallback(int width, int height);
				static void CloseCallback();
				static void MouseMotionCallback(int x, int y);
				static void SpecialKeysInputCallback(int key, int x, int y);
				static void KeysInputCallback(unsigned char key, int x, int y);
			private:
				static IListener* listener;
				static WindowInfo windowInformation;

			public:
				static void setListener(Core::IListener* iListener);
			};
		}
	}
}