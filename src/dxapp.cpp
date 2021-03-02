#include "wunise/dxapp.h"
#include <utility>
namespace wunise {
    DXAPP::DXAPP(DXAPP&& r) noexcept
    {
        m_Device = std::move(r.m_Device);
        m_DeviceContext = std::move(r.m_DeviceContext);
    }

    DXAPP& DXAPP::operator=(DXAPP&& r) noexcept
    {
        m_Device = std::move(r.m_Device);
        m_DeviceContext = std::move(r.m_DeviceContext);
        return *this;
    }

	void DXAPP::InitDevice() {
        UINT createDeviceFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
        createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
        D3D_FEATURE_LEVEL featureLevel;

        D3D_FEATURE_LEVEL featurearray[] = {
            D3D_FEATURE_LEVEL_11_1,
            D3D_FEATURE_LEVEL_11_0,
            D3D_FEATURE_LEVEL_10_1,
            D3D_FEATURE_LEVEL_10_0,
            D3D_FEATURE_LEVEL_9_3,
            D3D_FEATURE_LEVEL_9_2,
            D3D_FEATURE_LEVEL_9_1,
        };;

        D3D11CreateDevice(
            0, // default adapter
            D3D_DRIVER_TYPE_HARDWARE,
            0, // no software device
            createDeviceFlags,
            featurearray, 7, // default feature level array
            D3D11_SDK_VERSION,
            &m_Device,
            &featureLevel,
            &m_DeviceContext);
	}
}