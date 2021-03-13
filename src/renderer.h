#pragma once
#ifndef __RENDERER_H__
#define __RENDERER_H__

namespace wunise {
	class Renderer {
	public:
		Renderer() noexcept {}
		~Renderer() {}

		Renderer(Renderer&& r) noexcept {}
		Renderer& operator=(Renderer&& r) noexcept {}

		Renderer(const Renderer& r) = delete;
		Renderer& operator=(const Renderer& r) = delete;


	private:

	};
}
#endif // !__RENDERER_H__
