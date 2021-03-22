#pragma once
#ifndef __GAMEPAD_H__
#define __GAMEPAD_H__
namespace wunise {
	class GamePad {
	public:
		GamePad() {}
		~GamePad() {}

		GamePad(GamePad&& r)  = default;
		GamePad& operator=(GamePad&& r) noexcept = default;

		GamePad(const GamePad& r) = delete;
		GamePad& operator=(const GamePad& r) = delete;
	private:

	};
}
#endif // !__GAMEPAD_H__
