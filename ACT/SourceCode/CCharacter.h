#pragma once
#include"CGameObject.h"		//ゲームオブジェクトクラス
#include "CImage.h"		//イメージクラス
#include"MyMath.h"			//数学クラス

 /*****************************
*		キャラクタークラス
**/
class CCharacter
	:public CGameObject		//ゲームオブジェクトクラスを継承
{
public:
	CCharacter();
	//仮想関数：関数の戻り値の方の前に　virtual(バーチャル)をつける
	//		継承させる可能性のあるクラスのデストラクタは仮想関数にすること
	virtual ~CCharacter();

	//動作関数
	virtual void Update() override{}
	//描画関数
	virtual void Draw(CCamera* pCamera) override {}

	//画像を設定する
	void SetImage(CImage* pImg) { m_pImg = pImg; }

	//画像を３つ設定する関数
	void ThreeSetImage(CImage* pImg, CImage* pImg2, CImage* pImg3) { m_pImg = pImg; }

	//位置情報を習得する
	VECTOR2 GetPosition() const { return m_Position; }
	//１コマの画像情報を習得する
	CImage::FRAMESPLIT GetFrameSplit() const { return m_FrameSplit; }

protected:	//protected:外部からアクセス不可能。派生クラスでアクセス可能
	CImage* m_pImg;		//画像（外部で読み込んだデータを入れる）
	CImage* m_pImg2;
	CImage* m_pImg3;

	VECTOR2		m_Position;	//位置（座標）
	int			m_MoveSpeed;//移動速度

	CImage::FRAMESPLIT m_FrameSplit;	//1コマの画像情報
	int				   m_FrameCounter;	//アニメーション制御用カウンタ
	bool			   m_LookingRight;	//右向き判定
	bool			   m_LookingLeft;	//ボス用　左向き判定
};
