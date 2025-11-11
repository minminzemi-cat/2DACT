#pragma once
#include <Windows.h>
#include "Global.h"
#include"MyMacro.h"		//マクロ
#include "CImage.h"		//イメージクラス
#include "CPlayer.h"	//プレイヤークラス
#include"CEnemy.h"		//エネミークラス
#include"CStage.h"		//ステージクラス
#include "CCamera.h"	//カメラクラス



/**************************************************
*	ゲームクラス.
**/
class CGame
{
public:
	//---------------------------------------
	//	定数宣言.
	//---------------------------------------
	static const int C_SIZE = 64;	//キャラクターサイズ.
	static const int P_SPD = 4;		//プレイヤー移動速度.

	//---------------------------------------
	//	列挙型宣言.
	//---------------------------------------
	//キャラクター状態列挙型.
	enum enCharaState
	{
		Ready = 0,//準備完了.
		Living,		//生存中.
		Dying,		//死亡中.
		Dead,		//死んだ.
	};
	//シーン列挙型.
	enum enScene
	{
		Title,		//タイトル.
		GameMain,	//ゲーム中.
		GameOver,	//ゲームオーバー.
		Ending,		//エンディング.
	};

	//---------------------------------------
	//	構造体宣言.
	//---------------------------------------
	//キャラクター構造体.
	struct CHARA
	{
		int x;			//x座標.
		int y;			//y座標.
		int state;		//状態.
		int ExpAnimCnt;	//爆発アニメーションカウンタ.
	};

public:
	CGame();	//コンストラクタ.
	CGame( GameWindow* pGameWnd );//コンストラクタ(引数あり).
	~CGame();	//デストラクタ.

	//初期化(リセット)関数.
	void InitializeGame();
	//構築関数.
	bool Create();
	//破棄関数.
	void Destroy();
	//更新関数(キー入力や動作処理を行う).
	void Update();
	//描画関数(画像の表示処理を行う).
	void Draw();

	//ウィンドウを閉じているか確認.
	BOOL IsWindowClosed() const { return m_pGameWnd->isWndClose; }
	//FPSを取得.
	DWORD GetFPS() const { return m_pGameWnd->dwFPS; }
	//バックバッファを取得.
	HDC GetScreenDC() const { return m_pGameWnd->hScreenDC; }
	//ウィンドウハンドルを取得.
	HWND GetWnd() const { return m_pGameWnd->hWnd; }

private:
	GameWindow*	m_pGameWnd;		//ゲームウィンドウ構造体.
	HDC			m_hMemDC;		//メモリデバイスコンテキスト.
	HDC			m_hWorkDC;		//作業用DC
	HBITMAP		m_hWorkBmp;		//作業用BITMAP
	HFONT		m_hFont;		//フォントハンドル.
	CImage*		m_pBackImg;		//背景.
	CImage*		m_pCharaImg;		//キャラクター画像.
	CImage*		m_pEnemyImg;		//敵画像.
	CImage*		m_pPlayer_right_Img;	//プレイヤー(右向き)画像
	CImage*		m_pPlayer_left_Img;	//プレイヤー（左向き）画像
	CImage*		m_pPlayer_atk_Img;	//プレイヤー（アタック）画像

	CImage*		m_pStageImg;	//ステージ画像
	
	//-----自機-----.
	CHARA		m_Player;
	CPlayer*	m_pPlayer;		//プレイヤー
	//-----敵機-----.
	CEnemy* m_pEnemy;			//エネミー
	//-----ステージ-----.
	CStage* m_pStage;			//ステージ

	//-----カメラ------
	CCamera* m_pCamera;
};



//矩形同士の当たり判定.
bool CollisionDetection(
	int Ax, int Ay, int Aw, int Ah,		//矩形Aのx,y座標と幅高さ.
	int Bx, int By, int Bw, int Bh );	//矩形Bのx,y座標と幅高さ.