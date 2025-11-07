#include "CWinInit.h"
#include "CGame.h"	//ゲームクラス.

//--------------------------------------
//　定数宣言
//--------------------------------------
const char APP_NAME[] = "2DAct";					//アプリ名
const char WND_TITLE[] = "初めてのアクションゲーム";	//ウィンドウタイトル

//スレッド関数.
DWORD WINAPI ThreadFunc(LPVOID vdParam)
{
	//変数宣言
	CGame* pGame = nullptr;	//ポインタの初期化は nullptr を使う.
	//ゲームクラスのインスタンス(実体)を生成.
	pGame = new CGame((GameWindow*)vdParam);//先頭アドレスをキャストして移す.

	DWORD frames = 0;		//フレーム数.
	DWORD beforeTime = 0;	//前の時間.
	char MsgFPS[128] = "";

	//時間の取得.
	beforeTime = timeGetTime();	//現在の時間を取得.

	//----------------------------------------------------------
	//	起動処理[WM_CREATE].
	//----------------------------------------------------------
	if (pGame->Create() == false)	return 0;

	//ウィンドウが閉じられるまで無限ループ.
	while (pGame->IsWindowClosed() == FALSE)
	{
		DWORD nowTime = 0;		//現在の時間.
		DWORD progress = 0;		//経過時間.
		DWORD idealTime = 0;	//理想時間.

		nowTime = timeGetTime();//現在の時間を取得.

		progress = nowTime - beforeTime;	//経過時間.

		//理想時間の算出.
		// ( 現在のフレーム数 × ( 1000 ÷ FPS値 ) ).
		idealTime = (DWORD)(frames * (1000.0F / pGame->GetFPS()));

		//----------------------------------------------------------
		//  ゲーム処理[WM_TIMER].
		//----------------------------------------------------------
		pGame->Update();

		//----------------------------------------------------------
		//	描画処理[WM_PAINT].
		//----------------------------------------------------------
		pGame->Draw();

		//FPSの表示.
		TextOut(pGame->GetScreenDC(),
			300, 0, MsgFPS, lstrlen(MsgFPS));

		//描画の時間待ち.
		if (idealTime > progress) {
			Sleep(idealTime - progress);	//時間待ち.
		}

		//再描画.
		InvalidateRect(pGame->GetWnd(), nullptr, FALSE);

		if (progress >= 1000)	//1秒経過.
		{
			wsprintf(MsgFPS, "FPS[%03d]", frames);
			beforeTime = nowTime;	//現在の時間に更新.
			frames = 0;
		}
		frames++;	//フレーム数UP.

		//Sleep(1);//画面ちらつき回避のため少し待たせる
	}

	//----------------------------------------------------------
	//	解放処理[WM_DESTROY].
	//----------------------------------------------------------
	pGame->Destroy();

	//不要になったので削除.
	if (pGame != nullptr) {
		delete pGame;
		pGame = nullptr;
	}

	//スレッド終了通知.
	ExitThread(0);

	return TRUE;
}


