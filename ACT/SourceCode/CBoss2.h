#pragma once
#include"CCharacter.h"		//キャラクタークラス
#include <stdlib.h>			//乱数
/**********************************
* 		ボスクラス
*	***/

class CBoss2
	: public CCharacter  //キャラクタークラスを継承
{
public:
	//動作処理列挙型
	enum enBoss2Action
	{
		Wait = 0,	//待機

		Attack,     //攻撃

		Inazuma,  //いなずま

		dei,		//死亡

		Explosion,

		None = -1,	//未設定
	};
public:
	CBoss2();//コンストラクタ
	~CBoss2() override;//デストラクタ

	//キャラクター構造体
	struct CHARA
	{
		int x;
		int y;
		int state;
	};

	//初期化(リセット)関数.
	void InitializeGame();
	//動作関数
	void Update() override;//override:再定義前の関数が仮想関数かチェックできる
	//		仮想関数でない場合はエラーになる
//描画関数
	void Draw(CCamera* pCamera) override;

	void Two3SetImage(CImage* pImg, CImage* pImg2,CImage* pImg3)
	{
		m_pImg = pImg;
		m_pBoss2Img = pImg;
		m_pExplosion01_Img = pImg2;
		m_pInazumaImg = pImg3;
	}

	//アニメーション処理
	void Animation();

	//イナズマアニメーション
	void InazumaAnimation();

	//爆発アニメーション
	void ExplosionAnimation();

	CHARA m_Boss2;			//キャラクター設定

	DWORD nowTime = 0;		//現在の時間.

	int   Boss2HP = 10000;	//ボスのHP	

	bool	m_Atacking;		//攻撃中

private:
	int			m_GroundPos;	//地面の位置（定数でも可）

	//この画像を使うという宣言
	CImage* m_pBoss2Img;
	CImage* m_pExplosion01_Img;
	CImage* m_pInazumaImg;


	int  	m_Action;


};
