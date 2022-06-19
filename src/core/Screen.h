#pragma once

#include <Windows.h>

#include <string>

#include "Buffer.h"

namespace MiniRenderer
{
	class Renderer;
	
	class Screen
	{
	public:
		void Init(const std::wstring& title, Renderer* renderer, int width = 800, int height = 600);
		void Show();
		void Update();
		void Destrroy();

		bool ShouldRun() { return s_runing; }
	public:
		static LRESULT CALLBACK WinSunProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		static void ResizeWindow(HWND hWnd);
	private:
		void messageDispatch();
		void setViewBitmap();
	private:
		std::wstring m_title;
	private:
		static int s_width;
		static int s_height;
		static bool s_runing;
		static HWND s_hWnd;
		static HDC s_hDC;
		static HBITMAP s_hBitmap;
		static BITMAPINFO s_bitmapInfo;
		static BITMAP s_viewBitmap;
		static Framebuffer* s_deviceFramebuffer;

		static Renderer* m_renderer;
	};
} // namespace MiniRenderer