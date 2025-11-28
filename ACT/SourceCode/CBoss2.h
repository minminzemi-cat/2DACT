#pragma once
#include"CCharacter.h"		//キャラクタークラス


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

	//動作関数
	void Update() override;//override:再定義前の関数が仮想関数かチェックできる
	//		仮想関数でない場合はエラーになる
//描画関数
	void Draw(CCamera* pCamera) override;

	void Two2SetImage(CImage* pImg, CImage* pImg2)
	{
		m_pImg = pImg;
		m_pBoss2Img = pImg;
		m_pExplosion01_Img = pImg2;
	}

	//アニメーション処理
	void Animation();

	//爆発アニメーション
	void ExplosionAnimation();

	CHARA m_Boss2;

	DWORD nowTime = 0;		//現在の時間.

	int   Boss2HP = 1000;	//ボスのHP	

	bool	m_Atacking;		//攻撃中

private:
	int			m_GroundPos;	//地面の位置（定数でも可）

	CImage* m_pBoss2Img;
	CImage* m_pExplosion01_Img;



	int  	m_Action;


};
