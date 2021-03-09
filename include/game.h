#pragma once
#ifndef __GAME_H__
#define __GAME_H__
#include <Windows.h>
#include <d3d11_4.h>
#include <dxgi1_6.h>
#include <wrl/client.h>
namespace wunise {
    class Game
    {
    public:
        Game() noexcept;
        ~Game() = default;

        Game(Game&&) = default;
        Game& operator= (Game&&) = default;

        Game(Game const&) = delete;
        Game& operator= (Game const&) = delete;

        // Initialization and management
        void Initialize(HWND window);

        // Basic game loop
        void Tick();

        // Messages
        void OnActivated();
        void OnDeactivated();
        void OnSuspending();
        void OnResuming();
        void OnWindowSizeChanged(int width, int height);

        // Properties
        void GetDefaultSize(int& width, int& height) const noexcept;
    private:

        void CreateDevice();
        void CreateResources();

        // Device resources.
        HWND                                            m_window;
        int                                             m_outputWidth;
        int                                             m_outputHeight;

        D3D_FEATURE_LEVEL                               m_featureLevel;
        Microsoft::WRL::ComPtr<ID3D11Device1>           m_d3dDevice;
        Microsoft::WRL::ComPtr<ID3D11DeviceContext1>    m_d3dContext;

        Microsoft::WRL::ComPtr<IDXGISwapChain1>         m_swapChain;
        Microsoft::WRL::ComPtr<ID3D11RenderTargetView>  m_renderTargetView;
        Microsoft::WRL::ComPtr<ID3D11DepthStencilView>  m_depthStencilView;
    };
    namespace window {
        // Windows procedure
        LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    }
}
#endif // !__GAME_H__
