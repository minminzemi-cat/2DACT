#include "CGame.h"
#include <time.h>		//time関数を使用するために必要.
#include"CSoundManager.h"//サウンドマネージャークラス
#include <cmath>

//コンストラクタ.
CGame::CGame()
	: CGame( nullptr )
{
}

//コンストラクタ(引数あり).
CGame::CGame(GameWindow* pGameWnd)
	: m_pGameWnd(pGameWnd)
	, m_hMemDC(nullptr)
	, m_hWorkDC(nullptr)
	, m_hWorkBmp(nullptr)
	, m_hFont(nullptr)
	, m_pBackImg(nullptr)
	, m_pCharaImg(nullptr)
	, m_pEnemyImg(nullptr)
	, m_pBossImg(nullptr)
	, m_pExplosion01_Img(nullptr)
	, m_pPlayer_right_Img(nullptr)
	, m_pPlayer_left_Img(nullptr)
	, m_pPlayer_atk_Img(nullptr)
	, m_pStageImg(nullptr)
	, m_Player()
	, m_pPlayer(nullptr)
	, m_pEnemy(nullptr)
	, m_pBoss(nullptr)
	, m_pBoss2(nullptr)
	, m_pHPgeziImg(nullptr)
	, m_pStage		( nullptr )
	, m_Scene(enScene::Title)
	, m_pTitleImg	( nullptr )
	, m_pGameOverImg(nullptr)
	, m_pKuriaImg	( nullptr )
	, m_pCamera		( nullptr )
	, m_Muteki_Flag(false)
	, m_TimeConter(0.0f)
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

	//ボスの初期配置.
	m_pBoss->m_Boss.x = (WND_W / 2) - (C_SIZE / 2);
	m_pBoss->m_Boss.y = WND_H - (C_SIZE + 16);	//補正:画面下からキャラ1体分+16上の位置.
	m_pBoss->m_Boss.state = enCharaState::Living;	//生存中.
	m_pBoss->enBossAction
	

	m_pBoss2->m_Boss2.x = (WND_W / 2) - (C_SIZE / 2);
	m_pBoss2->m_Boss2.y = WND_H - (C_SIZE + 16);	//補正:画面下からキャラ1体分+16上の位置.
	m_pBoss2->m_Boss2.state = enCharaState::Living;	//生存中.

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
	//ボス画像のインスタンス生成
	m_pBossImg = new CImage(m_pGameWnd->hScreenDC, m_hMemDC, m_hWorkDC);

	//ボス2画像のインスタンス生成
	m_pBoss2Img = new CImage(m_pGameWnd->hScreenDC, m_hMemDC, m_hWorkDC);

	//爆発画像のインスタンス生成
	m_pExplosion01_Img = new CImage(m_pGameWnd->hScreenDC, m_hMemDC, m_hWorkDC);

	//プレイヤー（右向いている）画像のインスタンス生成
	m_pPlayer_right_Img= new CImage(m_pGameWnd->hScreenDC, m_hMemDC, m_hWorkDC);
	//プレイヤー（左向いている）画像のインスタンス生成
	m_pPlayer_left_Img= new CImage(m_pGameWnd->hScreenDC, m_hMemDC, m_hWorkDC);
	//プレイヤー(アタック)画像のインスタンス生成
	m_pPlayer_atk_Img = new CImage(m_pGameWnd->hScreenDC, m_hMemDC, m_hWorkDC);

	//HPゲージの画像のインスタンス生成
	m_pHPgeziImg	=		new CImage(m_pGameWnd->hScreenDC, m_hMemDC, m_hWorkDC);

	//タイトル画像のインスタンス生成
	m_pTitleImg =		new CImage(m_pGameWnd->hScreenDC, m_hMemDC, m_hWorkDC);
	//ゲームオーバー画像のインスタンス生成
	m_pGameOverImg =	new CImage(m_pGameWnd->hScreenDC, m_hMemDC, m_hWorkDC);
	//ゲームクリア画像のインスタンス生成
	m_pKuriaImg =		new CImage(m_pGameWnd->hScreenDC, m_hMemDC, m_hWorkDC);

	//ステージ画像のインスタンス生成
	m_pStageImg =		new CImage(m_pGameWnd->hScreenDC, m_hMemDC, m_hWorkDC);
	


	//背景の読み込み.
	if( m_pBackImg->LoadBmp("Data\\Image\\bg.bmp" )		== false ) return false;
	//キャラクターの読み込み.
	if( m_pCharaImg->LoadBmp("Data\\BMP\\chara.bmp" )	== false ) return false;
	//敵の読み込み.
	if (m_pEnemyImg->LoadBmp("Data\\Image\\enemy_lite.bmp") == false) return false;
	
	//ボスの読み込み.
	if (m_pBossImg->LoadBmp("Data\\Image\\Boss.bmp") == false) return false;

	//ボス2の読み込み.
	if (m_pBoss2Img->LoadBmp("Data\\Image\\Boss2.bmp") == false) return false;

	//爆発の読み込み
	if (m_pExplosion01_Img->LoadBmp("Data\\Image\\Explosion.bmp") == false) return false;

	////プレイヤー(右向いている)の読み込み.
	if (m_pPlayer_right_Img->LoadBmp("Data\\Image\\migi.bmp") == false) return false;
	////プレイヤー（左向いている）の読み込み.
	if (m_pPlayer_left_Img->LoadBmp("Data\\Image\\hidari.bmp") == false) return false;
	////プレイヤー（アタック）の読み込み.
	if (m_pPlayer_atk_Img->LoadBmp("Data\\Image\\atk.bmp") == false) return false;

	//HPゲージの読み込み
	if (m_pHPgeziImg->LoadBmp("Data\\Image\\PlayerHP01.bmp") == false) return false;
	
	//ステージの読み込み.
	if (m_pStageImg->LoadBmp("Data\\Image\\SwitchPlace_lite.bmp") == false) return false;


	//タイトルの読み込み.
	if (m_pTitleImg->LoadBmp("Data\\Image\\title2.bmp") == false) return false;

	//ゲームオーバーの読み込み.
	if (m_pGameOverImg->LoadBmp("Data\\Image\\GameOver.bmp") == false) return false;

	//エンディングの読み込み.
	if (m_pKuriaImg->LoadBmp("Data\\Image\\gamekuria.bmp") == false) return false;

	//プレイヤーのインスタンス生成
	m_pPlayer = new CPlayer();
	//画像の設定
	m_pPlayer->ThreeSetImage(m_pPlayer_right_Img, m_pPlayer_left_Img, m_pPlayer_atk_Img);


	//エネミーのインスタンス生成
	m_pEnemy = new CEnemy();
	//画像の設定
	m_pEnemy->SetImage(m_pEnemyImg);

	//ボスのインスタンス生成
	m_pBoss = new CBoss();
	//画像の設定
	m_pBoss->TwoSetImage(m_pBossImg, m_pExplosion01_Img);
	
	//ボスのインスタンス生成
	m_pBoss2 = new CBoss2();
	//画像の設定
	m_pBoss2->Two2SetImage(m_pBoss2Img, m_pExplosion01_Img);

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

	SAFE_DELETE(m_pBoss);

	SAFE_DELETE(m_pBoss2);

	SAFE_DELETE(m_pPlayer);


	//BITMAPの解放.
	SAFE_DELETE(m_pKuriaImg);
	SAFE_DELETE(m_pGameOverImg);
	SAFE_DELETE(m_pTitleImg);
	SAFE_DELETE(m_pStageImg);
	SAFE_DELETE(m_pHPgeziImg);
	SAFE_DELETE(m_pPlayer_right_Img);
	SAFE_DELETE(m_pPlayer_left_Img);
	SAFE_DELETE(m_pPlayer_atk_Img);
	SAFE_DELETE(m_pExplosion01_Img);
	SAFE_DELETE(m_pBoss2Img);
	SAFE_DELETE(m_pBossImg);
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

	//シーンごとの処理
	switch (m_Scene) {
		case enScene::Title://タイトル
			if (GetAsyncKeyState(VK_RETURN) & 0x0001)//Enterキーが押されたら
			{
				//F1キー.
				if (GetAsyncKeyState(VK_F1) & 0x0001) {
					//ウィンドウを閉じる通知を送る.
					PostMessage(m_pGameWnd->hWnd, WM_CLOSE, 0, 0);
				}
				m_Scene = enScene::GameMain;

			
			}
			break;

		case enScene::GameMain:
			
				

				//プレイヤー動作
				m_pPlayer->Update();

				//エネミー動作
				m_pEnemy->Update();

				//ボス２動作
				m_pBoss2->Update();

				//ボス動作
				m_pBoss->Update();

				//ステージ動作
				m_pStage->Update();

				//カメラ位置をプレイヤーにそろえる
				//※カメラ位置を揃えるタイミグはすべての動作が完了し最終的な座標が確定した後
				m_pCamera->SePosition(m_pPlayer->GetPosition());

				//F1キー.
				if (GetAsyncKeyState(VK_F1) & 0x0001) {
					//ウィンドウを閉じる通知を送る.
					PostMessage(m_pGameWnd->hWnd, WM_CLOSE, 0, 0);
				}

				//*****************************************************************
				//プレイヤーがアタック状態のときの当たり判定
				//-------------ボス------------
				if (m_pPlayer->m_Atacking == true) {
					if (CircleCollisionDetection(m_pPlayer->GetPosition().x, m_pPlayer->GetPosition().y, C_SIZE,
						m_pBoss->m_Boss.x, m_pBoss->m_Boss.y, C_SIZE))
					{
						m_pBoss->BossHP = m_pBoss->BossHP - 100;
					}


					/*if (m_pBoss->BossHP == 0)
					{
 						m_Scene = enScene::Kuria;
					}*/
				}

				//---------------ボス２----------------
				if (m_pPlayer->m_Atacking == true) {
					if (CircleCollisionDetection(m_pPlayer->GetPosition().x, m_pPlayer->GetPosition().y, C_SIZE,
						m_pBoss2->m_Boss2.x, m_pBoss2->m_Boss2.y, C_SIZE))
					{
						m_pBoss2->Boss2HP = m_pBoss2->Boss2HP - 100;

						if (m_pBoss2->Boss2HP == 0)
						{
							m_Scene = enScene::Kuria;
						}
					}

				}

				
				
				//ボスが攻撃中のプレイヤーとの当たり判定
				//m_pBoss->m_Boss.x + C_SIZE/2　の　C_SIZE/2を加えることでボスが攻撃して剣の頂点にしか当たり判定がなかった奴が
				//ボス自身に当たり判定をつけることができるようになった
				if (m_pBoss->Attack) {
					if (CircleCollisionDetection(m_pBoss->m_Boss.x + C_SIZE / 2, m_pBoss->m_Boss.y + C_SIZE / 2, C_SIZE/2 ,
						m_pPlayer->GetPosition().x, m_pPlayer->GetPosition().y, C_SIZE /2
						 ))
					{
						m_Muteki_Flag = true;
						if (m_TimeConter > 1500)
						{
							m_Muteki_Flag = false;
							m_TimeConter = 0;
						}
						//ここにプレイヤーのHPゲージが減る処理を書く
						m_pPlayer->m_PlayerHP =m_pPlayer->m_PlayerHP- 1;
					}

				}

				if (m_pBoss2->Attack) {
					if (CircleCollisionDetection(m_pBoss2->m_Boss2.x + C_SIZE / 2, m_pBoss2->m_Boss2.y + C_SIZE / 2, C_SIZE / 2,
						m_pPlayer->GetPosition().x, m_pPlayer->GetPosition().y, C_SIZE / 2
					))
					{
						m_Muteki_Flag = true;
						if (m_TimeConter > 1500)
						{
							m_Muteki_Flag = false;
							m_TimeConter = 0;
						}
						//ここにプレイヤーのHPゲージが減る処理を書く
						m_pPlayer->m_PlayerHP = m_pPlayer->m_PlayerHP - 1;
					}
				}


				if (m_pPlayer->m_PlayerHP == 0)
				{
					m_Scene = enScene::GameOver;
				}

				//*****************************************************************
				
				
				
				//自機が画面外にでないようにする  なんかできなかった
				if (m_Player.x < 0) {
					m_Player.x = 0;		//左側でない
				}
				if (m_Player.x > 640) {
					m_Player.x = 640;	//右側でない
				}
				
		break;
		case enScene::Kuria:
			if (GetAsyncKeyState(VK_RETURN) & 0x0001)
			{

				//タイトルへ
				m_Scene = enScene::Title;
			}

			break;
		case enScene::GameOver://ゲームオーバー
			//F1キー.
			if (GetAsyncKeyState(VK_F1) & 0x0001) {
				//ウィンドウを閉じる通知を送る.
				PostMessage(m_pGameWnd->hWnd, WM_CLOSE, 0, 0);
			}
			if (GetAsyncKeyState(VK_RETURN) & 0x0001)
			{
				
				//タイトルへ
				m_Scene = enScene::Title;
			}
			break;
	}
}

