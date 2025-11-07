#include "CEnemy.h"

//コンストラクタ
CEnemy::CEnemy()
{
}

//デストラクタ
CEnemy::~CEnemy()
{
}

void CEnemy::Update()
{

}

void CEnemy::Draw(CCamera* pCamera)
{
	m_FrameSplit.w = 32;
	m_FrameSplit.h = 32;
	m_FrameSplit.x = 32 * 6;
	m_FrameSplit.y = 0;

	VECTOR2 DispPos = pCamera->CalcToPositionInCamera(&m_Position, &m_FrameSplit);

	//敵の表示
	m_pImg->TransAlBlend(
		DispPos.x,				//表示位置x座標 
		DispPos.y,				//表示位置y座標		
		m_FrameSplit.w,			//表示幅
		m_FrameSplit.h,			//表示高さ
		m_FrameSplit.x,			//元画像読込開始ｘ座標
		m_FrameSplit.y,			//元画像読込開始ｙ座標
		127);					//α値.
}