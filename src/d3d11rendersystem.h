#pragma once
#ifndef __D3D11RENDERERSYSTEM_H__
#define __D3D11RENDERERSYSTEM_H__
#include "rendersystem.h"
namespace wunise {
	class D3D11RenderSystem:public RenderSystem {
	public:
		D3D11RenderSystem() {}
		virtual ~D3D11RenderSystem() {}

		D3D11RenderSystem(D3D11RenderSystem&& r) noexcept {}
		D3D11RenderSystem& operator=(D3D11RenderSystem&& r) noexcept {}

		D3D11RenderSystem(const D3D11RenderSystem& r) = delete;
		D3D11RenderSystem& operator=(const D3D11RenderSystem& r) = delete;

		virtual void CreateDevice() override;
	private:
	};
}
#endif // !__D3D11RENDERERSYSTEM_H__
