#pragma once
#include <iostream>
//#include <GL\glew.h>
#include <gl\glew.h>
#include <gl\freeglut.h>
namespace BasicEngine {
	namespace Core {
		namespace Init {
			class GLEW
			{
			public:
				GLEW();
				~GLEW();
				static void Init();
			};
		}
	}
}