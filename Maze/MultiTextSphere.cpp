#include "MultiTextSphere.h"
#include "../BasicEngine/Core/Camera.h"
using namespace BasicEngine::Rendering;

extern BasicEngine::Camera* activeCamera;

const float PI = (float)3.14159;
int indicesSize;
std::chrono::time_point<std::chrono::steady_clock> startTime;

MultiTextSphere::MultiTextSphere() {

}

MultiTextSphere::~MultiTextSphere() {

}

void MultiTextSphere::CreateSphere(GLfloat radius, unsigned int rings, unsigned int sectors)
{
	std::vector<GLfloat> vertices;
	std::vector<GLfloat> texcoords;
	std::vector<GLushort> indices;

	float const RingsRecip = (float)1.0 / (float)(rings - 1);
	float const SectorsRecip = (float)1.0 / (float)(sectors - 1);
	size_t countRings, countSectors;

	vertices.resize(rings * sectors * 3);						// *3 because it's a vec3 (position)
	texcoords.resize(rings * sectors * 2);						// *2 because it's a vec2 (UVs)

	std::vector<GLfloat>::iterator v = vertices.begin();
	std::vector<GLfloat>::iterator t = texcoords.begin();

	// Calculate vertices' position and their respective texture coordinates 
	for (countRings = 0; countRings < rings; countRings++) {
		float const y = sin(-PI / 2 + PI * countRings * RingsRecip) * radius;

		for (countSectors = 0; countSectors < sectors; countSectors++) {
			float const x = cos(2 * PI * countSectors * SectorsRecip) * sin(PI * countRings * RingsRecip);
			float const z = sin(2 * PI * countSectors * SectorsRecip) * sin(PI * countRings * RingsRecip);

			*t++ = countSectors * SectorsRecip;
			*t++ = countRings * RingsRecip;

			*v++ = x * radius;
			*v++ = y;
			*v++ = z * radius;
		}
	}

	// Calculate indices 
	indices.resize(rings * sectors * 6);									// using GL_TRIANGLES with indices to draw, not GL_QUADS
	std::vector<GLushort>::iterator i = indices.begin();
	for (countRings = 0; countRings < rings - 1; countRings++) {
		for (countSectors = 0; countSectors < sectors - 1; countSectors++) {

			*i++ = (countRings + 0) * sectors + countSectors;				// added for half-symmetry
			*i++ = (countRings + 0) * sectors + (countSectors + 1);
			*i++ = (countRings + 1) * sectors + (countSectors + 1);
			*i++ = (countRings + 0) * sectors + countSectors;
			*i++ = (countRings + 1) * sectors + countSectors;
			*i++ = (countRings + 1) * sectors + (countSectors + 1);			// since we're using GL_TRIANGLE with indices to draw the mesh
		}
	}

	// Use the previous tutorial approach for storing everything in a VertexFormat(vec3 vertices, vex2 texCoords)
	GLuint vao, vbo, ibo;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	std::vector<VertexFormat> vertexData;

	int count = 0;
	for (size_t verts = 0; verts < vertices.size(); verts += 3) {
		for (size_t tex = count; tex < texcoords.size(); tex += 2) {
			vertexData.push_back(VertexFormat(glm::vec3(vertices[verts], vertices[verts + 1], vertices[verts + 2]),
				glm::vec2(texcoords[tex], texcoords[tex + 1])));
			count += 2;
			break;
		}
	}

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(VertexFormat), &vertexData[0], GL_STATIC_DRAW);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::texture)));
	glBindVertexArray(0);
	this->vao = vao;
	this->vbos.push_back(vbo);
	this->vbos.push_back(ibo);

	indicesSize = indices.size();		// index size must be passed to the glDrawElements() later on

	startTime = HiResTime::now();		// assume the app starts...now!
}

void MultiTextSphere::Draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix)
{
	glm::mat4 trenslationMatrix(viewMatrix);

	glUseProgram(program);
	glBindVertexArray(vao);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->GetTexture("BaseTexture"));
	unsigned int textureLocation = glGetUniformLocation(program, "nebulaTex1");
	glUniform1i(textureLocation, 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, this->GetTexture("SecondTexture"));
	unsigned int secondTextureLocation = glGetUniformLocation(program, "nebulaTex2");
	glUniform1i(secondTextureLocation, 1);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, this->GetTexture("ThirdTexture"));
	unsigned int thirdTextureLocation = glGetUniformLocation(program, "nebulaTex3");
	glUniform1i(thirdTextureLocation, 2);

	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, this->GetTexture("AlphaChanTexture"));
	unsigned int alphaChanTextureLocation = glGetUniformLocation(program, "alphaChanTex");
	glUniform1i(alphaChanTextureLocation, 3);

	trenslationMatrix = glm::translate(glm::vec3(2.0f*Maze::MazeGenerator::finishPosition->x,
		0,
		2.0f * Maze::MazeGenerator::finishPosition->y));

	Maze::MazeGenerator::finishPosition;

	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, this->GetTexture("RampTexture"));
	unsigned int rampTextureLocation = glGetUniformLocation(program, "rampTex");
	glUniform1i(rampTextureLocation, 4);

	auto endTime = HiResTime::now();
	DeltaTime dt = endTime - startTime;
	MiliSec dtMS = std::chrono::duration_cast<MiliSec>(dt);

	

	glUniform1f(glGetUniformLocation(program, "timer"), dtMS.count());	// tuck it in a uniform and pass it on to the shader
	glUniformMatrix4fv(glGetUniformLocation(program, "viewMatrix"), 1, false, &trenslationMatrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "camera"), 1, false, &activeCamera->getWorldToViewMatrix()[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "projectionMatrix"), 1, false, &projectionMatrix[0][0]);

	glCullFace(GL_BACK); // draw back face 
	glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_SHORT, 0);

	glCullFace(GL_FRONT); // draw front face
	glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_SHORT, 0);


}