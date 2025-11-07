#pragma once
#include"CGameObject.h"		//ゲームオブジェクトクラス
#include"CImage.h"			//イメージクラス
#include"Global.h"
#include"MyMath.h"			//VECTOR2構造体で必要

/**********************************
*		ステージクラス
***/

class CStage 
	:public CGameObject	//ゲームオブジェクトクラスを継承
{
public:
	static const int DATA_X_MAX = 20;
	static const int DATA_Y_MAX = 15;
public:
	CStage();
	~CStage();
	//動作関数
	void Update() override ;
	//描画関数
	void Draw( CCamera* pCamera ) override ;

	//画像を設定する
	void SetImage(CImage* pImg) { m_pImg = pImg; }
	//ステージの幅を習得※データ読込完了のみ習得設定
	int GetWidth() const { return m_Chip.w * m_MapMax.x; }

	//マップデータ読み込み
	bool LoadData(const char* fileName);
	//マップデータ解放
	void ReleaseData();


public:
	CImage*				 m_pImg;		//画像（外部で読み込んだデータを入れる）
	CImage::FRAMESPLIT   m_Chip;		//マップチップ画像１つ値の幅、高さ

	int   m_Data[DATA_Y_MAX][DATA_X_MAX];					//マップデータ	

	VECTOR2				m_MapMax;		//マップデータの縦と横の最大数
	int**				m_ppData;		//マップデータ（ポインタのポインタorダブルポインタ）

	VECTOR2				m_Position;		//ステージ位置

	
};