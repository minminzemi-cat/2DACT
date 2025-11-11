#include "CGame.h"
#include <time.h>		//time関数を使用するために必要.
#include"CSoundManager.h"//サウンドマネージャークラス


//コンストラクタ.
CGame::CGame()
	: CGame( nullptr )
{
}

//コンストラクタ(引数あり).
CGame::CGame( GameWindow* pGameWnd )
	: m_pGameWnd	( pGameWnd )
	, m_hMemDC		( nullptr )
	, m_hWorkDC		( nullptr )
	, m_hWorkBmp	( nullptr )
	, m_hFont		( nullptr )
	, m_pBackImg	( nullptr )
	, m_pCharaImg	( nullptr )
	, m_pEnemyImg	( nullptr )
	, m_pPlayer_right_Img  ( nullptr )
	, m_pPlayer_left_Img	(nullptr)
	, m_pPlayer_atk_Img		(nullptr)
	, m_pStageImg	( nullptr )
	, m_Player		()
	, m_pPlayer		( nullptr )
	, m_pEnemy		( nullptr )
	, m_pStage		( nullptr )
	, m_pCamera		( nullptr )
{
}

//デストラクタ.
CGame::~CGame()
{
}

//初期化(リセット)関数.
void CGame::InitializeGame()
{
	//自機初期配置.
	m_Player.x = ( WND_W / 2 ) - ( C_SIZE / 2 );
	m_Player.y = WND_H - ( C_SIZE + 16 );	//補正:画面下からキャラ1体分+16上の位置.
	m_Player.state = enCharaState::Living;	//生存中.
	m_Player.ExpAnimCnt = 0;


}

//構築関数.
bool CGame::Create()
{
	//乱数の初期化.
	srand( (unsigned int)time( nullptr ) );

	//メモリDCの作成.
	m_hMemDC = CreateCompatibleDC( nullptr );

	//作業用DCの作成
	m_hWorkDC = CreateCompatibleDC(m_pGameWnd->hScreenDC);//作業用DCの作成
	m_hWorkBmp = CreateCompatibleBitmap(m_pGameWnd->hScreenDC, WND_W, WND_H);//作業用BITMAPの作成
	SelectObject(m_hWorkDC, m_hWorkBmp);			//DCとBITMAPを紐づけ

	//フォントの作成.
	m_hFont = CreateFont(
		60,	//文字高さ.
		20,	//文字幅.
		0,	//角度.
		0,	//ベースライン角度.
		FW_REGULAR,	//太さ(太字:FW_BOLD,通常:FW_REGULAR).
		FALSE,		//斜体(TRUE:有効).
		FALSE,		//下線(TRUE:有効).
		FALSE,		//打ち消し線(TRUE:有効).
		SHIFTJIS_CHARSET,	//文字セット.
		OUT_DEFAULT_PRECIS,	//出力精度.
		CLIP_DEFAULT_PRECIS,//クリッピング精度.
		DEFAULT_QUALITY,	//出力品質.
		VARIABLE_PITCH | FF_ROMAN,	//可変ピッチとフォントファミリ.
		"HG創英角ﾎﾟｯﾌﾟ体" );		//書体(nullptr:現在使われている書体).

	//背景画像のインスタンス生成
	m_pBackImg = new CImage(m_pGameWnd->hScreenDC, m_hMemDC, m_hWorkDC);
	//キャラクター画像のインスタンス生成
	m_pCharaImg = new CImage(m_pGameWnd->hScreenDC, m_hMemDC, m_hWorkDC);
	//敵画像のインスタンス生成
	m_pEnemyImg = new CImage(m_pGameWnd->hScreenDC, m_hMemDC, m_hWorkDC);
	//プレイヤー画像のインスタンス生成
	m_pPlayer_right_Img = new CImage(m_pGameWnd->hScreenDC, m_hMemDC, m_hWorkDC);
	//プレイヤー画像のインスタンス生成
	m_pPlayer_left_Img = new CImage(m_pGameWnd->hScreenDC, m_hMemDC, m_hWorkDC);
	//プレイヤー画像のインスタンス生成
	m_pPlayer_atk_Img = new CImage(m_pGameWnd->hScreenDC, m_hMemDC, m_hWorkDC);
	//ステージ画像のインスタンス生成
	m_pStageImg = new CImage(m_pGameWnd->hScreenDC, m_hMemDC, m_hWorkDC);
	
	//背景の読み込み.
	if( m_pBackImg->LoadBmp("Data\\Image\\bg.bmp" )		== false ) return false;
	//キャラクターの読み込み.
	if( m_pCharaImg->LoadBmp("Data\\BMP\\chara.bmp" )	== false ) return false;
	//敵の読み込み.
	if (m_pEnemyImg->LoadBmp("Data\\Image\\enemy_lite.bmp") == false) return false;
	//プレイヤー(右向いている)の読み込み.
	if (m_pPlayer_right_Img->LoadBmp("Data\\Image\\migi_1.bmp") == false) return false;
	//プレイヤー（左向いている）の読み込み.
	if (m_pPlayer_left_Img->LoadBmp("Data\\Image\\hidari_1.bmp") == false) return false;
	//プレイヤー（アタック）の読み込み.
	if (m_pPlayer_atk_Img->LoadBmp("Data\\Image\\atk.bmp") == false) return false;
	//ステージの読み込み.
	if (m_pStageImg->LoadBmp("Data\\Image\\SwitchPlace_lite.bmp") == false) return false;


	//プレイヤーのインスタンス生成
	m_pPlayer = new CPlayer();
	//画像の設定
	m_pPlayer->SetImage(m_pPlayer_right_Img);

	//プレイヤーのインスタンス生成
	m_pPlayer = new CPlayer();
	//画像の設定
	m_pPlayer->SetImage(m_pPlayer_left_Img);

	//プレイヤーのインスタンス生成
	m_pPlayer = new CPlayer();
	//画像の設定
	m_pPlayer->SetImage(m_pPlayer_atk_Img);


	//エネミーのインスタンス生成
	m_pEnemy = new CEnemy();
	//画像の設定
	m_pEnemy->SetImage(m_pEnemyImg);

	//ステージのインスタンス生成
	m_pStage = new CStage();
	//画像の設定
	m_pStage->SetImage(m_pStageImg);
	//マップデータの読み込み
	if(m_pStage->LoadData("Data\\MapData\\Map01.csv") == false) return false;

	//カメラのインスタンス生成
	m_pCamera = new CCamera();
	m_pCamera->SetStageWidth(m_pStage->GetWidth());

	//サウンドデータを読み込む
	if (CSoundManager::GetInstance()->Load(m_pGameWnd->hWnd) == false) return false;

	return true;
}

