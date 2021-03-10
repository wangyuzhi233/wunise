#pragma once
#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__
namespace wunise {
	class GraphicsDevice {
	public:
		GraphicsDevice() {}
		~GraphicsDevice() = default;
		
		GraphicsDevice(GraphicsDevice&&) = default;
		GraphicsDevice& operator=(GraphicsDevice&&) = default;

		GraphicsDevice(const GraphicsDevice&) = delete;
		GraphicsDevice& operator=(const GraphicsDevice&) = delete;
	private:
	};
}
#endif // !__GRAPHICS_H__
