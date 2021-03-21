#pragma once
#ifndef __MESH_H__
#define __MESH_H__
namespace wunise {
	class Mesh {
	public:
		Mesh() {}
		~Mesh() {}

		Mesh(Mesh&& r) noexcept = default;
		Mesh& operator=(Mesh&& r) noexcept = default;

		Mesh(const Mesh& r) = delete;
		Mesh& operator=(const Mesh& r) = delete;
	private:

	};
}
#endif // !__MESH_H__
