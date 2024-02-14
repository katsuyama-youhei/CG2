#include "WinApp.h"

const wchar_t kWindowTitle[] = { L"CG2" };

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	
	WinApp::CreateWindowView(kWindowTitle);

	MSG msg{};
	// ウィンドウのxボタンが押されるまでループ
	while (msg.message != WM_QUIT) {
		// Windowにメッセージが来てたら最優先で処理させる
		if (PeekMessage(&msg,NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			// ゲームの処理
		}
	}
	 
	
	// 出力ウィンドウへの文字出力
	OutputDebugStringA("Hello,DirectX!\n");
	
	return 0;
}