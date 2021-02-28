#include "wunise/mygl.h"

#define GL_VERTEX_SHADER 0x8B31
#define GL_FRAGMENT_SHADER 0x8B30

namespace wunise {
	void GLObject::InitShader(std::string vs, std::string fs) {
        //const char* vertexShaderSource = vs.c_str();
        //unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        //glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        //glCompileShader(vertexShader);
        //const char* fragmentShaderSource = fs.c_str();
        //// fragment shader
        //unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        //glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        //glCompileShader(fragmentShader);

        //// link shaders
        //unsigned int shaderProgram = glCreateProgram();
        //glAttachShader(shaderProgram, vertexShader);
        //glAttachShader(shaderProgram, fragmentShader);
        //glLinkProgram(shaderProgram);

        //glDeleteShader(vertexShader);
        //glDeleteShader(fragmentShader);
	}
}