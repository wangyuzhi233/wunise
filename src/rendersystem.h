#pragma once
#ifndef __RENDERERSYSTEM_H__
#define __RENDERERSYSTEM_H__
namespace wunise {
	class RenderSystem {
	public:
		RenderSystem() {}
		virtual ~RenderSystem() {}

		RenderSystem(RenderSystem&& r) noexcept = default;
		RenderSystem& operator=(RenderSystem&& r) noexcept = default;

		RenderSystem(const RenderSystem& r) = delete;
		RenderSystem& operator=(const RenderSystem& r) = delete;

		virtual void CreateDevice() = 0;
	private:
	};
}
#endif // !__RENDERERSYSTEM_H__
