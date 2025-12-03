#pragma once
#include"CCharacter.h"		//キャラクタークラス


/**********************************
* 		ボスクラス
*	***/

class CBoss
	: public CCharacter  //キャラクタークラスを継承
{
public:
	//動作処理列挙型
	enum enBossAction
	{
		Wait = 0,	//待機
		
		Attack,     //攻撃

		dei,		//死亡
		
		Explosion,


		None = -1,	//未設定
	};
	public:
		CBoss();//コンストラクタ
		virtual~CBoss() override ;//デストラクタ

		//キャラクター構造体
		struct CHARA
		{
			int x;
			int y;
			int state;
		};
		
		//初期化(リセット)関数.
		virtual void InitializeGame();
		//動作関数
		virtual void Update() override;//override:再定義前の関数が仮想関数かチェックできる
								//		仮想関数でない場合はエラーになる
		//描画関数
		virtual void Draw(CCamera* pCamera) override;

		virtual void TwoSetImage(CImage* pImg, CImage* pImg2)
		{
			m_pImg = pImg;
			m_pBossImg = pImg;
			m_pExplosion01_Img= pImg2;
		}

		//アニメーション処理
		virtual void Animation();

		//爆発アニメーション
		virtual void ExplosionAnimation();
		
		//キャラクター
		CHARA m_Boss;

		DWORD nowTime = 0;		//現在の時間.

		int   BossHP = 1000;	//ボスのHP	

		
		bool	m_Atacking;		//攻撃中

private:
	int			m_GroundPos;	//地面の位置（定数でも可）

	//画像を読み込む
	CImage* m_pBossImg;
	CImage* m_pExplosion01_Img;

	//アクション中
	int  	m_Action;


};
