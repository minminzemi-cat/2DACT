#pragma once
#include<Windows.h>

#pragma comment( lib, "msimg32.lib" )	//指定色を透過して描画で使用する.
										//半透明の描画でも使用する.


/***************************************
*	イメージクラス
*/
class CImage
{
public:
	//コマ割り構造体
	struct FRAMESPLIT
	{
		int x;	//読み込みx座標
		int y;	//読み込みy座標
		int w;	//読み込み、表示の幅
		int h;	//読み込み、表示の高さ

		FRAMESPLIT(int xSrc = 0, int ySrc = 0, int wDest = 0, int hDest = 0)
			:x(xSrc), y(ySrc), w(wDest), h(hDest)
		{}
	};
public:
	//コンストラクタ(引数あり)
	CImage(HDC hScreenDC, HDC hMemDC , HDC hWorkDC);
	//デストラクタ
	~CImage();

	//画像の読み込み.
	bool LoadBmp( const char* fileName);

	//画像を表示する関数
	bool BBlt(
		int xDest, int yDest, int wDest, int hDest,
		int xSrc, int ySrc);

	//画像を透過して表示.
	bool TransBlt( int xDest, int yDest,int wDest, int hDest,
		int xSrc, int ySrc);

	//画像を半透明にして表示する関数.
	bool AlBlend(
		 int xDest, int yDest, int wDest, int hDest,
		 int xSrc, int ySrc, int Alpha);

	//画像を透過＋半透明にして表示する関数
	void TransAlBlend(
		int  xDest, int yDest, int wDest, int hDest,
		int xSrc, int ySrc, int Alpha);

private:
	// = delete[削除定義]と呼ばれる機能
	//指定された場合、その関数は呼び出せなくなる
	CImage() = delete;		//デフォルトコンストラクタ削除（使用禁止）
private:
	HBITMAP	m_hBmp;			//ビットマップ

	HDC		m_hScreenDC;	//スクリーンDC
	HDC		m_hMemDC;		//メモリDC
	HDC		m_hWorkDC;		//作業用DC
};