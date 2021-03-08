#pragma once
#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

namespace wunise {
	class GraphicsDevice {
	public:
		GraphicsDevice() {}
		~GraphicsDevice() {}
		GraphicsDevice(const GraphicsDevice&) {}
		GraphicsDevice(GraphicsDevice&&) noexcept {}
		GraphicsDevice& operator=(const GraphicsDevice&) { return *this; }
		GraphicsDevice& operator=(GraphicsDevice&&) noexcept { return *this; }
	private:

	};
}
#endif // !__GRAPHICS_H__
