#pragma once
#ifndef __GAME_H__
#define __GAME_H__
#include <memory>
namespace wunise {
    class Game
    {
    public:
        Game() noexcept;
        virtual ~Game();

        Game(Game&&) noexcept = default;
        Game& operator=(Game&&) noexcept = default;

        Game(const Game&) = delete;
        Game& operator=(const Game&) = delete;

        virtual void Initialize();

        virtual int Run() final; 
    private:
        std::unique_ptr<class GameWindow> window;
    };
}
#endif // !__GAME_H__
    