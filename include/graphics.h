#pragma once
#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__
namespace wunise {
	class GraphicsDevice {
	public:
		GraphicsDevice();
		~GraphicsDevice();
		GraphicsDevice(const GraphicsDevice&);
		GraphicsDevice(GraphicsDevice&&) noexcept;
		GraphicsDevice& operator=(const GraphicsDevice&);
		GraphicsDevice& operator=(GraphicsDevice&&) noexcept;

		void CreateDeivce();
	private:
	};
}
#endif // !__GRAPHICS_H__