//描画関数(画像の表示処理を行う).
void CGame::Draw()
{
	switch(m_Scene){
	case enScene::Title://タイトル
		//タイトル描画
		m_pTitleImg->BBlt(
			0,					//描画させたいｘ座標
			0,					//描画させたいｙ座標
			WND_W,				//描画するサイズｘ（横）
			WND_H,				//描画するサイズｙ　縦
			0,					//元画像のｘ
			0					//元画像のｙ
		);

		break;
	case enScene::GameMain://ゲーム中


		//ステージ描画
		m_pStage->Draw( m_pCamera );

		//プレイヤー描画
		m_pPlayer->Draw( m_pCamera );

		//ボスを描画
		m_pBoss->Draw(m_pCamera);

		//ボスのHPが少なくなってきたら
		if (m_pBoss->BossHP <= 10)
		{
			//ボス２を描画
			m_pBoss2->Draw(m_pCamera);
		}
		//エネミー描画
		m_pEnemy->Draw( m_pCamera);

		//ボスのHPが0のとき爆発
		if (m_pBoss->BossHP == 0)
		{
			m_pBoss->ExplosionAnimation();
		}


		//++++++++++++++++++++++++++++++++++++++++++++++++++++++
		//		プレイヤーのHPゲージ

		/*if (m_pPlayer->m_PlayerHP == 100)
		{*/
			//画像の表示させたい場所と画像の座標を求める
			m_pHPgeziImg->TransBlt(
				10,					//表示位置x座標
				10,					//表示位置y座標.
				143,				//画像幅
				50,					//画像高さ.
				//ディエゴのおかげ
				715-(m_pPlayer->m_PlayerHP / 20) * 143,					//元画像x座標.・・・座標0,0から画像幅、高さ分を取り出しますよ
				0);					//元画像y座標.
			//意味合い
			//143,50はHP画像の幅と高さでo,oは開始位置　
			//開始位置０，０から幅143、高さ50の画像を取り出しますよ



			//僕の勘違い
			//		m_pPlayer->m_PlayerHP == 75にすると
			//		74とかになると100になったり0になったりするようになっていた
			



		//}
		//else if (m_pPlayer->m_PlayerHP >= 75)
		//{
		//	//画像の表示させたい場所と画像の座標を求める
		//	m_pHPgeziImg->TransBlt(
		//		10,					//表示位置x座標
		//		10,					//表示位置y座標.
		//		143,				//画像幅
		//		50,					//画像高さ.
		//		//取り出し開始位置
		//		143,				//元画像x座標.・・・座標0,0から画像幅、高さ分を取り出しますよ
		//		0);					//元画像y座標.
		//}

		//else if (m_pPlayer->m_PlayerHP >= 50)
		//{
		//	//画像の表示させたい場所と画像の座標を求める
		//	m_pHPgeziImg->TransBlt(
		//		10,					//表示位置x座標
		//		10,					//表示位置y座標.
		//		143,				//画像幅
		//		50,					//画像高さ.
		//		//取り出し開始位置
		//		143*2,				//元画像x座標.・・・座標0,0から画像幅、高さ分を取り出しますよ 286
		//		0);					//元画像y座標.
		//}
		//else if (m_pPlayer->m_PlayerHP >= 30)
		//{
		//	//画像の表示させたい場所と画像の座標を求める
		//	m_pHPgeziImg->TransBlt(
		//		10,					//表示位置x座標
		//		10,					//表示位置y座標.
		//		143,				//画像幅
		//		50,					//画像高さ.
		//		//取り出し開始位置
		//		143*3,				//元画像x座標.・・・座標0,0から画像幅、高さ分を取り出しますよ  429,
		//		0);					//元画像y座標.
		//}
		//else {
		//	//画像の表示させたい場所と画像の座標を求める
		//	m_pHPgeziImg->TransBlt(
		//		10,					//表示位置x座標
		//		10,					//表示位置y座標.
		//		143,				//画像幅
		//		50,					//画像高さ.
		//		//取り出し開始位置
		//		143*4,				//元画像x座標.・・・座標0,0から画像幅、高さ分を取り出しますよ
		//		0);					//元画像y座標.
		//}

		//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

		break;
	case enScene::GameOver://ゲームオーバー
		//ゲームオーバー描画
		m_pGameOverImg->BBlt(
			0,
			0,
			WND_W,
			WND_H,
			0,
			0
		);
		
		break;
	case enScene::Kuria://エンディング

		//エンディング描画
		m_pKuriaImg->BBlt(
			0,
			0,
			WND_W,
			WND_H,
			0,
			0
		);
		

		break;
	}

		
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

//円と円の当たり判定
bool CircleCollisionDetection(float Ax, float Ay, float Ar, float Bx, float By, float Br)
{
	float dx = Ax - Bx;
	float dy = Ay - By;
	//sqrftは平方根
	//#include<cmath>が必要らしい
	float distance = sqrtf(dx * dx + dy * dy);

	//命中したとき
	if (distance < Ar + Br) {
		return true;
	}
	//外れた時
	return false;
}