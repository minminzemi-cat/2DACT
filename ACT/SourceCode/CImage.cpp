#include "CImage.h"

//透過色(緑を指定).
const UINT TRANS_COLOR = RGB(0x00, 0xFF, 0x00);

//コンストラクタ
CImage::CImage( HDC hScreenDC, HDC hMemDC, HDC hWorkDC)
	:	m_hBmp		(nullptr)
	,	m_hScreenDC	(hScreenDC)
	,	m_hMemDC	(hMemDC)
	,	m_hWorkDC   ( hWorkDC )
{
}

//デストラクタ
CImage::~CImage()
{
	DeleteObject(m_hBmp);

	//外部で作られたものなのでnullptrで初期化
	m_hWorkDC = nullptr;
	m_hMemDC = nullptr;
	m_hScreenDC = nullptr;
}

//画像の読み込み.
bool CImage::LoadBmp(const char* fileName)
{
	m_hBmp = (HBITMAP)LoadImage(
		nullptr,			//インスタンス.
		fileName,			//ファイル名(パス含む).
		IMAGE_BITMAP,		//ビットマップ.
		0, 0,				//読み込む座標.
		LR_LOADFROMFILE);	//ファイルから読み込む.

	if (m_hBmp == nullptr) {
		MessageBox(nullptr,
			fileName, "画像読み込み失敗", MB_OK);
		return false;
	}
	return true;
}

//画像を表示する関数
bool CImage::BBlt(int xDest, int yDest, int wDest,
	int hDest, int xSrc, int ySrc)
{
	SelectObject(m_hMemDC, m_hBmp);

	if (BitBlt(
		m_hScreenDC,		//デバイスコンテキスト
		xDest, yDest,		//表示位置x,y座標
		wDest, hDest,		//表示幅、高さ
		m_hMemDC,			//読み込み元DC
		xSrc, ySrc,			//読み込み元画像x,y座標
		SRCCOPY) == FALSE)	//コピーする
	{
		return false;
	}
	return false;
}

//画像を透過して表示.
bool CImage::TransBlt(
	int xDest, int yDest,int wDest, int hDest,
	int xSrc, int ySrc)
{
	SelectObject(m_hMemDC, m_hBmp);

	if (TransparentBlt(
		m_hScreenDC,			//表	示先(実はディスプレイ).
		xDest, yDest,			//表示位置x,y座標.
		wDest, hDest,			//表示幅、高さ.
		m_hMemDC,				//画像が設定されたメモリDC.
		xSrc, ySrc,				//元画像の取り出し開始x,y座標.
		wDest, hDest,			//元画像の取り出し幅、高さ.
		TRANS_COLOR )			//透過色(緑を指定).
		== FALSE)
	{
		return false;
	}
	return true;
}

//画像を半透明にして表示する関数.
bool CImage::AlBlend(
	 int xDest, int yDest, int wDest, int hDest,
	 int xSrc, int ySrc, 
	int Alpha)//a値（0:完全透明、　255:不透明）
{
	//BLENDFUNCTION構造体.
	BLENDFUNCTION blendfunc = { AC_SRC_OVER, 0, (BYTE)Alpha, 0 };

	SelectObject(m_hMemDC, m_hBmp);

	//半透明にする画像の表示.
	if (AlphaBlend(
		m_hScreenDC,		//デバイスコンテキスト.
		xDest, yDest,	//表示位置x,y座標.
		wDest, hDest,	//画像幅、高さ.
		m_hMemDC,			//読み込み元DC.
		xSrc, ySrc,		//読み込み元画像x,y座標.
		wDest, hDest,	//読み込み元画像幅,高さ.
		blendfunc))	//BLENDFUNCTION構造体.
	{
		return true;
	}
	return false;
}

//画像を透過＋半透明にして表示する関数
void CImage::TransAlBlend(int xDest, int yDest, 
	int wDest, int hDest, 
	int xSrc, int ySrc, int Alpha)
{
	
	SelectObject(m_hMemDC,m_hBmp);
	//スクリーン→作業用DCへ
	BitBlt(
		m_hWorkDC,		//出力先：作業用DC
		0, 0,			//出力先：x,yは０で固定
		wDest, hDest,
		m_hScreenDC,	//読込元：スクリーン
		xDest,yDest,	//スクリーン上で表示したいx,y座標
		SRCCOPY);
	//メモリ→作業用DCへ
	TransparentBlt(
		m_hWorkDC,	//出力先：作業用DC
		0, 0,		//出力先：x,y座標は０で固定
		wDest, hDest,
		m_hMemDC,	//読込元：メモリ
		xSrc,ySrc,
		wDest, hDest,
		TRANS_COLOR);
	//作業用DC→スクリーンへ
	BLENDFUNCTION blendfunc = { AC_SRC_OVER , 0 , (BYTE)Alpha, 0 };
	AlphaBlend(
		m_hScreenDC,	//出力先：スクリーン
		xDest, yDest,	//スクリーン上で表示したいx,y座標
		wDest, hDest,
		m_hWorkDC,				//読込元：作業用DC
		0, 0,					//出力先：x,yは０で固定
		wDest, hDest,
		blendfunc);



}
