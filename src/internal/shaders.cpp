#include "internal/shaders.h"

#include "assets/shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

static const char *sliBasicVertexShaderCode =
"#version 150 \n"
"uniform mat4 u_Projection;"
"uniform mat4 u_Modelview;"
"in vec2 a_Vertex;"
"void main()"
"{"
"gl_Position = u_Projection * u_Modelview * vec4(a_Vertex, 0.0, 1.0);"
"}";

static const char *sliBasicFragmentShaderCode =
"#version 150 \n"
"uniform vec4 u_Color;"
"out vec4 f_Color;"
"void main()"
"{"
"f_Color = u_Color;"
"}";

static const char *sliPointVertexShaderCode =
"#version 150 \n"
"uniform mat4 u_Projection;"
"in vec2 a_Vertex;"
"in vec4 a_Color;"
"out vec4 v_Color;"
"void main()"
"{"
"v_Color = a_Color;"
"gl_Position = u_Projection * vec4(a_Vertex, 0.0, 1.0);"
"}";

static const char *sliPointFragmentShaderCode =
"#version 150 \n"
"in vec4 v_Color;"
"out vec4 f_Color;"
"void main()"
"{"
"f_Color = v_Color;"
"}";

Shader *sliBasicShader;
Shader *sliPointShader;
Shader *sliTextureShader;

void sliShadersInit(mat4 &projection)
{
	sliBasicShader = new Shader(sliBasicVertexShaderCode, sliBasicFragmentShaderCode);
	sliBasicShader -> bindAttrib("a_Vertex", 0);
	sliBasicShader -> link();
	sliBasicShader -> bind();
	sliBasicShader -> uniformMatrix4fv("u_Projection", 1, value_ptr(projection));

	sliPointShader = new Shader(sliPointVertexShaderCode, sliPointFragmentShaderCode);
	sliPointShader -> bindAttrib("a_Vertex", 0);
	sliPointShader -> bindAttrib("a_Color", 1);
	sliPointShader -> link();
	sliPointShader -> bind();
	sliPointShader -> uniformMatrix4fv("u_Projection", 1, value_ptr(projection));
}
