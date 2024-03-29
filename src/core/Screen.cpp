#include "Screen.h"

#include "MiniRenderer.h"

namespace MiniRenderer
{
	int Screen::s_width = 800;
	int Screen::s_height = 600;
	bool Screen::s_runing = true;
	HWND Screen::s_hWnd = NULL;
	HDC Screen::s_hDC = NULL;
	HBITMAP Screen::s_hBitmap = NULL;
	BITMAPINFO Screen::s_bitmapInfo = BITMAPINFO();
	BITMAP Screen::s_viewBitmap = BITMAP();
	Framebuffer* Screen::s_deviceFramebuffer = nullptr;

	int Screen::s_keyPress[1024];
	int Screen::s_mousePress[1024];
	int Screen::s_wheelDelta = 0;
	bool Screen::s_isHovered = true;

	int Screen::s_fps = 0;

	Renderer* Screen::m_renderer = nullptr;

	Rasterizer* Renderer::GetPtrRasterizer()
	{
		return &m_rasterizer;
	}

	Profiler* Renderer::GetPtrProfiler()
	{
		return &m_profiler;
	}

	Camera* Renderer::GetPtrCamera()
	{
		return m_camera.get();
	}
	
	void Screen::Init(const std::wstring& title, Renderer* renderer, int width, int height)
	{
		m_title = title;
		
		s_width = width;
		s_height = height;

		m_renderer = renderer;

		s_viewBitmap.bmWidth = width;
		s_viewBitmap.bmHeight = height;
		s_deviceFramebuffer = renderer->GetPtrRasterizer()->GetFramebuffer();
		
		WNDCLASS wc;
		wc.style = CS_BYTEALIGNCLIENT;
		wc.lpfnWndProc = WinSunProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = GetModuleHandle(NULL);
		wc.hIcon = NULL;
		wc.hCursor = NULL;
		wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wc.lpszMenuName = TEXT("MainWindow");
		wc.lpszClassName = TEXT("MainWindow");

		BITMAPINFOHEADER bitmapInfoHeader;
		bitmapInfoHeader.biSize = sizeof(BITMAPINFOHEADER);
		bitmapInfoHeader.biWidth = s_width;
		bitmapInfoHeader.biHeight = -s_height;
		bitmapInfoHeader.biPlanes = 1;
		bitmapInfoHeader.biBitCount = 32;
		bitmapInfoHeader.biCompression = BI_RGB;
		bitmapInfoHeader.biSizeImage = s_width * s_height * 4;
		bitmapInfoHeader.biXPelsPerMeter = 0;
		bitmapInfoHeader.biYPelsPerMeter = 0;
		bitmapInfoHeader.biClrUsed = 0;
		bitmapInfoHeader.biClrImportant = 0;

		s_bitmapInfo.bmiHeader = bitmapInfoHeader;

		if (!RegisterClass(&wc))
			throw std::runtime_error("Register window class failed!");

		// HMENU hMenu;
		// hMenu = CreateMenu();
		// AppendMenu(hMenu, MF_STRING, 0x11, TEXT("Capture Screen"));

		RECT rect{ 0, 0, width, height };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);
		auto windowWidth = rect.right - rect.left;
		auto windowHeight = rect.bottom - rect.top;
		auto windowLeft = (GetSystemMetrics(SM_CXSCREEN) - windowWidth) / 4;
		auto windowRight = (GetSystemMetrics(SM_CYSCREEN) - windowHeight) / 4;
		windowLeft = windowLeft >= 0 ? windowLeft : 0;
		windowHeight = windowHeight >= 0 ? windowHeight : 0;
		s_hWnd = CreateWindow(TEXT("MainWindow"), title.c_str(), WS_OVERLAPPEDWINDOW,
			windowLeft, windowRight, windowWidth, windowHeight,
			NULL, /*hMenu*/ NULL, wc.hInstance, NULL);

		if (s_hWnd == NULL)
			throw std::runtime_error("Create window failed!");

		HDC hDC = GetDC(s_hWnd);
		s_hDC = CreateCompatibleDC(hDC);
		ReleaseDC(s_hWnd, hDC);

		s_hBitmap = CreateDIBSection(s_hDC, &s_bitmapInfo, DIB_RGB_COLORS, &s_viewBitmap.bmBits, 0, 0);

		if (s_hBitmap == NULL)
			throw std::runtime_error("Create bitmap failed!");

		SelectObject(s_hDC, s_hBitmap);

