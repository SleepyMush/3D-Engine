#pragma once
#include <iostream>
#include <map>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Render/Shader.h"
#include <ft2build.h>
#include FT_FREETYPE_H 

struct Character {
	int TextureID; // ID handle of the glyph texture
	glm::ivec2   Size;      // Size of glyph
	glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
	unsigned int Advance;   // Horizontal offset to advance to next glyph
};
std::map<GLchar, Character> Characters;
GLuint textureArray;
std::vector<int>letterMap;
std::vector<glm::mat4>T;
unsigned int TVAO, TVBO;
const unsigned int ARRAY_LIMIT = 400;

class Text
{
public:
	void init();
	void RenderText(Shader& shader, std::string text, float x, float y, float scale, glm::vec3 color);
	void TextRenderCall(int length, GLuint shader);
};
