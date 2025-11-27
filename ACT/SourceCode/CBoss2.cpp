#include "CBoss2.h"
#include"Global.h"
#include<cmath>
#include"CSoundManager.h"	//サウンドマネージャークラス


CBoss2::CBoss2()
	: CCharacter()
	, m_GroundPos()
	, m_Atak1()
	, m_Atak2()
	, m_Boss2({ 576,320 })
	, m_Action(enBoss2Action::Wait)
	, m_Atacking(false)
	, m_pBoss2Img(m_pImg)
	, m_pExplosion01_Img(m_pImg2)
{
	m_FrameSplit.w = 576;
	m_FrameSplit.h = 320;
}

CBoss2::~CBoss2()
{
}

void CBoss2::Update()
{
	//毎フレーム左方向に動き続ける
	//m_Boss.x -= 1;

	//ボスのHPが０以上のときは生きている

	//ボスHPが０のときの処理（if文）を書いたら反対の処理を書いたほうがいい
	//そうしないとm_FrameSplit.x　に 　3680 - 167.273が代入されてしまう
	if (Boss2HP >= 0) {
		m_Action = enBoss2Action::Attack;

		//アタック中の処理
		if (m_Action == enBoss2Action::Attack)
		{
			//すべてのアニメーションを描画し終えたら終わり
 			if (( m_FrameSplit.x) / m_FrameSplit.w >= 15)
			{
				m_FrameSplit.x = 0; //攻撃アニメーション最初の位置に戻す
				m_FrameCounter = 0;
			}
		}
	}

	//ボスのHPが０以下になったら死んだということにする
	if (Boss2HP <= 0) {
		//死亡中の処理
		m_Action = enBoss2Action::Explosion;

		if (m_Action == enBoss2Action::Explosion)
		{
			//すべてのアニメーションを描画し終えたら終わり
			if ((m_FrameSplit.x) / m_FrameSplit.w > 11)
			{
				m_FrameSplit.x = 0;
				m_FrameCounter = 0;
			}
		}

		if (m_Action == enBoss2Action::dei)
		{
			//すべてのアニメーションを描画し終えたら終わり
			if ((800 - m_FrameSplit.x) / m_FrameSplit.w > 23)
			{
				m_FrameSplit.x = 800 - 160; //死亡アニメーション最初の位置に戻す
				m_FrameCounter = 0;
			}
		}
	}

	//動作状態による処理の場合分け
	switch (m_Action) {
	case enBoss2Action::Wait:
		break;
	case enBoss2Action::Attack:
		m_pImg = m_pBoss2Img;
		break;
	case enBoss2Action::dei:
		m_Action = true;
		break;
	case enBoss2Action::Explosion:
		m_pImg = m_pExplosion01_Img;
		break;
	case enBoss2Action::None:
		break;
	default:
		break;
	}
}

//描画関数
void CBoss2::Draw(CCamera* pCamera)
{
	//アニメーション処理
	Animation();

	//この本体はキャラクタークラスにある　親クラス
	//m_pImg = m_pBossImg;

	m_Position = { m_Boss2.x, m_Boss2.y };
	VECTOR2 DispPos2 = pCamera->CalcToPositionInCamera(&m_Position, &m_FrameSplit);

	m_pImg->TransBlt(
		DispPos2.x,		//表示位置x座標
		100,		//表示位置y座標.
		m_FrameSplit.w,		//画像幅
		m_FrameSplit.h,		//画像高さ.
		m_FrameSplit.x,		//元画像x座標.
		m_FrameSplit.y);	//元画像y座標.

}

void CBoss2::Animation()
{
	//常にカウンターを動かす
	m_FrameCounter++;

	//僕の画像はこの大きさでないとだめ
	m_FrameSplit.w = 576;
	m_FrameSplit.h = 320;
	m_FrameSplit.y = 0;

	switch (m_Action) {
	case enBoss2Action::Wait:
		m_FrameSplit.x = 12672 - 576;//待機画像（０コマ目）
		m_FrameSplit.y = 0;
		m_FrameCounter = 0;//待機アニメーションないので0にしておく
		break;
	case enBoss2Action::Attack:
		//m_FrameSplit.x = 0;
		m_FrameSplit.y = 1600 - (320*3);
		if (m_FrameCounter >= 15) {
			m_FrameSplit.x += m_FrameSplit.w;
			m_FrameCounter = 1;
		}
		break;
	case enBoss2Action::Explosion:
		ExplosionAnimation();

		break;
	case enBoss2Action::dei:
		/*
		m_FrameSplit.y = 800-160;
		if (m_FrameCounter >= 22) {
			m_FrameSplit.x -= m_FrameSplit.w;
			m_FrameSplit.y += m_FrameSplit.h;
			m_FrameCounter = 0;
		}
		*/
		;


		break;
	case enBoss2Action::None:		//未設定
		break;
	default:
		break;
	}
}

void  CBoss2::ExplosionAnimation()
{
	//画像のサイズを間違えると描画されない
	//ディエゴのおかげ
	m_FrameSplit.w = 192;
	m_FrameSplit.h = 192;
	m_FrameSplit.y = 0;
	
	if (m_FrameCounter >= 11) {
		m_FrameSplit.x += m_FrameSplit.w;

		m_FrameCounter = 1;
	}

}