//破棄関数.
void CGame::Destroy()
{
	SAFE_DELETE(m_pCamera);

	SAFE_DELETE(m_pStage);

	SAFE_DELETE(m_pEnemy);

	SAFE_DELETE(m_pPlayer);


	//BITMAPの解放.
	SAFE_DELETE(m_pStageImg);
	SAFE_DELETE(m_pPlayer_right_Img);
	SAFE_DELETE(m_pPlayer_left_Img);
	SAFE_DELETE(m_pPlayer_atk_Img);
	SAFE_DELETE(m_pEnemyImg);
	SAFE_DELETE(m_pCharaImg);
	SAFE_DELETE(m_pBackImg);

	//フォントの解放.
	DeleteObject( m_hFont );

	//作業用BITMAPの解放
	DeleteObject(m_hWorkBmp);
	//作業用DCの解放
	DeleteDC(m_hWorkDC);

	//メモリDCの解放.
	DeleteDC( m_hMemDC );
}

//更新関数(キー入力や動作処理を行う).
void CGame::Update()
{	
		//BGM_Bonusをループ再生
	CSoundManager::PlayLoop(CSoundManager::BGM_Bonus);

		//F1キー.
		if( GetAsyncKeyState( VK_F1 ) & 0x0001 ) {
			//ウィンドウを閉じる通知を送る.
			PostMessage( m_pGameWnd->hWnd, WM_CLOSE, 0, 0 );
		}

		//プレイヤー動作
		m_pPlayer->Update();

		//エネミー動作
		m_pEnemy->Update();

		//ステージ動作
		m_pStage->Update();

		//カメラ位置をプレイヤーにそろえる
		//※カメラ位置を揃えるタイミグはすべての動作が完了し最終的な座標が確定した後
		m_pCamera->SePosition(m_pPlayer->GetPosition());
		
}

//描画関数(画像の表示処理を行う).
void CGame::Draw()
{
		
		//ステージ描画
		m_pStage->Draw( m_pCamera );

		//プレイヤー描画
		m_pPlayer->Draw( m_pCamera );

		//エネミー描画
		m_pEnemy->Draw( m_pCamera);

		
		/*SelectObject(m_hMemDC, m_pEnemyImg->GetBmp());
		//スクリーン→作業用DCへ
		BitBlt(
			m_hWorkDC,
			0, 0,
			32, 32,
			m_pGameWnd->hScreenDC,//読込元：スクリーン
			x,
			y,
			SRCCOPY);
		//メモリ→作業用DCへ
		TransparentBlt(
		    m_hWorkDC,	//出力先：作業用DC
			0, 0,
			32, 32,
			m_hMemDC,	//読込元：メモリ
			32 * 6,
			0,
			32 , 32,
			RGB(0x00, 0xFF, 0X00) );
		//作業用DC→スクリーンへ
		BLENDFUNCTION blendfunc = { AC_SRC_OVER , 0 , 127, 0 };
		AlphaBlend(
			m_pGameWnd->hScreenDC,	//出力先：スクリーン
			x, y,
			32, 32,
			m_hWorkDC,				//読込元：作業用DC
			0, 0,
			32, 32,
			blendfunc);
			*/
}



//矩形同士の当たり判定.
bool CollisionDetection(
	int Ax, int Ay, int Aw, int Ah,	//矩形Aのx,y座標と幅高さ.
	int Bx, int By, int Bw, int Bh)	//矩形Bのx,y座標と幅高さ.
{
	//自機の弾と敵機の当たり判定.
	if( ( Ax <= Bx + Bw ) && ( Bx <= Ax + Aw ) &&
		( Ay <= By + Bh ) && ( By <= Ay + Ah ) )
	{
		//命中した時.
		return true;
	}
	//外れた時.
	return false;
}
