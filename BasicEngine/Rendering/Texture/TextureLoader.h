#pragma once
#include <gl\glew.h>
#include <fstream>
#include <iostream>
#include <string>
#include "BMPHeaders.h"

namespace BasicEngine {
	namespace Rendering
	{


		class TextureLoader
		{
		public:
			TextureLoader();
			~TextureLoader();

			unsigned int LoadTexture(const std::string& filename, GLuint width, GLuint height);

		private:
			void LoadBMPFile(const std::string& filename, unsigned int& width, unsigned int& height, unsigned char*& data);
		};

	}
}