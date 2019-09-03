#include "Window.h"
#include "D3DContext.h"
#include "Shader.h"

namespace d3d {
	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	Window::Window(uint width, uint height, string title, HINSTANCE& hInstance)
		: m_Width(width), m_Height(height), m_Title(title), m_HInstance(hInstance)
	{
		if (!Init())
		{
			return;
		}
		WindowUpdate();

	}

	bool Window::Init()
	{
		WNDCLASS winClass = {};
		winClass.hInstance = m_HInstance;
		winClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		winClass.lpfnWndProc = WndProc;
		winClass.lpszClassName = "D3D";
		winClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		winClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);

		if (!RegisterClass(&winClass))
		{
			return false;
		}

		RECT size = { 0, 0, (LONG)m_Width, (LONG)m_Height };
		AdjustWindowRectEx(&size, WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, false, WS_EX_APPWINDOW | WS_EX_WINDOWEDGE);

		m_HWnd = CreateWindowEx(
			NULL,
			winClass.lpszClassName,
			m_Title.c_str(),
			WS_OVERLAPPEDWINDOW,
			GetSystemMetrics(SM_CXSCREEN) / 2 - m_Width / 2,
			GetSystemMetrics(SM_CYSCREEN) / 2 - m_Height / 2,
			size.right + (-size.left),
			size.bottom + (-size.top),
			NULL,
			NULL,
			m_HInstance,
			NULL
		);

		if (!m_HWnd)
		{
			std::cout << "ERROR: HWND" << std::endl;
			return false;
		}
		ShowWindow(m_HWnd, SW_SHOW);
		SetFocus(m_HWnd);
		return true;
	}

	void Window::WindowUpdate()
	{
		D3DContext::s_Context = new D3DContext(m_HWnd, { 640, 480, false, false });
		graphics::Shader::CreateFromFile("shaders.shader", "shaders.shader");

		// create a triangle using the VERTEX struct
		struct COLOR 
		{ 
			FLOAT r, g, b, a; 
			COLOR(float _r, float _g, float _b, float _a)
			{
				r = _r;
				g = _g;
				b = _b;
				a = _a;
			};
		};
		struct VERTEX { FLOAT X, Y, Z; COLOR Color; };
		VERTEX OurVertices[] =
		{
			{0.0f, 0.5f, 0.0f, COLOR(1.0f, 0.0f, 0.0f, 1.0f)},
			{0.45f, -0.5, 0.0f, COLOR(0.0f, 1.0f, 0.0f, 1.0f)},
			{-0.45f, -0.5f, 0.0f, COLOR(0.0f, 0.0f, 1.0f, 1.0f)}
		};

		ID3D11Buffer* pVBuffer;                // the pointer to the vertex buffer


		// create the vertex buffer
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));

		bd.Usage = D3D11_USAGE_DYNAMIC;                // write access access by CPU and GPU
		bd.ByteWidth = sizeof(VERTEX) * 3;             // size is the VERTEX struct * 3
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;       // use as a vertex buffer
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;    // allow CPU to write in buffer

		D3DContext::GetDevice()->CreateBuffer(&bd, NULL, &pVBuffer);       // create the buffer


		// copy the vertices into the buffer
		D3D11_MAPPED_SUBRESOURCE ms;
		D3DContext::GetDeviceContext()->Map(pVBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);    // map the buffer
		memcpy(ms.pData, OurVertices, sizeof(OurVertices));                 // copy the data
	 	D3DContext::GetDeviceContext()->Unmap(pVBuffer, NULL);                                      // unmap the buffer






		MSG message;
		while (GetMessage(&message, NULL, NULL, NULL))
		{
			if (message.message == WM_QUIT)
			{
				return;
			}
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		// Renderer!

		D3DContext::GetDeviceContext()->ClearRenderTargetView(D3DContext::GetBackBuffer, {0.0f, 0.2f, 0.4f, 1.0f});

		// select which vertex buffer to display
		UINT stride = sizeof(VERTEX);
		UINT offset = 0;
		D3DContext::GetDeviceContext()->IASetVertexBuffers(0, 1, &pVBuffer, &stride, &offset);

		// select which primtive type we are using
		D3DContext::GetDeviceContext()->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// draw the vertex buffer to the back buffer
		D3DContext::GetDeviceContext()->Draw(3, 0);

		// switch the back buffer and the front buffer
		D3DContext::GetSwapChain()->Present(0, 0);



	}

	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		LRESULT result = NULL;
		switch (message)
		{
		case WM_ACTIVATE:
			if (!HIWORD(wParam))
			{

			}
			else
			{

			}
		default:
			break;
		}
		result = DefWindowProc(hWnd, message, wParam, lParam);
		return result;
	}
}

