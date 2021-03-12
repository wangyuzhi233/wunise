#pragma once
#ifndef __RENDERSYSTEM_H__
#define __RENDERSYSTEM_H__
namespace wunise {
	class RenderSystem {
	public:
		RenderSystem() noexcept = default;
		virtual ~RenderSystem() = default;

		RenderSystem(RenderSystem&&) noexcept = default;
		RenderSystem& operator=(RenderSystem&&) noexcept = default;

		RenderSystem(const RenderSystem&) = delete;
		RenderSystem& operator=(const RenderSystem&) = delete;

	private:

	};
}
#endif // !__RENDERSYSTEM_H__
