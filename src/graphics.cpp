#include "graphics.h"
#include <d3d11_4.h>
#include <dxgi1_6.h>
#include <wrl/client.h>
namespace wunise {
	GraphicsDevice::GraphicsDevice()
	{
	}
	GraphicsDevice::~GraphicsDevice()
	{
	}
	GraphicsDevice::GraphicsDevice(const GraphicsDevice& r)
	{
	}
	GraphicsDevice::GraphicsDevice(GraphicsDevice&& r) noexcept
	{

	}
	GraphicsDevice& GraphicsDevice::operator=(const GraphicsDevice& r)
	{
		return *this;
	}
	GraphicsDevice& GraphicsDevice::operator=(GraphicsDevice&& r) noexcept
	{
		return *this;
	}

	void GraphicsDevice::CreateDeivce() {}

}