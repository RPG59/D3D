#pragma once

#include<d3d11.h>

#include "Types.h"


namespace d3d {

	struct WindowProps
	{
		uint width, height;
		bool isFullscreen;
		bool isVSync;
	};
	class D3DContext
	{
	private:
		ID3D11RenderTargetView* m_RenderTargetView = nullptr;
		ID3D11DepthStencilView* m_DepthStencilView = nullptr;
		D3D11_VIEWPORT m_ScreenViewport;
		ID3D11Texture2D* m_DepthStencilBuffer = nullptr;

		ID3D11Debug* m_DebugLayer = nullptr;
		D3D_FEATURE_LEVEL m_D3DFeatureLevel;

		WindowProps m_WindowProps;

		uint m_MSAAQuality;
		bool m_MSAAEnabled;
		bool m_DebugLayerEnabled;
	public:
		static D3DContext* s_Context;
		D3DContext(void* deviceContext, WindowProps props);
		//void Present();
	private:
		void InitD3D(HWND hWnd);
		void Resize();
		void SetRenderTargets(ID3D11RenderTargetView* target, ID3D11DepthStencilView* view);
	public:
		IDXGISwapChain* swapchain;
		ID3D11Device* dev;
		ID3D11DeviceContext* devCon;
		ID3D11RenderTargetView* backBuffer;
	public:
		inline static D3DContext* GetContext() { return s_Context; }
		inline static ID3D11Device* GetDevice() { return GetContext()->dev; }
		inline static ID3D11DeviceContext* GetDeviceContext() { return GetContext()->devCon; }
		inline static ID3D11RenderTargetView* GetBackBuffer() { return GetContext()->m_RenderTargetView; }
		inline static IDXGISwapChain* GetSwapChain() { return GetContext()->swapchain; }
	};
}