//ウィンドウ関数.
LRESULT CALLBACK WindowProc(
	HWND hWnd,		//ウィンドウハンドル.
	UINT uMsg,		//メッセージ.
	WPARAM wParam,	//メッセージに対応する情報.
	LPARAM lParam)	//メッセージに対応する情報.
{
	HDC hDC;			//デバイスコンテキスト.
	PAINTSTRUCT ps;		//描画構造体.

	//----------------------------------------------------------
	//	スレッド関連.
	//----------------------------------------------------------
	static GameWindow gameWnd;	//ゲームウィンドウ構造体.
	static HANDLE hThread;		//スレッドハンドル.
	DWORD dwID;		//スレッドID.
	HBITMAP hBmp;	//ビットマップハンドル.

	//メッセージ別の処理.
	switch (uMsg) {
	case WM_DESTROY:	//ウィンドウが破棄された時.

		//アプリケーションの終了をWindowsに通知する.
		PostQuitMessage(0);
		return 0;

	case WM_CREATE:		//ウィンドウが生成される時.
		//----------------------------------------------------------
		//	スレッドの設定.
		//----------------------------------------------------------
		//スレッドに渡す値を設定.
		gameWnd.hWnd = hWnd;		//ウィンドウハンドル.
		gameWnd.size.cx = WND_W;	//ウィンドウ幅.
		gameWnd.size.cy = WND_H;	//ウィンドウ高さ.
		gameWnd.dwFPS = FPS;		//FPS値(基準).

		//HDCの作成.
		hDC = GetDC(hWnd);	// DC(デバイスコンテキスト)を取得.

		//ビットマップハンドルを作成.
		hBmp = CreateCompatibleBitmap(
			hDC,
			gameWnd.size.cx,
			gameWnd.size.cy);

		//DCと互換性のあるDCを作成.
		gameWnd.hScreenDC = CreateCompatibleDC(hDC);

		//hScreenDCをビットマップ用として定義.
		SelectObject(gameWnd.hScreenDC, hBmp);

		//不要になったDCを解放.
		ReleaseDC(hWnd, hDC);

		//スレッドの作成と実行.
		hThread = CreateThread(
			nullptr,			//ハンドルを他のプロセスと共有する場合は指定.
			0,					//スタックサイズ(デフォルト:0).
			ThreadFunc,			//スレッド関数名.
			(LPVOID)&gameWnd,	//スレッドに渡す構造体.
			0,					//0:作成と同時に実行.
			&dwID);			//(out)スレッドID.

		return 0;

	case WM_KEYDOWN:
		//キー別の処理.
		switch (wParam) {
		case VK_ESCAPE:	//ESCキー.
			if (MessageBox(nullptr,
				"ゲームを終了しますか", "警告", MB_YESNO) == IDYES)
			{
				//ウィンドウを閉じることをWindowsに知らせる.
				PostMessage(gameWnd.hWnd, WM_CLOSE, 0, 0);
			}
			break;
		}
		return 0;

	case WM_CLOSE:
		//ウィンドウ閉じるフラグ有効.
		//※スレッド側で確認するためのフラグ.
		gameWnd.isWndClose = TRUE;

		DWORD result;
		while (1) {
			//スレッドが終わったかチェック.
			GetExitCodeThread(hThread, &result);
			//終わったらハンドルを閉じる.
			if (STILL_ACTIVE != result) {
				//closehandleで閉じる.
				CloseHandle(hThread);
				//ループを抜ける.
				break;
			}
		}
		//ウィンドウを破棄する.
		DestroyWindow(hWnd);
		return 0;

	case WM_PAINT:		//ウィンドウが更新された時.
		//描画開始.
		hDC = BeginPaint(hWnd, &ps);

		BitBlt(
			hDC,				//表示DC.
			0, 0,				//表示先x,y座標.
			gameWnd.size.cx,	//表示する幅.
			gameWnd.size.cy,	//表示する高さ.
			gameWnd.hScreenDC,	//バックバッファ(スレッド内で作成).
			0, 0,				//元画像のx,y.
			SRCCOPY);			//コピーする.

		//描画終了.
		EndPaint(hWnd, &ps);
		return 0;
	}

	//メインに返す情報.
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


//コンストラクタ
CWinInit::CWinInit()
{
}

//デストラクタ
CWinInit::~CWinInit()
{
}

//ウィンドウ作成関数
HRESULT CWinInit::MakeWindow(HWND* phWnd, HINSTANCE hInstance)
{

	//使用するCPUを指定する
	if (FAILED(SelectUseCPU(1)))	//CPU1を指定
	{
		return E_FAIL;
	}
	//ウィンドウクラスを登録
	if (FAILED(RegisterMyWindowClass(hInstance, APP_NAME)))
	{
		return E_FAIL;
	}

	//ウィンドウ領域の調整
	int WindowWidth = 0;
	int WindowHeight = 0;
	DWORD   dwStyle = WS_OVERLAPPEDWINDOW;
	if (FAILED(
		AdjustMyWindowRect(&WindowWidth, &WindowHeight, dwStyle, WND_W, WND_H ) ) )
	{
		return S_OK;
	}
	
	//ウィンドウの作成
	if (FAILED(
		CreateMyWindow(phWnd, hInstance, APP_NAME, dwStyle, WindowWidth, WindowHeight)))
	{
		return E_FAIL;
	}

	

	//ウィンドウの表示.
	// SW_SHOW : 表示する.
	// SW_HIDE : 隠す(非表示).
	ShowWindow(*phWnd, SW_SHOW);
	return S_OK;
}

//使用するCPUを指定する
HRESULT CWinInit::SelectUseCPU(
	DWORD ProcessAffinitMask)	//CPUを指定(2進数で指定)

{
	HANDLE hProcess;			//プロセスハンドル.
	DWORD errnum;				//エラーNo.
	BOOL ret;					//関数復帰値.

	//自身のプロセスのハンドルを取得.
	hProcess = GetCurrentProcess();

	ret = SetProcessAffinityMask(
		hProcess,
		ProcessAffinitMask);
	if (ret == FALSE)
	{
		errnum = GetLastError();	//エラー情報を取得.
		return E_FAIL;
	}
	return S_OK;
}

//ウィンドウクラスを登録
HRESULT CWinInit::RegisterMyWindowClass(
	HINSTANCE hInstance, const char* pApplicationName)
{
	WNDCLASS wc;	//ウィンドウクラス構造体.

	//--------------------------------------
	//  ウィンドウクラスの登録.
	//--------------------------------------
	//スタイルの登録.
	// CS_HREDRAW : 水平方向の再描画.
	// CS_VREDRAW : 垂直方向の再描画.
	wc.style = CS_HREDRAW | CS_VREDRAW;
	//ウィンドウ関数の登録.
	// DefWindowProc : デフォルトウィンドウ関数(後で自分で作る).
	wc.lpfnWndProc = WindowProc;
	//使わない(0固定).
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	//インスタンス番号の登録.
	wc.hInstance = hInstance;
	//アイコンの登録.
	// nullptr : デフォルト.
	wc.hIcon = nullptr;
	//カーソルの登録.
	// nullptr : デフォルト.
	wc.hCursor = nullptr;
	//ウィンドウの背景色.
	// LTGRAY_BRUSH : 明るい灰色.
	wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	//メニューの登録.
	// nullptr : デフォルト.
	wc.lpszMenuName = nullptr;
	//アプリケーション名.
	wc.lpszClassName = pApplicationName;

	//ウィンドウをWindowsに登録.
	if (RegisterClass(&wc) == 0) {
		//エラーメッセージの表示.
		// MB_OK : OKﾎﾞﾀﾝのみ.
		// MB_YESNO : はい・いいえ.
		// MB_OKCANCEL : OK・キャンセル.
		// MB_YESNOCANCEL : はい・いいえ・キャンセル.
		MessageBox(nullptr,
			"ウィンドウクラス登録失敗",
			"エラーメッセージ",
			MB_YESNOCANCEL);
		return E_FAIL;
	}
	return S_OK;
}

//ウィンドウ領域の調整
HRESULT CWinInit::AdjustMyWindowRect(
	int* pOutWidth, int* pOutHeight,	//(out)計算
	DWORD WindowStyle,					//ウィンドウ種別
	int WindowWidth,						//ウィンドウ幅
	int WindowHeight)					//ウィンドウ高さ
{
	RECT rect;			//矩形構造体.

	rect.top = 0;			//上.
	rect.left = 0;			//左.
	rect.right = WindowWidth;		//右.
	rect.bottom = WindowHeight;	//下.

	if (AdjustWindowRect(
		&rect,			//(in)画面サイズが入った矩形構造体.(out)計算結果.
		WindowStyle,		//ウィンドウスタイル.
		FALSE) == 0)	//メニューを持つかどうかの指定.
	{
		MessageBox(nullptr, "ウィンドウ領域の調整に失敗", "エラーメッセージ", MB_OK);
		return E_FAIL;
	}

	//ウィンドウ幅、高さを産出
	*pOutWidth = rect.right - rect.left;
	*pOutHeight = rect.bottom - rect.top;

	return S_OK;
}

//ウィンドウの作成
HRESULT CWinInit::CreateMyWindow(
	HWND* phWnd, HINSTANCE hInstance,
	const char* pApplicationName,		//アプリケーション名
	DWORD WindowStyle,					//ウィンドウ種別
	int WindowWidth,						//ウィンドウ幅
	int WindowHeight)					//ウィンドウ高さ
{
	*phWnd = CreateWindow(
		pApplicationName,		//アプリケーション名.
		WND_TITLE,				//ウィンドウタイトル.
		WindowStyle,			//ウィンドウ種別.
		100, 100,				//ウィンドウの表示位置(x,y).
		WindowWidth,			//ウィンドウの幅.
		WindowHeight,			//ウィンドウの高さ.
		nullptr,				//親ウィンドウのハンドル.
		nullptr,				//メニューの設定.
		hInstance,				//インスタンス番号.
		nullptr);				//ウィンドウ作成時に発生するイベントに渡すデータ.

	if (*phWnd == nullptr) {
		MessageBox(nullptr,
			"ウィンドウ作成失敗",
			"エラーメッセージ", MB_OK);
		return E_FAIL;
	}
	return S_OK;
}
