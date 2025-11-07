#pragma once
#include <Windows.h>

//---------------------------------------
//	定数宣言.
//---------------------------------------
const int FPS = 60;		//FPS(基準).
const int WND_W = 640;	//ウィンドウの幅.
const int WND_H = 480;	//ウィンドウの高さ.

//---------------------------------------
//	構造体.
//---------------------------------------
typedef struct _GameWindow
{
	HWND	hWnd;		//ウィンドウハンドル.
	HDC		hScreenDC;	//バックバッファ.
	SIZE	size;		//サイズ.
	DWORD	dwFPS;		//FPS( Frame Per Second: フレーム / 秒 ).
	BOOL	isWndClose;	//ウィンドウ閉じてるか確認用.
} GameWindow;