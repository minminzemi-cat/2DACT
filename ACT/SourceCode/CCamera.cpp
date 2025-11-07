#include "CCamera.h"
#include"Global.h"

//コンストラクタ
CCamera::CCamera()
	:m_Center		( WND_W / 2 ,WND_H / 2) //constなので以降は値の変更不可
	,m_Position		()
	,m_StageWidth	()
{
}	

//デストラクタ
CCamera::~CCamera()
{
}

//ステージ上の座標をカメラ上の座標に変換
VECTOR2 CCamera::CalcToPositionInCamera(
	const VECTOR2* pPos, const CImage::FRAMESPLIT* pFS)
{
	VECTOR2 pos(0, 0);

	//カメラ内（ウィンドウ内）でのプレイヤー位置
	pos.x = pPos->x - (pFS->w / 2) + m_Center.x - m_Position.x;
	pos.y = pPos->y;

	return pos;
}

//ステージの表示座標を算出
VECTOR2 CCamera::CalcToStagePosition()
{
	VECTOR2 pos(0, 0);

	//移動範囲
	MoveRange();
	

	//ステージ表示位置
	//ステージの表示位置は左側基準なので、カメラ中央値をカメラ位置にプラスする
	pos.x = m_Center.x - m_Position.x;

	return pos;
}

//移動範囲
void CCamera::MoveRange()
{
	//カメラ移動制御（ステージ左側）
	if (m_Position.x < m_Center.x) {
		m_Position.x = m_Center.x;
	}

	//カメラ移動制御（ステージ右側）
	if (m_Position.x > m_StageWidth - m_Center.x) {
		m_Position.x = m_StageWidth - m_Center.x;
	}
}