		m_tFPS = std::thread(ShowFPS, m_title);
		m_tFPS.detach();
	}

	void Screen::Show()
	{
		SetForegroundWindow(s_hWnd);
		ShowWindow(s_hWnd, SW_SHOWNORMAL);
		//UpdateWindow(m_hWnd);
	}

	void Screen::Update()
	{
		//int i = 0;
		//for (unsigned int* it = (unsigned int*)s_viewBitmap.bmBits; i < m_width * m_height; it++) {
		//	*it = 0xffeeaa88;
		//	i++;
		//}

		// float FPS = m_renderer->GetPtrProfiler()->GetFPS();
		// auto newTitle = m_title + TEXT("   FPS: ") + std::to_wstring(FPS);
		// SetWindowText(s_hWnd, newTitle.c_str());

		setViewBitmap();
		
		HDC hDC = GetDC(s_hWnd);
		BitBlt(hDC, 0, 0, s_width, s_height, s_hDC, 0, 0, SRCCOPY);
		ReleaseDC(s_hWnd, hDC);
		
		messageDispatch();

		s_fps++;
	}

	void Screen::Destrroy()
	{
		DestroyWindow(s_hWnd);
		PostQuitMessage(0);
	}

	LRESULT CALLBACK Screen::WinSunProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		short delta = 0;
		
		switch (uMsg)
		{
		case WM_SIZE:
			ResizeWindow(hWnd);
			break;
		case WM_CLOSE:
			s_runing = false;
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		// Key buttom
		case WM_KEYDOWN:
			s_keyPress[wParam & 1023] = 1;
			break;
		case WM_KEYUP:
			s_keyPress[wParam & 1023] = 0;
			break;
		// TODO: Mouse move
		case WM_MOUSEHOVER:
			s_isHovered = true;
			break;
		case WM_MOUSELEAVE:
			s_isHovered = false;
			break;
		// Mouse button
		case WM_LBUTTONDOWN:
			SetCapture(s_hWnd);
			s_mousePress[Mouse::Left & 1023] = 1;
			break;
		case WM_MBUTTONDOWN:
			SetCapture(s_hWnd);
			s_mousePress[Mouse::Middle & 1023] = 1;
			break;
		case WM_RBUTTONDOWN:
			SetCapture(s_hWnd);
			s_mousePress[Mouse::Right & 1023] = 1;
			break;
		case WM_LBUTTONUP:
			ReleaseCapture();
			s_mousePress[Mouse::Left & 1023] = 0;
			break;
		case WM_MBUTTONUP:
			ReleaseCapture();
			s_mousePress[Mouse::Middle & 1023] = 0;
			break;
		case WM_RBUTTONUP:
			ReleaseCapture();
			s_mousePress[Mouse::Right & 1023] = 0;
			break;
		// Mouse wheel
		case WM_MOUSEWHEEL:
			delta = HIWORD(wParam);
			delta /= WHEEL_DELTA;
			s_wheelDelta = delta;
			break;
		default:
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}
		return 0;
	}

	void Screen::ResizeWindow(HWND hWnd)
	{
		RECT rect{ 0, 0, 0, 0 };
		GetClientRect(s_hWnd, &rect);
		auto windowWidth = rect.right - rect.left;
		auto windowHeight = rect.bottom - rect.top;

		if (windowWidth == 0 || windowHeight == 0)
			return;

		DeleteObject(s_hBitmap);

		s_width = windowWidth;
		s_height = windowHeight;
		
		s_bitmapInfo.bmiHeader.biWidth = windowWidth;
		s_bitmapInfo.bmiHeader.biHeight = -windowHeight;

		s_viewBitmap.bmWidth = windowWidth;
		s_viewBitmap.bmHeight = windowHeight;
		s_hBitmap = CreateDIBSection(s_hDC, &s_bitmapInfo, DIB_RGB_COLORS, &s_viewBitmap.bmBits, 0, 0);

		if (s_hBitmap == NULL)
			throw std::runtime_error("Create bitmap failed!");

		SelectObject(s_hDC, s_hBitmap);

		m_renderer->GetPtrRasterizer()->SetBufferSize(windowWidth, windowHeight);
		if (m_renderer->GetPtrCamera())
			m_renderer->GetPtrCamera()->Resize(windowWidth, windowHeight);
	}

	void Screen::ShowFPS(const std::wstring& m_title)
	{
		while (true)
		{
			Sleep(1000);

			auto newTitle = m_title + TEXT("   FPS: ") + std::to_wstring(s_fps);
			SetWindowText(s_hWnd, newTitle.c_str());

			s_fps = 0;
		}
	}

	void Screen::messageDispatch()
	{
		MSG msg;
		while (1)
		{
			if (!PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
				break;
			if (!GetMessage(&msg, NULL, 0, 0))
				break;
			DispatchMessage(&msg);
		}
	}

	void Screen::setViewBitmap()
	{
		int i = 0;
		Vec4* pixel = s_deviceFramebuffer->GetData();
		for (unsigned int* it = (unsigned int*)s_viewBitmap.bmBits; i < s_width * s_height; it++) {
			int r = Math::Clamp((int)(pixel->r * 255.0f), 0, 255);
			int g = Math::Clamp((int)(pixel->g * 255.0f), 0, 255);
			int b = Math::Clamp((int)(pixel->b * 255.0f), 0, 255);
			*it = (r << 16) | (g << 8) | b;
			pixel++;
			i++;
		}
	}
} // namespace MiniRenderer