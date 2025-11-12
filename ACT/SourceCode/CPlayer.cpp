#include "CPlayer.h"
#include"Global.h"
#include"CSoundManager.h"	//サウンドマネージャークラス

CPlayer::CPlayer()//コンストラクタ
	:m_GroundPos	(WND_H - 64)
	,m_OldPosition	()
	,m_Action		( enAction::Wait )
	,m_Jumping		( false)
	,m_JumpAcc		( 0.0f)		//値を変えるとジャンプの高さが変わる
	,m_JumpPower	( 24.0f )	//値を変えると落下速度がかわる
	,m_Gravity		( 0.8f )
{
	m_Position = VECTOR2(0, m_GroundPos);
	m_MoveSpeed = 4;

	m_LookingRight = true;
}

CPlayer::~CPlayer()//デストラクタ
{
}

//動作関数
void CPlayer::Update()
{
	//移動前の位置を退避
	m_OldPosition = m_Position;

	//舞フレーム最初は待機状態に戻す
	m_Action = enAction::Wait;
	
	KeyInput();

	//ジャンプ中の処理
	/*if (m_Jumping == true)
	{
		//移動量　　　　＝　ジャンプ力　　ー　加速度
		m_Position.y -= static_cast<int>(m_JumpPower - m_JumpAcc);
		m_JumpAcc += m_Gravity;//加速度を重量分増加.

		//地面より下になった
		if (m_Position.y >= m_GroundPos)
		{
			m_Position.y = m_GroundPos; //地面とそろえる
			m_Jumping = false;			//ジャンプ中を解除

			//ジャンプの音を鳴らす
			CSoundManager::PlaySE(CSoundManager::SE_Jump);
		}
	}*/

	//動作状態による処理の場合分け
	switch (m_Action) {
	case enAction::Wait:
		break;
	case enAction::MoveLeft:
		m_Position.x -= m_MoveSpeed;
		m_LookingRight = false;//右向き無効
		break;
	case enAction::MoveRight:
		m_Position.x += m_MoveSpeed;
		m_LookingRight = true;//右向き有効
		break;
	case enAction::None:
		break;
	default:
		break;
	}

	//右向き判定
	if (m_LookingRight == true)
	{
		m_FrameSplit.y += m_FrameSplit.h;
	}
}

//描画関数
void CPlayer::Draw( CCamera* pCamera )
{
	//アニメーション処理
	Animation();

	VECTOR2 DispPos = pCamera->CalcToPositionInCamera(&m_Position, &m_FrameSplit);

	m_pImg->TransBlt(
		DispPos.x,		//表示位置x座標
		DispPos.y,		//表示位置y座標.
		m_FrameSplit.w,		//画像幅
		m_FrameSplit.h,		//画像高さ.
		m_FrameSplit.x,		//元画像x座標.
		m_FrameSplit.y);	//元画像y座標.
}

//操作処理
void CPlayer::KeyInput()
{
	//ジャンプ
	/*if (GetAsyncKeyState('Z') & 0x8000)
	{
		if (m_Jumping == false)
		{
			m_Jumping = true;	//ジャンプ中にする
			m_JumpAcc = 0.0f;	//加速度を初期化
		}
	}*/

	//←.
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)//0x0001[遅延連射], 0x8000[即連射].
	{
		m_Action = enAction::MoveLeft;
	}
	//→.
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)//0x0001[遅延連射], 0x8000[即連射].
	{
		m_Action = enAction::MoveRight;
	}
}

//アニメーション処理
void CPlayer::Animation()
{
	//常にカウンターを動かす
	m_FrameCounter++;

	//僕の画像はこの大きさでないとだめ
	m_FrameSplit.w = 128;
	m_FrameSplit.h = 64;
	m_FrameSplit.y = 0;

	switch (m_Action) {
	case enAction::Wait:		//待機
		m_FrameSplit.x = 0;//待機画像（０コマ目）
		m_FrameCounter = 0;//待機アニメーションないので0にしておく
		break;
	case enAction::MoveLeft:	//左移動
	case enAction::MoveRight:	//右移動
		//6フレーム事にアニメーション切り替え
		if (m_FrameCounter >= 6) {
			m_FrameSplit.x += m_FrameSplit.w;
			m_FrameCounter = 0;
		}

		//歩きアニメーション最大コマ数（１コマ目）を超えると最初（0コマ目）に戻す
		if (m_FrameSplit.x / m_FrameSplit.w > 18)
		{
			m_FrameSplit.x = 0;
		}
		break;
	
	case enAction::None:		//未設定
		break;
	default:
		break;
	}

	//ジャンプ中
	/*if (m_Jumping == true)
	{
		//現在の位置が移動前の位置よりも大きい（画面上では下）になった
		if (m_Position.y > m_OldPosition.y)
		{
			m_FrameSplit.x = m_FrameSplit.w * 4;
		}
		else
		{
			m_FrameSplit.x = m_FrameSplit.w * 3;//ジャンプ画像
		}
	}*/
	
	//右向き判定
	if (m_LookingRight == true)
	{
		m_FrameSplit.y += m_FrameSplit.h;

	}
}
