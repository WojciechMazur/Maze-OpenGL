#include "TextureLoader.h"
using namespace BasicEngine::Rendering;


TextureLoader::TextureLoader()
{
}


TextureLoader::~TextureLoader()
{
}


unsigned int TextureLoader::LoadTexture(const std::string & filename, GLuint width, GLuint height)
{
	unsigned char* data;
	LoadBMPFile(filename, width, height, data);

	unsigned int glTextureObject;
	glGenTextures(1, &glTextureObject);
	glBindTexture(GL_TEXTURE_2D, glTextureObject);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	
	float maxAnisotropy = 0;;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnisotropy);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAnisotropy);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	//Generatete texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	delete data;
	glGenerateMipmap(GL_TEXTURE_2D);
	return glTextureObject;

}


void TextureLoader::LoadBMPFile(const std::string& filename, unsigned int& width, unsigned int& height, unsigned char*& data) {
	std::ifstream file(filename.c_str(), std::ios::in | std::ios::binary);
	if (!file.good())
	{
		std::cout << "Texture Loader: Cannot open texture file: " << filename.c_str() << std::endl;
		width = 0;
		height = 0;
		return;
	}

	//Reads the headers
	Texture::BMPHeader h;
	Texture::BMPHeaderInfo hInfo;
	file.read((char*)&(h.type[0]), sizeof(char));
	file.read((char*)&(h.type[1]), sizeof(char));
	file.read((char*)&(h.fLenght), sizeof(int));
	file.read((char*)&(h.rezerved1), sizeof(short));
	file.read((char*)&(h.rezerved2), sizeof(short));
	file.read((char*)&(h.offBits), sizeof(int));
	file.read((char*)&(hInfo), sizeof(Texture::BMPHeaderInfo));

	//Assigning memory (a pixel has 3 components, R, G, B)
	data = new unsigned char[hInfo.width*hInfo.height * 3];

	//Check if the line contains 4 byte groups
	long padd = 0;
	if ((hInfo.width * 3) % 4 != 0) padd = 4 - (hInfo.width * 3) % 4;

	//Save height &width
	width = hInfo.width;
	height = hInfo.height;

	long pointer;
	unsigned char r, g, b;
	//Reading the matrix
	for (unsigned int i = 0; i < height; i++)
	{
		for (unsigned int j = 0; j < width; j++)
		{
			file.read((char*)&b, 1);	//In bmp, the component order in the pixel is b,g,r (in Windows)
			file.read((char*)&g, 1);
			file.read((char*)&r, 1);

			pointer = (i*width + j) * 3;
			data[pointer] = r;
			data[pointer + 1] = g;
			data[pointer + 2] = b;
		}

		file.seekg(padd, std::ios_base::cur);
	}
	file.close();
}