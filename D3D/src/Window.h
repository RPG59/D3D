#include <Windows.h>
#include "Types.h"

namespace d3d {
	class Window
	{
	private:
		uint m_Width, m_Height;
		string m_Title;
		HINSTANCE& m_HInstance;
		HDC m_HDC;
		HWND m_HWnd;
	private:
		bool Init();
		void WindowUpdate();
	public:
		Window(uint width, uint height, string title, HINSTANCE& hInstance);

	};
}
