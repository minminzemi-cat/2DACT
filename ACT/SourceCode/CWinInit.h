#pragma once
#include"Global.h"


/***********************************
*	ウィンドウ作成クラス
**/
class CWinInit
{
public://public:外部からアクセス可能
	CWinInit();		//コンストラクタ
	~CWinInit();	//デストラクタ

	//ウィンドウ作成関数
	HRESULT MakeWindow(HWND* phWnd, HINSTANCE hInstance);

	private://private:外部からアクセス不可能.
	//使用するCPUを指定する
		HRESULT SelectUseCPU(DWORD ProcessAffinitMask);
	//ウィンドウクラスを登録
		HRESULT RegisterMyWindowClass(
			HINSTANCE hInstance, const char* pApplicationName);
	//ウィンドウ領域の調整
		HRESULT AdjustMyWindowRect(
			int* pOutWidth, int* pOutHeight,
			DWORD WindowStyle, int WindowWidth, int WindowHeight);
	//ウィンドウの作成
		HRESULT CreateMyWindow(HWND* phWnd, HINSTANCE hInstance,
			const char* pApplicationName, DWORD WindowStyle,
			int WindowWidth, int WindowHeight);
};
