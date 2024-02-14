#pragma once
#include <Windows.h>
#include <cstdint>

class WinApp{
public:
	// クライアント領域のサイズ
	static const int32_t kClientWidth = 1280;
	static const int32_t kClientHeight = 720;
	
	// ウィンドウプロシーシャ
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	static void CreateWindowView(const wchar_t* title);

private:

	static inline	WNDCLASS wc{};// ウィンドウクラス
	static	HWND hwnd_;

};

