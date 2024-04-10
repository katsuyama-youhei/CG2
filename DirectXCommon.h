#pragma once
#include "DirectXGame/Base/WinApp/WinApp.h"
#include "DirectXGame/Base/DebugSytem/DebugLog.h"
#include "Externals/DirectXTex/d3dx12.h"
#include <format>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <dxgidebug.h>
#include <dxcapi.h>
#include <cassert>
#include <compare>
#include <chrono>
#include <thread>

using namespace Microsoft::WRL;

class DirectXCommon
{
public:
	static DirectXCommon* GetInstance();

public:

	void Initialize();

	/// <summary>
	/// 描画前処理
	/// </summary>
	void PreDraw();

	/// <summary>
	/// 描画後処理
	/// </summary>
	void PostDraw();

	/// <summary>
	/// 画面のクリア
	/// </summary>
	void ClearRenderTarget();

	/// <summary>
	/// 深度バッファのクリア
	/// </summary>
	void ClearDepthStencilBuffer();

	/// <summary>
	/// コマンドのキックから次のコマンドリストの準備
	/// </summary>
	void TransferCommandList();

	/// <summary>
	/// Dxcのコンパイルシェーダー
	/// </summary>
	/// <param name="filePath"></param>
	/// <param name="profile"></param>
	/// <returns></returns>
	ComPtr<IDxcBlob> CompilerShader(const std::wstring& filePath, const wchar_t* profile);

	/// <summary>
	/// ディスクリプターヒープの生成
	/// </summary>
	/// <param name="heapType"></param>
	/// <param name="numDescriptors"></param>
	/// <param name="shaderVisible"></param>
	/// <returns></returns>
	ComPtr<ID3D12DescriptorHeap> CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE heapType, UINT numDescriptors, bool shaderVisible);

	/// <summary>
	/// 深度情報を収納するためのリソース確保関数
	/// </summary>
	/// <returns></returns>
	ComPtr<ID3D12Resource> CreateDepthStencilTextureResource();

public:

	inline ID3D12Device* GetDevice() { return device_.Get(); }

	inline ID3D12GraphicsCommandList* GetCommandList() { return commandList_.Get(); }

	inline IDXGISwapChain4* GetSwapShain() { return swapChain_.Get(); }

	inline ID3D12DescriptorHeap* GetRtvDescriptorHeap() { return rtvDescriptorHeap_.Get(); }

	inline ID3D12DescriptorHeap* GetSrvDescriptorHeap() { return srvDescriptorHeap_.Get(); }

	inline ID3D12DescriptorHeap* GetDsvDescriptorHeap() { return dsvDescriptorHeap_.Get(); }

	inline D3D12_RENDER_TARGET_VIEW_DESC GetRtvDesc() { return rtvDesc_; }

	inline D3D12_DEPTH_STENCIL_VIEW_DESC GetDsvDesc() { return dsvDesc_; }

	CD3DX12_CPU_DESCRIPTOR_HANDLE GetRtvHandle();

	D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandle(int index);

	D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDescriptorHandle(int index);

private:
	DirectXCommon() = default;
	~DirectXCommon() = default;

	/// <summary>
	/// DXGIデバイス初期化
	/// </summary>
	void InitializeDxgiDevice();

	/// <summary>
	/// コマンド関連初期化
	/// </summary>
	void InitializeCommand();

	/// <summary>
	/// スワップチェーンの生成
	/// </summary>
	void InitializeSwapChain();

	/// <summary>
	/// RTV用のディスクリプターヒープの生成
	/// </summary>
	void CreateRenderTargetView();

	/// <summary>
	/// SRV用ディスクリプターヒープの生成
	/// </summary>
	void CreateShaderResourceView();

	/// <summary>
	/// 深度バッファ生成
	/// </summary>
	void CreateDepthStencilView();

	/// <summary>
	/// フェンス生成
	/// </summary>
	void CreateFence();

	/// <summary>
	/// DXCの初期化
	/// </summary>
	void InitializeDXC();
	
	void InitializeFixFPS();

	void UpdateFixFPS();

private: //メンバ変数
	ComPtr<IDXGIFactory7> dxgiFactory_ = nullptr;
	ComPtr<ID3D12Device> device_ = nullptr;
	ComPtr<ID3D12CommandQueue> commandQueue_ = nullptr;
	ComPtr<ID3D12CommandAllocator> commandAllocator_ = nullptr;
	ComPtr<ID3D12GraphicsCommandList> commandList_ = nullptr;
	ComPtr<IDXGISwapChain4> swapChain_ = nullptr;
	ComPtr<ID3D12DescriptorHeap> rtvDescriptorHeap_ = nullptr;
	ComPtr<ID3D12DescriptorHeap> srvDescriptorHeap_ = nullptr;
	ComPtr<ID3D12DescriptorHeap> dsvDescriptorHeap_ = nullptr;
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc_;
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc_;
	std::vector<ComPtr<ID3D12Resource>> backBuffers;
	ComPtr<ID3D12Fence> fence_ = nullptr;
	ComPtr<IDxcUtils> dxcUtils_ = nullptr;
	ComPtr<IDxcCompiler3> dxcCompiler_ = nullptr;
	ComPtr<IDxcIncludeHandler> includeHandler_ = nullptr;
	ComPtr<ID3D12Resource> depthStencilResource_ = nullptr;
	uint64_t fenceValue_ = 0;
	std::chrono::steady_clock::time_point reference_;

};

