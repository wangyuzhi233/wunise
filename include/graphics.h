#pragma once
#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

namespace wunise {
	class GraphicsDevice {
	public:
		GraphicsDevice() {}
		~GraphicsDevice() = default;
		
		GraphicsDevice(GraphicsDevice&&) noexcept = default;
		GraphicsDevice& operator=(GraphicsDevice&&) noexcept = default;

		GraphicsDevice(const GraphicsDevice&) = delete;
		GraphicsDevice& operator=(const GraphicsDevice&) = delete;
	private:
	};
}
#endif // !__GRAPHICS_H__
