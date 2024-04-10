#include "WinApp.h"
#include "Externals/imgui/imgui.h"
#include "Externals/imgui/imgui_impl_dx12.h"
#include "Externals/imgui/imgui_impl_win32.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lParam);

WinApp* WinApp::GetInstance() {
	static WinApp instance;
	return &instance;
}

// ウィンドウプロシーシャ
LRESULT WinApp::WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {

	if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam)) {
		return true;
	}

	// メッセージに応じてゲーム固有の処理を行う
	switch (msg) {
		// ウィンドウが破壊された
	case WM_DESTROY:
		//　OSに対して、アプリの終了を伝える
		PostQuitMessage(0);
		return 0;
	}

	// 標準のメッセージ処理を行う
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

const wchar_t WinApp::className[] = L"CG2";
void WinApp::CreateGameWindow(const wchar_t* title, UINT windowStyle, int32_t windowWidth, int32_t windowHeight) {

	//COMの初期化
	CoInitializeEx(0, COINIT_MULTITHREADED);

	//メンバ変数の初期化
	windowStyle_ = windowStyle;
	//windowStyle_ = WS_OVERLAPPEDWINDOW;

	// ウィンドウポロージャ 
	wc_.lpfnWndProc = WindowProc;
	// ウィンドウクラス名
	wc_.lpszClassName = className;
	// インスタンスハンドル
	wc_.hInstance = GetModuleHandle(nullptr);
	// カーソル
	wc_.hCursor = LoadCursor(nullptr, IDC_ARROW);

	// ウィンドウクラスを登録
	RegisterClass(&wc_);

	// ウィンドウサイズを表す構造体にクライアント領域を入れる
	RECT wrc = { 0,0,windowWidth,windowHeight };

	// クライアント領域を元に実際のサイズにwrcを変更してもらう
	AdjustWindowRect(&wrc, windowStyle_, false);

	// ウィンドウの生成
	hwnd_ = CreateWindow(
		wc_.lpszClassName,		//利用するクラス名
		title,					//タイトルバーの文字(何でも良い)
		windowStyle_,	//よく見るウィンドウスタイル
		CW_USEDEFAULT,			//表示X座標(Windowsに任せる)
		CW_USEDEFAULT,			//表示Y座標(WindowsOSに任せる)
		wrc.right - wrc.left,	//ウィンドウ横幅
		wrc.bottom - wrc.top,	//ウィンドウ縦幅
		nullptr,				//親ウィンドウハンドル
		nullptr,				//メニューハンドル
		wc_.hInstance,			//インスタンスハンドル
		nullptr
	);				//オプション

	// ウィンドウを表示する
	ShowWindow(hwnd_, SW_SHOW);

};

void WinApp::DiscardingWindow() {

	//Comの終了処理
	CoUninitialize();

	//ウィンドウクラスの登録解除
	UnregisterClass(wc_.lpszClassName, wc_.hInstance);
}

bool WinApp::ProcessMessage() {
	MSG msg;

	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (msg.message == WM_QUIT) {
		return true;
	}

	return false;
}
