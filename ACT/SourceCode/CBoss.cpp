#include "CBoss.h"
#include"Global.h"
#include"CSoundManager.h"	//サウンドマネージャークラス


CBoss::CBoss()
	:m_GroundPos()
	, m_Atak1()
	, m_Atak2()
	, m_Boss()
	, m_Action(enBossAction::Wait)
	,m_Atacking(false)
{
}

CBoss::~CBoss()
{
}

void CBoss::Update()
{

	m_Boss.x = 500;
	m_Boss.y = 0;

	m_Action = enBossAction::Wait;

	//アタック中の処理
	if (m_Atacking == true)
	{
		//すべてのアニメーションを描画し終えたら終わり
		if (m_FrameSplit.x / m_FrameSplit.w > 12)
		{
			m_Atacking = false; //攻撃中解除
			m_Action = enBossAction::Wait;
		}


	}
}

void CBoss::Draw(CCamera* pCamera)
{
	//アニメーション処理
	Animation();

	m_pImg->TransBlt(
		m_Boss.x,		//表示位置x座標
		m_Boss.y,		//表示位置y座標.
		m_FrameSplit.w,		//画像幅
		m_FrameSplit.h,		//画像高さ.
		m_FrameSplit.x,		//元画像x座標.
		m_FrameSplit.y);	//元画像y座標.


	
}

void CBoss::Animation()
{
	//常にカウンターを動かす
	m_FrameCounter++;

	//僕の画像はこの大きさでないとだめ
	m_FrameSplit.w = 128;
	m_FrameSplit.h = 64;
	m_FrameSplit.y = 0;

	switch (m_Action) {
	case enBossAction::Wait:
		m_FrameSplit.x = 1840;//待機画像（０コマ目）
		m_FrameSplit.y = 0;
		m_FrameCounter = 0;//待機アニメーションないので0にしておく
		break;
	case enBossAction::Attack:
		m_FrameSplit.y = 240;
		if (m_FrameCounter >= 12) {
			m_FrameSplit.x -= m_FrameSplit.w;
			m_FrameCounter = 0;
		}
		break;
	case enBossAction::dei:
		m_FrameSplit.y = 400;
		if (m_FrameCounter >= 22) {
			m_FrameSplit.x -= m_FrameSplit.w;
			m_FrameCounter = 0;
		}
		break;
	case enBossAction::None:		//未設定
		break;
	default:
		break;
	}
}

