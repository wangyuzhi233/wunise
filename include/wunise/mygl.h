#pragma once
#ifndef __MYGL__H__
#define __MYGL__H__

namespace wunise {
	class GLObject {
	public:
		GLObject() {}
		~GLObject() {}
		GLObject(const GLObject&) {}
		GLObject(GLObject&&) noexcept {}
		GLObject& operator=(const GLObject&) { return *this; }
		GLObject& operator=(GLObject&&) noexcept { return *this; }
	private:
	};
}
#endif