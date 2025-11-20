#include "CBoss.h"
#include"Global.h"
#include<cmath>
#include"CSoundManager.h"	//サウンドマネージャークラス


CBoss::CBoss()
	:m_GroundPos()
	, m_Atak1()
	, m_Atak2()
	, m_Boss({500,300})
	, m_Action(enBossAction::Wait)
	,m_Atacking(false)
{
}

CBoss::~CBoss()
{
}

void CBoss::Update()
{
	//毎フレーム左方向に動き続ける
	//m_Boss.x -= 1;


	//アタック中の処理
	if (m_Action == enBossAction::Attack)
	{
		//すべてのアニメーションを描画し終えたら終わり
		if ((3680 - m_FrameSplit.x) / m_FrameSplit.w > 12)
		{
			m_FrameSplit.x = 3680 - 167.273; //攻撃アニメーション最初の位置に戻す
			m_FrameCounter = 0;
		}
	}

	if (BossHP == 0) {
		m_Action = enBossAction::dei;

		//死亡中の処理
		if (m_Action == enBossAction::dei)
		{
			//すべてのアニメーションを描画し終えたら終わり
			if ((800 - m_FrameSplit.x) / m_FrameSplit.w > 23)
			{
				m_FrameSplit.x = 800 - 160; //死亡アニメーション最初の位置に戻す
				m_FrameCounter = 0;
			}
		}
	}
	if (nowTime / 10 == 0) {
		m_Action = enBossAction::Attack;
	}
	
	//動作状態による処理の場合分け
	switch (m_Action) {
	case enBossAction::Wait:
		break;
	case enBossAction::Attack:
		
		break;
	case enBossAction::dei:	
		m_Action = true;
		break;
	case enBossAction::None:
		break;
	default:
		break;
	}
}

//描画関数
void CBoss::Draw(CCamera* pCamera)
{
	//アニメーション処理
	Animation();

	//この本体はキャラクタークラスにある　親クラス
	m_Position = { m_Boss.x, m_Boss.y };
	VECTOR2 DispPos1 = pCamera->CalcToPositionInCamera(&m_Position, &m_FrameSplit);

	m_pImg->TransBlt(
		DispPos1.x,		//表示位置x座標
		DispPos1.y,		//表示位置y座標.
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
	m_FrameSplit.w = 170;
	m_FrameSplit.h = 200;
	m_FrameSplit.y = 0;

	switch (m_Action) {
	case enBossAction::Wait:
		m_FrameSplit.x = 3680-167;//待機画像（０コマ目）
		m_FrameSplit.y = 0;
		m_FrameCounter = 0;//待機アニメーションないので0にしておく
		break;
	case enBossAction::Attack:
		//m_FrameSplit.x = 3680 - 160;//待機画像（０コマ目）
		m_FrameSplit.y = 480-160;
		if (m_FrameCounter >= 12) {
			m_FrameSplit.x -= m_FrameSplit.w;
			m_FrameCounter = 0;
		}
		break;
	case enBossAction::dei:
		m_FrameSplit.y = 800-160;
		if (m_FrameCounter >= 22) {
			m_FrameSplit.x -= m_FrameSplit.w;
			m_FrameSplit.y += m_FrameSplit.h;
			m_FrameCounter = 0;
		}
		break;
	case enBossAction::None:		//未設定
		break;
	default:
		break;
	}
}


