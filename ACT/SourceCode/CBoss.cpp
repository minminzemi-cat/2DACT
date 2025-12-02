#include "CBoss.h"
#include"Global.h"
#include<cmath>
#include"CSoundManager.h"	//サウンドマネージャークラス


CBoss::CBoss()
	:m_GroundPos()
	, m_Boss({500,340})
	, m_Action(enBossAction::Wait)
	,m_Atacking(false)
	,m_pBossImg(m_pImg)
	,m_pExplosion01_Img(m_pImg2)
	,m_Explosion_Flag(false)
{
}

CBoss::~CBoss()
{
}

//初期化関数
void CBoss::InitializeGame()
{
	int   BossHP = 1000;	//ボスのHP

}

//更新関数
void CBoss::Update()
{
	//毎フレーム左方向に動き続ける
	//m_Boss.x -= 1;

	//ボスのHPが０以上のときは生きている

	//ボスHPが０のときの処理（if文）を書いたら反対の処理を書いたほうがいい
	//そうしないとm_FrameSplit.x　に 　3680 - 167.273が代入されてしまう
	if (BossHP >= 0) {
		m_Action = enBossAction::Attack;

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
	}

	//前回のactionを保存
	//これで爆発アニメーション開始時を検出できる
	int prevAction = m_Action;

	//ボスのHPが０以下になったら死んだということにする
	if (BossHP <= 0) {

		//爆発画像のためのm_FrameSplit.xを設定する
		//今、ボス画像のm_FrameSplit.xが設定されているから爆発が表示されない

		//死亡中の処理
		if (m_Action != enBossAction::dei)
		{
			m_Action = enBossAction::Explosion;
		}

		if (m_Action == enBossAction::Explosion)
		{
			//今prevActionには爆発のアクションが入っており、それを爆発と等しくないとき、爆発を描画する
			//ボスのHPが０なので、ずっと爆発処理をするになっていたが、これにより止まる
			if (prevAction != enBossAction::Explosion)
			{
				//爆発の大きさ
				m_FrameSplit.w = 192;
				m_FrameSplit.h = 192;
				m_FrameSplit.y = 0;
				m_FrameSplit.x = 0;
			}
			//m_Action = enBossAction::dei;
			
				//すべてのアニメーションを描画し終えたら終わり
				if ((m_FrameSplit.x) / m_FrameSplit.w > 11)
				{
					
					//画像の描画を開始するｘ座標
					m_FrameSplit.x = 0;
					m_FrameCounter = 0;
	
					//描画し終わったら死んでる状態に
					m_Action = enBossAction::dei;
					
				}
		}
		//死んでいる状態時は何もしない
		if (m_Action == enBossAction::dei)
		{
		}
	}
	
	//動作状態による処理の場合分け
	switch (m_Action) {
	case enBossAction::Wait:
		break;

	//アタックのとき、アタックの画像を入れる
	case enBossAction::Attack:
		m_pImg = m_pBossImg;
		break;
	case enBossAction::dei:
		
		break;
	//爆発のとき、爆発の画像を入れる
	case enBossAction::Explosion:
		m_pImg = m_pExplosion01_Img;
		break;
	//何も設定しない
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
	//m_pImg = m_pBossImg;

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
	m_FrameSplit.w = 160;
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
			m_FrameCounter = 1;
		}
		break;

	//爆発のとき、爆発アニメーション再生
	case enBossAction::Explosion:
		ExplosionAnimation();

		break;
	//死んだとき、何もしない
	case enBossAction::dei:
		break;
	case enBossAction::None:		//未設定
		break;
	default:
		break;
	}
}

//爆発アニメーション関数
void  CBoss::ExplosionAnimation()
{

	//画像のサイズを間違えると描画されない
	//ディエゴのおかげ
	m_FrameSplit.w = 192;
	m_FrameSplit.h = 192;
	m_FrameSplit.y = 0;
	//僕の画像はこの大きさでないとだめ
	
	
		//爆発の描画
		if (m_FrameCounter >= 11) {

			//　　　0       +=     192
			m_FrameSplit.x += m_FrameSplit.w;

			m_FrameCounter = 1;

		}
	
}
