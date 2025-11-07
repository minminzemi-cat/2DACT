#pragma once
#include "MyMath.h"			//VECTOR2構造体で必要
#include "CImage.h"			//イメージクラス

/******************************************
*		カメラクラス
**/
class CCamera
{
public:
	CCamera();		//コンストラクタ
	~CCamera();		//デストラクタ

	//ステージ上の座標をカメラ上の座標に変換
	VECTOR2 CalcToPositionInCamera(const VECTOR2* pPos, const CImage::FRAMESPLIT* pFS);
	//ステージの表示座標を算出
	VECTOR2 CalcToStagePosition();

	//ステージ幅を設定
	void SetStageWidth(int width) { m_StageWidth = width; }
	//カメラ中央に表示したい対象のステージ上の座標を設定
	void SePosition(const VECTOR2& pos) { m_Position = pos; }

private:
	//移動範囲
	void MoveRange();

private:
	const VECTOR2   m_Center;		//中央位置調整用

	VECTOR2			m_Position;		//位置（中央基準の座標）
	int				m_StageWidth;	//ステージ幅

};