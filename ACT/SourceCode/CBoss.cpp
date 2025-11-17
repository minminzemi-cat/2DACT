#include "CBoss.h"
#include"Global.h"
#include"CSoundManager.h"	//サウンドマネージャークラス


CBoss::CBoss()
	:m_GroundPos()
	, m_Atak1()
	, m_Atak2()
	, m_Boss()
{
}

CBoss::~CBoss()
{
}

void CBoss::Update()
{

}

void CBoss::Draw(CCamera* pCamera)
{
	m_pImg->TransBlt(
		m_Boss.x,		//表示位置x座標
		m_Boss.y,		//表示位置y座標.
		m_FrameSplit.w,		//画像幅
		m_FrameSplit.h,		//画像高さ.
		m_FrameSplit.x,		//元画像x座標.
		m_FrameSplit.y);	//元画像y座標.
}

void CBoss::AttackPattern1()
{
}

void CBoss::AttackPattern2()
{
}
