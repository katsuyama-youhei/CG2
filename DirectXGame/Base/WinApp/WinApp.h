#pragma once
#include <Windows.h>
#include <cstdint>

class WinApp {
public:
	static WinApp* GetInstance();

	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

public:
	static const wchar_t className[];
	static const int32_t kWindowWidth = 1280;
	static const int32_t kWindowHeight = 720;

public:
	void CreateGameWindow(const wchar_t* title = L"CG2", UINT windowStyle = WS_OVERLAPPEDWINDOW, int32_t windowWidth = kWindowWidth, int32_t windowHeight = kWindowHeight);

	void DiscardingWindow();

	bool ProcessMessage();

	inline HWND GetHWND() { return hwnd_; }
	inline WNDCLASS GetWNDCLASS() { return wc_; }

private:
	WinApp() = default;
	~WinApp() = default;

private: //メンバ変数
	HWND hwnd_;
	UINT windowStyle_;
	WNDCLASS wc_;

};

