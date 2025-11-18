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

		Dei,		//死亡

		None = -1,	//未設定
	};
public:

	CBoss2();
	~CBoss2();

public:


	//キャラクター構造体
	struct CHARA
	{
		int x;
		int y;
	};

	//動作関数
	void Update() override;//override:再定義前の関数が仮想関数かチェックできる
	//		仮想関数でない場合はエラーになる
//描画関数
	void Draw(CCamera* pCamera) override;
	//アニメーション処理
	void Animation();

	CHARA		m_Boss2;

	bool		m_Atacking;		//攻撃中

};