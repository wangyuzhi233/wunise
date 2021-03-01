#include "wunise/mygl.h"
#include <Windows.h>
#include <gl/GL.h>
#define GL_VERTEX_SHADER 0x8B31
#define GL_FRAGMENT_SHADER 0x8B30
#define GL_STATIC_DRAW 0x88E4

typedef char GLchar;

typedef GLuint(__stdcall* __PFNGLCREATESHADERPROC) (GLenum type);
typedef void (__stdcall* __PFNGLSHADERSOURCEPROC) (GLuint shader, GLsizei count, const GLchar* const* string, const GLint* length);
typedef void (__stdcall* __PFNGLCOMPILESHADERPROC) (GLuint shader);
typedef GLuint(__stdcall* __PFNGLCREATEPROGRAMPROC) (void);
typedef void (__stdcall* __PFNGLATTACHSHADERPROC) (GLuint program, GLuint shader);
typedef void (__stdcall* __PFNGLLINKPROGRAMPROC) (GLuint program);
typedef void (__stdcall* __PFNGLDELETESHADERPROC) (GLuint shader);

GLuint __stdcall __glCreateShader(GLenum type) {
    auto p = (__PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader");
    return p(type);
}

void __stdcall __glShaderSource(GLuint shader, GLsizei count, const GLchar* const* string, const GLint* length) {
    auto p = (__PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource");
    return p(shader, count, string, length);
}

void __stdcall __glCompileShader(GLuint shader) {
    auto p = (__PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader");
    return p(shader);
}

GLuint __stdcall __glCreateProgram(void) {
    auto p = (__PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram");
    return p();
}

void __stdcall __glAttachShader(GLuint program, GLuint shader) {
    auto p = (__PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader");
    return p(program, shader);
}


void __stdcall __glLinkProgram(GLuint program) {
    auto p = (__PFNGLLINKPROGRAMPROC)wglGetProcAddress("glLinkProgram");
    return p(program);
}

void __stdcall __glDeleteShader(GLuint shader) {
    auto p = (__PFNGLDELETESHADERPROC)wglGetProcAddress("glDeleteShader");
    return p(shader);
}



namespace wunise {
	void GLObject::InitShader(std::string vs, std::string fs) {
        const char* vertexShaderSource = vs.c_str();
        unsigned int vertexShader = __glCreateShader(GL_VERTEX_SHADER);
        __glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        __glCompileShader(vertexShader);
        const char* fragmentShaderSource = fs.c_str();
        // fragment shader
        unsigned int fragmentShader = __glCreateShader(GL_FRAGMENT_SHADER);
        __glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        __glCompileShader(fragmentShader);

        // link shaders
        unsigned int shaderProgram = __glCreateProgram();
        __glAttachShader(shaderProgram, vertexShader);
        __glAttachShader(shaderProgram, fragmentShader);
        __glLinkProgram(shaderProgram);

        __glDeleteShader(vertexShader);
        __glDeleteShader(fragmentShader);
	}
}