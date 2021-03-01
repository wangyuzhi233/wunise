#pragma once
#ifndef __MYGL__H__
#define __MYGL__H__
#include <string>
namespace wunise {
	class GLObject {
	public:
		GLObject() {}
		~GLObject() {}
		GLObject(const GLObject&) {}
		GLObject(GLObject&&) noexcept {}
		GLObject& operator=(const GLObject&) { return *this; }
		GLObject& operator=(GLObject&&) noexcept { return *this; }

		void InitShader(std::string vs, std::string fs);		
	private:
		//unsigned int shaderProgram;
	};
}
#endif