#pragma once
#ifndef __GAMETIME_H__
#define __GAMETIME_H__
namespace wunise {
	class GameTime {
	public:
		GameTime() {}
		~GameTime() {}
		GameTime(const GameTime&) {}
		GameTime(GameTime&&) noexcept {}
		GameTime& operator=(const GameTime&) { return *this; }
		GameTime& operator=(GameTime&&) noexcept { return *this; }
	private:
	};
}
#endif // !__GAMETIME_H__
